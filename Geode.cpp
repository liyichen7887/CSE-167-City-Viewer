#include "Geode.h"
#include <iostream>

Geode::Geode(const char *filepath, GLint geodeshaderProgram) {
	modelM = glm::mat4(1.0f);
	angle = 0.0f;
	shader = geodeshaderProgram;

	parse(filepath);
	VBO = 0;
	VBO_N = 0;
	EBO = 0;
	// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO_N);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
	// Consider the VAO as a container for all your buffers.
	glBindVertexArray(VAO);

	// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
	// you want to draw, such as vertices, normals, colors, etc.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	glBindBuffer(GL_ARRAY_BUFFER, VBO_N);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0);

	// We've sent the vertex data over to OpenGL, but there's still something missing.
	// In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);
}

void Geode::parse(const char *filepath)
{
	FILE* fp;     // file pointer
	float x, y, z;  // vertex coordinates
	unsigned int f_1_n, f_2_n, f_3_n;
	unsigned int f_1, f_2, f_3;
	float r, g, b;  // vertex color
	int c1, c2, c3;    // characters read from file
	int v_count = 0;
	int n_count = 0;
	int f_count = 0;
	fp = fopen(filepath, "rb");  // make the file name configurable so you can load other files

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	while (!feof(fp)) {
		c1 = fgetc(fp);
		c2 = fgetc(fp);
		char line[150];
		if ((c1 == 'v') && (c2 == ' ')) {
			fscanf(fp, "%f %f %f", &x, &y, &z);
			glm::vec3 vertex_pos(x, y, z);
			vertices.push_back(vertex_pos);
			v_count++;
		}
		else if ((c1 == 'v') && (c2 == 'n')) {
			c3 = fgetc(fp);
			if (c3 == ' ') {
				fscanf(fp, "%f %f %f", &x, &y, &z);
				glm::vec3 vertex_pos(x, y, z);
				normals.push_back(glm::normalize(vertex_pos));
			}
			n_count++;
		}
		else if ((c1 == 'f') && (c2 == ' ')) {
			fscanf(fp, "%u//%u %u//%u %u//%u", &f_1, &f_1_n, &f_2, &f_2_n, &f_3, &f_3_n);
			indices.push_back(f_1 - 1);
			indices.push_back(f_2 - 1);
			indices.push_back(f_3 - 1);
		}
		fgets(line, 300, fp);

		/*
		if (line_count == 1) {
		cout << line << endl;
		}
		if (line_count == 139350) {
		cout << line << endl;
		}
		*/

		// Populate the face indices, vertices, and normals vectors with the OBJ Object data
	}// read normal data accordingly

	fclose(fp);   // make sure you don't forget to close the file when done

	float x_max = std::numeric_limits<float>::min();
	float x_min = std::numeric_limits<float>::max();
	float y_max = std::numeric_limits<float>::min();
	float y_min = std::numeric_limits<float>::max();
	float z_max = std::numeric_limits<float>::min();
	float z_min = std::numeric_limits<float>::max();

	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		if (vertices[i].x > x_max) {
			x_max = vertices[i].x;
		}
		if (vertices[i].x < x_min) {
			x_min = vertices[i].x;
		}
		if (vertices[i].y > y_max) {
			y_max = vertices[i].y;
		}
		if (vertices[i].y < y_min) {
			y_min = vertices[i].y;
		}
		if (vertices[i].z > z_max) {
			z_max = vertices[i].z;
		}
		if (vertices[i].z < z_max) {
			z_min = vertices[i].z;
		}
	}

	float x_center = (x_max + x_min) / 2;
	float y_center = (y_max + y_min) / 2;
	float z_center = (z_max + z_min) / 2;


	std::vector<glm::vec3> vertices_center;
	for (auto&& v : vertices) {
		v = v - glm::vec3(x_center, y_center, z_center);
		vertices_center.push_back(v);
	}
	vertices = vertices_center;
}

void Geode::update() {
	//spin(100.0f);
}

void Geode::spin(float deg)
{
	this->angle += deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
	// This creates the matrix to rotate the cube
	angle = deg;
	this->modelM = this->modelM * glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Geode::draw(glm::mat4 M) {
	//modelM = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	modelM = M;
	//set the modelview matrix to M
	//printf("%f", light.direction.x);
	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * modelM;
	// We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
	// Consequently, we need to forward the projection, view, and model matrices to the shader programs
	// Get the location of the uniform variables "projection" and "modelview"
	uProjection = glGetUniformLocation(shader, "projection");
	uModelview = glGetUniformLocation(shader, "modelview");
	uModel = glGetUniformLocation(shader, "model");
	// Now send these values to the shader program
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &modelM[0][0]);

	if (sphere == true) {
		glUniform1f(glGetUniformLocation(shader, "transparency"), 0.3);
	}
	else {
		glUniform1f(glGetUniformLocation(shader, "transparency"), 1.0);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Now draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(VAO);
	// Tell OpenGL to draw with triangles, using 36 indices, the type of the indices, and the offset to start from
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);
}

glm::mat4 Geode::getMatrix() {
	return modelM;
}

void Geode::setMatrix(glm::mat4 mat) {
	modelM = mat;
}
