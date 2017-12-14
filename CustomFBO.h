#ifndef _FBO_H_
#define _FBO_H_
#define GLFW_INCLUDE_GLEXT
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS
#endif
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
using namespace std;
class CustomFBO {
public:
	GLuint FBO, colorMap, depthMap;
	CustomFBO(int, int);
	~CustomFBO();
	void update(int, int);
private:
	void initFBO(int width, int height);
	void deleteFBO();
};
#endif
