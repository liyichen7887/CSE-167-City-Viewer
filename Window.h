#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#define GLFW_INCLUDE_GLEXT
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include "shader.h"
#include "Skybox.h"
#include "Geode.h"
#include "Transform.h"

//blur
#include "CustomFBO.h"
#include <iostream>
#include <list>

//city
#include "City.h"

//water
#include "Camera.h"
#include "Water.h"
#include "SOIL.h"


class Window
{
public:
	static float focal;
	static int width;
	static int height;
	static glm::mat4 P; // P for projection
	static glm::mat4 V; // V for view
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static glm::vec3 trackBallMapping(double xpos, double ypos);
	static void poll_movement();
	static void renderToWaterRefractionBuffer();
	static void renderToWaterReflectionBuffer();
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void Do_Movement();
};

#endif
