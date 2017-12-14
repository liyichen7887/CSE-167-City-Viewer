#ifndef _GEODE_H_
#define _GEODE_H_

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
#include "Node.h"
#include "shader.h"
#include "Window.h"



class Geode : public Node {
public:
	float angle = 0.0f;
	glm::mat4 modelM;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	GLuint shader;
	bool sphere = false;

	GLuint VBO, VAO, VBO_N, EBO;
	GLuint uProjection, uModelview, uModel;

	Geode(const char *filepath, GLint geodeshaderProgram);
	~Geode(){}
	void spin(float deg);

	void draw(glm::mat4 C);
	void update();
	glm::mat4 getMatrix();
	void setMatrix(glm::mat4 mat);
	void parse(const char *filepath);
};

#endif
