#ifndef _ROBOTSPHERE_H_
#define _ROBOTSPHERE_H_

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
// Use of degrees is deprecated. Use radians instead.
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Geode.h"

#define SPHERE_VERTEX_SHADER_PATH "../SphereShader.vert"
#define SPHERE_FRAGMENT_SHADER_PATH "../SphereShader.frag"

class RobotSphere : public Node {
public:
	//a robotsphere with radius of 1
	glm::mat4 modelM;
	RobotSphere(int segments, int freqHor,int freqVer);
	~RobotSphere();

	std::vector<glm::vec3> points;
	int segments;
	void drawLayer(float z, float radius);
	void render(glm::mat4 C);
	void update();
	void draw(glm::mat4 C);
	glm::mat4 getMatrix();
	void setMatrix(glm::mat4 mat);

	GLuint VAO, VBO;
	GLuint uProjection, uModelview, uModel;
	GLint sphereShaderProgram = LoadShaders(SPHERE_VERTEX_SHADER_PATH, SPHERE_FRAGMENT_SHADER_PATH);
	
};

#endif