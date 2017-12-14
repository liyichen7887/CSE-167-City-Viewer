#include "RobotCube.h"
#include "../Window.h"
#include <iostream>

using namespace std;

RobotCube::RobotCube() {
	angle = 30.0f;
	
	// Create array object and buffers. Remember to delete your buffers when the object is destroyed!
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBOVertex);
	glGenBuffers(1, &VBONormal);

	// Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
	// Consider the VAO as a container for all your buffers.
	glBindVertexArray(VAO);

	// Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
	// you want to draw, such as vertices, normals, colors, etc.
	glBindBuffer(GL_ARRAY_BUFFER, VBOVertex);
	// glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
	// the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Enable the usage of layout location 0 (check the vertex shader to see what this is)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
	3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
	GL_FLOAT, // What type these components are
	GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
	3* sizeof(GL_FLOAT) , // 3 * sizeof(GLfloat) Offset between consecutive indices. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
	(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	//Now to do VBO Normals
	/*glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBONormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
*/
	// Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind the VAO now so we don't accidentally tamper with it.
	// NOTE: You must NEVER unbind the element array buffer associated with a VAO!
	glBindVertexArray(0);
	
}

RobotCube::~RobotCube() {
	// Delete previously generated buffers. Note that forgetting to do this can waste GPU memory in a 
	// large project! This could crash the graphics driver due to memory leaks, or slow down application performance!
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBOVertex);
	glDeleteBuffers(1, &VBONormal);
}

void RobotCube::render() {
	// Calculate the combination of the model and view (camera inverse) matrices
	glUseProgram(cubeShaderProgram);

	glm::mat4 modelview = Window::V * modelM;

	//glDepthMask(GL_FALSE);// Remember to turn depth writing off
	//glUseProgram(shaderProgram);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	// We need to calcullate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
	// Consequently, we need to forward the projection, view, and model matrices to the shader programs
	// Get the location of the uniform variables "projection" and "modelview"
	
	uProjection = glGetUniformLocation(cubeShaderProgram, "projection");
	uModelview = glGetUniformLocation(cubeShaderProgram, "modelview");
	uModel = glGetUniformLocation(cubeShaderProgram, "model");

	// Now send these values to the shader program
	glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(uModelview, 1, GL_FALSE, &modelview[0][0]);
	glUniformMatrix4fv(uModel, 1, GL_FALSE, &modelM[0][0]);

	// Now draw the cube. We simply need to bind the VAO associated with it.
	glBindVertexArray(VAO);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Tell OpenGL to draw with triangles, using number of indices, the type of the indices, and the offset to start from
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
	glBindVertexArray(0);
}

void RobotCube::update() {
	swing(1.0f);
}

void RobotCube::swing(float deg) {
	if (this->angle > 60.0f || (this->angle < 0.0f && this->angle >-60.0f)) {
		//time to swing back
		this->angle -= deg;
	}
	else if (this->angle < -60.0f || (this->angle >0.0f && this->angle < 60.0f)) {
		//swing foward
		this->angle += deg;
	}
	// This creates the matrix to rotate the cube
	this->rotateM = glm::rotate(glm::mat4(1.0f), this->angle / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	this->modelM = this->rotateM * this->modelM;
}