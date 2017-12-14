#include "RobotSphere.h"
#include "Window.h"
#include <iostream>

RobotSphere::RobotSphere(int segments, int freqHor, int freqVer) {
	this->segments = segments;
	int radius;
	//create a circle in z = 0 plane first 
	drawLayer(0.0f, 60.0f);

	//then rotate an angle and draw the points with rotation matrix
	float angle = 0.0f;
	while (angle < 360.0f)
	{
		glm::mat4 rotateMHor = glm::rotate(glm::mat4(1.0f), angle / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
		for (int i = 0; i < segments*2; i++)
		{
			glm::vec4 newPoint = rotateMHor * glm::vec4(points[i], 1.0f);
			glm::vec3 latestPoint = glm::vec3(newPoint.x / newPoint.w, newPoint.y / newPoint.w, newPoint.z / newPoint.w);
			//then add it into points
			points.push_back(latestPoint);
		}
		angle += 360.0f/freqHor;
	}

	//angle = 0.0f;
	//while (angle < 360.0f)
	//{
	//	glm::mat4 rotateMVer = glm::rotate(glm::mat4(1.0f), angle / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	//	for (int i = 0; i < segments * 2; i++)
	//	{
	//		glm::vec4 newPoint2 = rotateMVer * glm::vec4(points[i], 1.0f);
	//		glm::vec3 latestPoint2 = glm::vec3(newPoint2.x / newPoint2.w, newPoint2.y / newPoint2.w, newPoint2.z / newPoint2.w);
	//		//then add it into points
	//		points.push_back(latestPoint2);
	//	}
	//	angle += 360.0f/freqVer;
	//}
	std::cout << points.size() << std::endl;
	//time to do the VAO VBO stuff
	// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
	// Consider the VAO as a container for all your buffers.
	glBindVertexArray(VAO);

	// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
	// you want to draw, such as vertices, normals, colors, etc.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
	glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GL_FLOAT), // 3 * sizeof(GLfloat) Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

		
	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);
}

RobotSphere::~RobotSphere() {
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void RobotSphere::render(glm::mat4 C) {

	modelM = C;
	glUseProgram(sphereShaderProgram);
	// Calculate the combination of the model and view (camera inverse) matrices
	glm::mat4 modelview = Window::V * modelM;

	//glDepthMask(GL_FALSE);// Remember to turn depth writing off
	//glUseProgram(shaderProgram);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	// We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
	// Consequently, we need to forward the projection, view, and model matrices to the shader programs
	// Get the location of the uniform variables "projection" and "modelview"

	uProjection = glGetUniformLocation(sphereShaderProgram, "projection");
	uModelview = glGetUniformLocation(sphereShaderProgram, "modelview");
	uModel = glGetUniformLocation(sphereShaderProgram, "model");

	// Now send these values to the shader program
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &modelM[0][0]);

	// Now draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(VAO);

	glDrawArrays(GL_LINES, 0, points.size()/2);

	// Tell OpenGL to draw with triangles, using number of indices, the type of the indices, and the offset to start from
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);

}

void RobotSphere::drawLayer(float z, float radius) {
	for (int i = 0; i < segments; i++) {
		float angle = 2 * glm::pi<float>() * i / segments,
			next_angle = 2 * glm::pi<float>() * (i + 1) / segments;
		float x1 = cos(angle) * radius;
		float y1 = sin(angle) * radius;
		float x2 = cos(next_angle) * radius;
		float y2 = sin(next_angle) * radius;
		points.push_back(glm::vec3(x1, y1,z));
		points.push_back(glm::vec3(x2, y2,z));
	}
}

glm::mat4 RobotSphere::getMatrix() {
	return modelM;
}

void RobotSphere::setMatrix(glm::mat4 mat) {
	modelM = mat;
}

void RobotSphere::update() {

}

void RobotSphere::draw(glm::mat4 C) {
	render(C);
}
