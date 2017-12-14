#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <algorithm>
#include <GL/glut.h>
#include <iostream>

#include "soil.h"

class Skybox
{
public:
	glm::mat4 toWorld;
	float angle;

	float skyboxVertices[108] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	unsigned int skyboxVAO, skyboxVBO;
	GLuint uProjection, uView, uWorld;
	Skybox();
	//void loadTexture();
	void draw(GLuint shaderProgram);
	GLuint loadCubemap(std::vector<const GLchar*> faces);
	const char *vinit[6] =
	{ "C:\\Users\\Yichen Li\\Desktop\\final_merge\\GLFWStarterProject\\TropicalSunnyDayRight2048.jpg",
		"C:\\Users\\Yichen Li\\Desktop\\final_merge\\GLFWStarterProject\\TropicalSunnyDayLeft2048.jpg",
		"C:\\Users\\Yichen Li\\Desktop\\final_merge\\GLFWStarterProject\\TropicalSunnyDayUp2048.jpg",
		"C:\\Users\\Yichen Li\\Desktop\\final_merge\\GLFWStarterProject\\TropicalSunnyDayDown2048.jpg",
		"C:\\Users\\Yichen Li\\Desktop\\final_merge\\GLFWStarterProject\\TropicalSunnyDayBack2048.jpg",
		"C:\\Users\\Yichen Li\\Desktop\\final_merge\\GLFWStarterProject\\TropicalSunnyDayFront2048.jpg" };

	std::vector<const GLchar*> faces
	{
		vinit, std::end(vinit)
	};
	unsigned int cubemapTexture = loadCubemap(faces);
	void spin(float deg);
	void update();
};

#endif