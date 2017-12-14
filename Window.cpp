#include "window.h"
const char* window_title = "GLFW Starter Project";

// Default camera parameters
glm::vec3 cam_pos(0.0f, 1.0f, 100.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;



Skybox * skybox;
GLint shaderProgram;
GLint skybox_shader;
GLint dofShaderProgram;
GLint motionShaderProgram;
GLint building_shader;
GLuint waterShaderProgram;


GLfloat quadVertices[] = {
	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f,  1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "../shader.vert"
#define FRAGMENT_SHADER_PATH "../shader.frag"

#define SKYBOX_VERTEX_SHADER_PATH "../skybox_shader.vert"
#define SKYBOX_FRAGMENT_SHADER_PATH "../skybox_shader.frag"

#define DOF_VERTEX_SHADER_PATH "../DOFshader.vert"
#define DOF_FRAGMENT_SHADER_PATH "../DOFshader.frag"

#define MOTION_VERTEX_SHADER_PATH "../motion_shader.vert"
#define MOTION_FRAGMENT_SHADER_PATH "../motion_shader.frag"

#define VERTEX_SHADER_BUILDING_PATH "../shader_bd.vert"
#define FRAGMENGT_SHADER_BUILDING_PATH "../shader_bd.frag"

#define WATER_V_SHADER_PATH "../waterShader.vert"
#define WATER_F_SHADER_PATH "../waterShader.frag"

//blur
float Window::focal;
GLuint frameBuffers;
GLuint texColorBuffers[2];
GLuint vaoQuad, vboQuad;
GLint uniTexOffset;
int boolDOF = 0;
int boolMB = 0;
int boolFOG = 0;
CustomFBO* screenFBO;
list<CustomFBO*>FBO_list;

//building
City * city;
bool followMouseR = false;
bool peopleView = false;
bool posZ = true;
bool posX = false;
bool negZ = false;
bool negX = false;
glm::vec3 camlook;
glm::vec3 campos;

//water
Camera camera(cam_pos);
//(glm::vec3(0.0f, 5.0f, 50.0f));
bool leftButtonDown;
bool firstMouseCallback;
bool escape_camera;
bool keys[1024];
glm::vec3 lastPoint;
//TimeKeeping
GLfloat deltaTime = 0.0f, lastFrame = 0.0f;
Water* water;
//Water reflection/refraction variables
glm::vec4 refract_clip = glm::vec4(0, -1, 0, 5);
glm::vec4 reflect_clip = glm::vec4(0, 1, 0, -5);


void setAttr(GLuint shaderProgram)
{
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}





Transform * robot;
Transform * body_trans;
Geode * body;
Transform * head_trans;
Geode * head;
Transform * lefteye_trans;
Geode * lefteye;
Transform * righteye_trans;
Geode * righteye;
Transform * leftant_trans;
Geode * leftant;
Transform * rightant_trans;
Geode * rightant;
Transform * la_trans;
Geode * la;
Transform * ra_trans;
Geode * ra;
Transform * ll_trans;
Geode * ll;
Transform * rl_trans;
Geode * rl;

int limb_count = 2;
float initial_angle1 = 90.0f;
float initial_angle2 = 90.0f;
float initial_angle3 = 90.0f;
float initial_angle4 = 90.0f;
float angular_range = 90.0f;
float velocity = 1.0f;





//trackball
int x_position;
int y_position;
glm::vec3 last_pos(1.0);
int trackball_on = 0;
float qAngle = 0.0f;




void Window::initialize_objects()
{
	skybox = new Skybox();
	city = new City();
	water = new Water(1000, 1000);
	
	// Load the shader program. Make sure you have the correct filepath up top
	shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
	skybox_shader = LoadShaders(SKYBOX_VERTEX_SHADER_PATH, SKYBOX_FRAGMENT_SHADER_PATH);

	dofShaderProgram = LoadShaders(DOF_VERTEX_SHADER_PATH, DOF_FRAGMENT_SHADER_PATH);
	motionShaderProgram = LoadShaders(MOTION_VERTEX_SHADER_PATH, MOTION_FRAGMENT_SHADER_PATH);

	building_shader = LoadShaders(VERTEX_SHADER_BUILDING_PATH, FRAGMENGT_SHADER_BUILDING_PATH);

	waterShaderProgram = LoadShaders(WATER_V_SHADER_PATH, WATER_F_SHADER_PATH);
	
	robot = new Transform();
	body_trans = new Transform();
	head_trans = new Transform();
	lefteye_trans = new Transform();
	righteye_trans = new Transform();
	leftant_trans = new Transform();
	rightant_trans = new Transform();
	la_trans = new Transform();
	ra_trans = new Transform();
	ll_trans = new Transform();
	rl_trans = new Transform();
	lefteye_trans = new Transform();
	righteye_trans = new Transform();
	leftant_trans = new Transform();
	rightant_trans = new Transform();


	body = new Geode("body.obj", shaderProgram);
	body_trans->addChild(body);
	//glm::mat4 body_pos = glm::mat4(1.0f) * glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, -300.0f));
	glm::mat4 body_rot = glm::rotate(glm::mat4(1.0f), 90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	body_trans->setMatrix(body_rot);
	robot->addChild(body_trans);

	head = new Geode("head.obj", shaderProgram);
	head_trans->addChild(head);
	glm::mat4 head_rot = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 head_pos = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 43.0f, 0.0f))*head_rot;
	head_trans->setMatrix(head_pos);
	robot->addChild(head_trans);

	//left arm
	la = new Geode("limb.obj", shaderProgram);
	la_trans->addChild(la);
	glm::mat4 limb_rot = glm::rotate(glm::mat4(1.0f), initial_angle1 / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 limb_pos = glm::mat4(1.0f) * glm::translate(glm::mat4(1.f), glm::vec3(-16.0f, 10.0f, -0.0f)) *limb_rot;
	//limb_pos = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f))*limb_pos;
	la_trans->setMatrix(limb_pos);
	robot->addChild(la_trans);

	//right arm
	ra = new Geode("limb.obj", shaderProgram);
	ra_trans->addChild(ra);
	limb_rot = glm::rotate(glm::mat4(1.0f), initial_angle2 / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	limb_pos = glm::translate(glm::mat4(1.f), glm::vec3(38.0f, 10.0f, -0.0f))*limb_rot ;
	ra_trans->setMatrix(limb_pos);
	robot->addChild(ra_trans);

	//left leg
	ll = new Geode("limb.obj", shaderProgram);
	ll_trans->addChild(ll);
	limb_rot = glm::rotate(glm::mat4(1.0f), initial_angle3 / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	limb_pos = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, -20.0f, 0.0f))*limb_rot;
	ll_trans->setMatrix(limb_pos);
	robot->addChild(ll_trans);

	//right leg
	rl = new Geode("limb.obj", shaderProgram);
	rl_trans->addChild(rl);
	limb_rot = glm::rotate(glm::mat4(1.0f), initial_angle4 / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	limb_pos = glm::translate(glm::mat4(1.f), glm::vec3(22.0f, -20.0f, 0.0f))*limb_rot;
	rl_trans->setMatrix(limb_pos);
	robot->addChild(rl_trans);

	//left eye
	lefteye = new Geode("eyeball.obj", shaderProgram);
	lefteye_trans->addChild(lefteye);	
	limb_rot = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	limb_pos = glm::mat4(1.0f) * glm::translate(glm::mat4(1.f), glm::vec3(-10.0f, 40.0f, 10.0f))*limb_rot;
	lefteye_trans->setMatrix(limb_pos);
	robot->addChild(lefteye_trans);

	//right eye
	righteye = new Geode("eyeball.obj", shaderProgram);
	righteye_trans->addChild(righteye);
	limb_rot = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	limb_pos = glm::mat4(1.0f) * glm::translate(glm::mat4(1.f), glm::vec3(10.0f, 40.0f, 10.0f))*limb_rot;
	righteye_trans->setMatrix(limb_pos);
	robot->addChild(righteye_trans);

	//left ant
	leftant = new Geode("antenna.obj", shaderProgram);
	leftant_trans->addChild(leftant);
	limb_rot = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
	limb_pos = glm::mat4(1.0f) * glm::translate(glm::mat4(1.f), glm::vec3(-8.0f, 50.0f, 0.0f))*limb_rot;
	
	leftant_trans->setMatrix(limb_pos);
	robot->addChild(leftant_trans);

	//right ant
	rightant = new Geode("antenna.obj", shaderProgram);
	rightant_trans->addChild(rightant);
	limb_rot = glm::rotate(glm::mat4(1.0f), -90.0f / 180.0f* glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f))* glm::rotate(glm::mat4(1.0f), 180.0f / 180.0f* glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	limb_pos = glm::mat4(1.0f) * glm::translate(glm::mat4(1.f), glm::vec3(8.0f, 50.0f, 0.0f))*limb_rot;
	rightant_trans->setMatrix(limb_pos);
	robot->addChild(rightant_trans);

	//blur
	
	auto fbo = new CustomFBO(Window::width, Window::height);
	screenFBO = new CustomFBO(Window::width, Window::height);
	FBO_list.push_back(fbo);
	glGenVertexArrays(1, &vaoQuad);
	glGenBuffers(1, &vboQuad);
	glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glBindVertexArray(vaoQuad);
	glBindBuffer(GL_ARRAY_BUFFER, vboQuad);
	setAttr(dofShaderProgram);
	setAttr(motionShaderProgram);
	focal = 0.0f;
	
	
}


// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	delete(screenFBO);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(skybox_shader);
	glDeleteProgram(motionShaderProgram);
	glDeleteProgram(dofShaderProgram);
	glDeleteFramebuffers(1, &frameBuffers);
	glDeleteTextures(2, texColorBuffers);
	glDeleteVertexArrays(1, &vaoQuad);
	glDeleteBuffers(1, &vboQuad);

	delete(city);
	glDeleteProgram(building_shader);

	delete water;
	glDeleteProgram(waterShaderProgram);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!

	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		//V = glm::lookAt(cam_pos, cam_look_at, cam_up);
		V = camera.GetViewMatrix();
	}
	if (screenFBO != 0) {
		screenFBO->update(Window::width, Window::height);
	}

	if (FBO_list.size() > 0) {
		//screenFBO->update(Window::width, Window::height);
		while (FBO_list.size() > 0) {
			auto fst = FBO_list.front();
			delete(fst);
			FBO_list.pop_front();
		}
	}

}

void Window::idle_callback()
{
	// Call the update function the cube
	poll_movement();



}

void Window::display_callback(GLFWwindow* window)
{
	
	// Clear the color and depth buffers
	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO->FBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// Use the shader of programID
	glUseProgram(shaderProgram);
	glm::vec3 center = glm::vec3(0.0f, -2.5f, 0.0f);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			
			glm::mat4 robot_scale = glm::mat4(1.0f) * glm::scale(glm::mat4(1.f), glm::vec3(0.25f, 0.25f, 0.25f));
			glm::mat4 robot_trans = glm::translate(glm::mat4(1.f), glm::vec3(-200.0f + float(i * 20), -50.0f, -200.0f + float(j * 20)))*robot_scale;
			//calculate the point in Canonical View Volume
			glm::vec4 interPoint = Window::P * Window::V * robot_trans * robot->getMatrix() * glm::vec4(center, 1.0f);
			glm::vec3 viewPoint = glm::vec3(interPoint.x / interPoint.w, interPoint.y / interPoint.w, interPoint.z / interPoint.w);

			//robot->draw(robot_trans);

		}
	}

	glUseProgram(building_shader);
	city->draw(building_shader);


	glUseProgram(skybox_shader);
	skybox->draw(skybox_shader);

	renderToWaterRefractionBuffer();
	renderToWaterReflectionBuffer();

	glDisable(GL_CLIP_DISTANCE0);

	glBindFramebuffer(GL_FRAMEBUFFER, screenFBO->FBO);
	glUseProgram(waterShaderProgram);
	glUniform1f(glGetUniformLocation(waterShaderProgram, "moveFactor"), water->moveFactor);
	water->draw(waterShaderProgram);
	
	
	if (boolMB == 0) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vaoQuad);
		glDisable(GL_DEPTH_TEST);
		glUseProgram(dofShaderProgram);
		glUniform1i(glGetUniformLocation(dofShaderProgram, "openFOG"), boolFOG);
		glUniform1i(glGetUniformLocation(dofShaderProgram, "openDOF"), boolDOF);
		glUniform1f(glGetUniformLocation(dofShaderProgram, "focus"), Window::focal);

		glUniform1i(glGetUniformLocation(dofShaderProgram, "texFramebuffer"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, screenFBO->colorMap);

		glUniform1i(glGetUniformLocation(dofShaderProgram, "tDepth"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, screenFBO->depthMap);

		glUniform2f(uniTexOffset, 1.0f / Window::width, 0.0f);

		glDrawArrays(GL_TRIANGLES, 0, 6);



	}
	else {
		if (FBO_list.size() >= 9) {
			auto lastone = FBO_list.back();
			delete(lastone);
			FBO_list.pop_back();
		}

		while (FBO_list.size() < 9) {

			FBO_list.push_front(new CustomFBO(Window::width, Window::height));

			glBindFramebuffer(GL_FRAMEBUFFER, FBO_list.front()->FBO);
			glBindVertexArray(vaoQuad);
			glDisable(GL_DEPTH_TEST);
			glUseProgram(dofShaderProgram);
			glUniform1i(glGetUniformLocation(dofShaderProgram, "openFOG"), boolFOG);
			glUniform1i(glGetUniformLocation(dofShaderProgram, "openDOF"), boolDOF);
			glUniform1f(glGetUniformLocation(dofShaderProgram, "focus"), Window::focal);

			glUniform1i(glGetUniformLocation(dofShaderProgram, "texFramebuffer"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, screenFBO->colorMap);

			glUniform1i(glGetUniformLocation(dofShaderProgram, "tDepth"), 1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, screenFBO->depthMap);

			glDrawArrays(GL_TRIANGLES, 0, 6);



		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(vaoQuad);
		glDisable(GL_DEPTH_TEST);
		glUseProgram(motionShaderProgram);
		//bind color map
		glUniform1i(glGetUniformLocation(motionShaderProgram, "numOfSample"), FBO_list.size());
		int i = 0;
		typedef list<CustomFBO*>::iterator FboIt;
		for (FboIt j = FBO_list.begin(); j != FBO_list.end(); ++j) {
			char integer_string[32];
			sprintf(integer_string, "%d", i);
			char other_string[64] = "texFramebuffer";
			strcat(other_string, integer_string);
			glUniform1i(glGetUniformLocation(motionShaderProgram, other_string), i);
			glActiveTexture(GL_TEXTURE0 + i);
			auto x = *j;
			glBindTexture(GL_TEXTURE_2D, x->colorMap);
			i++;
		}
		glDrawArrays(GL_TRIANGLES, 0, 6);

	}
	

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();


	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (focal >= 0 && focal <= 500) {
		focal += yoffset * 7;
	}
	if (focal >= 500) focal = 500;
	if (focal <= 0) focal = 0;

}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_M)
		{
			if (boolMB == 1) {
				boolMB = 0;
			}
			else {
				boolMB = 1;
			}
		}
		if (key == GLFW_KEY_O) {
			if (boolDOF == 1) {
				boolDOF = 0;
			}
			else {
				boolDOF = 1;
			}
		}
		if (key == GLFW_KEY_F) {
			if (boolFOG == 1) {
				boolFOG = 0;
			}
			else {
				boolFOG = 1;
			}
		}
		if (key == GLFW_KEY_C)
		{
			city = new City();
			glUseProgram(building_shader);
			city->draw(building_shader);
		}
		if (key == GLFW_KEY_W) {
			keys[key] = true;
		}
		else if (key == GLFW_KEY_S) {
			keys[key] = true;
		}
		else if (key == GLFW_KEY_A) {
			keys[key] = true;
		}
		else if (key == GLFW_KEY_D) {
			keys[key] = true;
		}
		else if (mods == GLFW_MOD_ALT) {
			escape_camera = !escape_camera;
		}
		
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_W:
		case GLFW_KEY_A:
		case GLFW_KEY_S:
		case GLFW_KEY_D:
			keys[key] = false;
			break;
		}
	}
}

void Window::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	x_position = xpos;
	y_position = ypos;
	/*
	if (xpos < width && xpos >= 0 && ypos < height && ypos >= 0) {
		if (trackball_on == 1) {
			glm::vec3 curr_pos = glm::vec3(xpos, ypos, 0);
			glm::vec3 curr_pos_track = trackBallMapping(curr_pos.x, curr_pos.y);
			glm::vec3 last_pos_track = trackBallMapping(last_pos.x, last_pos.y);
			glm::vec3 direction = curr_pos_track - last_pos_track;
			float velocity = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
			if (velocity > 0.001) // If little movement - do nothing.
			{
				glm::vec3 normal = glm::cross(last_pos_track, curr_pos_track);
				float angle = acos(glm::dot(normalize(last_pos_track), normalize(curr_pos_track)));

				Window::V = glm::rotate(glm::mat4(1.0f), velocity * 5, normal)*Window::V;
			}
			last_pos = curr_pos;
		}
	}*/
	if (leftButtonDown) {
		if (firstMouseCallback)
		{
			lastPoint.x = xpos;
			lastPoint.y = ypos;
			firstMouseCallback = false;
		}

		GLfloat xoffset = xpos - lastPoint.x;
		GLfloat yoffset = lastPoint.y - ypos;  // Reversed since y-coordinates go from bottom to left

		lastPoint.x = xpos;
		lastPoint.y = ypos;
		if (escape_camera) return;
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

glm::vec3 Window::trackBallMapping(double xpos, double ypos)    // The CPoint class is a specific Windows class. Either use separate x and y values for the mouse location, or use a Vector3 in which you ignore the z coordinate.
{
	glm::vec3 v;    // Vector v is the synthesized 3D position of the mouse location on the trackball
	float d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
	v.x = (2.0*xpos - Window::width) / Window::width;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
	v.y = (Window::height - 2.0*ypos) / Window::height;   // this does the equivalent to the above for the mouse Y position
	v.z = 0.0;   // initially the mouse z position is set to zero, but this will change below
	d = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
	d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
	v.z = sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
	v = normalize(v); // Still need to normalize, since we only capped d, not v.
	return v;  // return the mouse location on the surface of the trackball
}


void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	/*
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		last_pos = glm::vec3(x_position, y_position, 0);
		trackball_on = 1;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		trackball_on = 0;
	}*/

	if (action == GLFW_PRESS) {

		//left mouse button pressed, rotation detected
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			leftButtonDown = true;

			std::cout << "left button pressed\n";
		}
	}
	//left button released
	if (action == GLFW_RELEASE) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			leftButtonDown = false;
			firstMouseCallback = true;
			std::cout << "left button released\n";
		}
	}
}

void Window::poll_movement() {
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	Do_Movement();
	V = camera.GetViewMatrix();
	P = glm::perspective(camera.Zoom, (float)width / (float)height, 0.1f, 1000.0f);
}

void Window::renderToWaterReflectionBuffer() {

	glUseProgram(waterShaderProgram);
	glEnable(GL_CLIP_DISTANCE0);
	water->SendDataToShader(waterShaderProgram);
	auto camPos = glGetUniformLocation(waterShaderProgram, "cameraPosition");
	glUniform3f(camPos, camera.Position.x, camera.Position.y, camera.Position.z);
	//load move factor

	//load clip plane into shader


	water->bindFB(Water::REFLECTION);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat distance = 0;
	//GLfloat distance = 2 * (camera.Position.y - water->height);
	camera.Position.y -= distance;
	camera.invertPitch();
	camera.updateCameraVectors();

	V = camera.GetViewMatrix();

	

	//draw the scene
	glUseProgram(skybox_shader);
	//glUniform4f(glGetUniformLocation(skyCubeShaderProgram, "plane"), reflect_clip.x, reflect_clip.y, reflect_clip.z, reflect_clip.w);
	//skycube->bind();
	skybox->draw(skybox_shader);

	glUseProgram(building_shader);
	city->draw(building_shader);
	//draw other objects...
	//glUseProgram(shaderProgram);
	//glUniform4f(glGetUniformLocation(shaderProgram, "plane"), reflect_clip.x, reflect_clip.y, reflect_clip.z, reflect_clip.w);
	//obj1->draw(shaderProgram);
	//obj2->draw(shaderProgram);
	//obj3->draw(shaderProgram);
	//obj4->draw(shaderProgram);

	camera.Position.y += distance;
	camera.invertPitch();
	camera.updateCameraVectors();
	V = camera.GetViewMatrix();
	water->unbindFB();
	glDisable(GL_CLIP_DISTANCE0);
}

void Window::renderToWaterRefractionBuffer() {
	
	glUseProgram(waterShaderProgram);
	glEnable(GL_CLIP_DISTANCE0);
	water->SendDataToShader(waterShaderProgram);
	//load camera position to shader
	auto camPos = glGetUniformLocation(waterShaderProgram, "cameraPosition");
	glUniform3f(camPos, camera.Position.x, camera.Position.y, camera.Position.z);
	//load move factor
	glUniform1f(glGetUniformLocation(waterShaderProgram, "moveFactor"), water->moveFactor);
	
	
	water->bindFB(Water::REFRACTION);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//draw the scene
	glUseProgram(building_shader);
	city->draw(building_shader);

	glUseProgram(skybox_shader);
	glUniform4f(glGetUniformLocation(skybox_shader, "plane"), refract_clip.x, refract_clip.y, refract_clip.z, refract_clip.w);
	//skycube->bind();
	skybox->draw(skybox_shader);
	//draw other objects...

	//glUseProgram(shaderProgram);
	//glUniform4f(glGetUniformLocation(shaderProgram, "plane"), refract_clip.x, refract_clip.y, refract_clip.z, refract_clip.w);
	//obj1->draw(shaderProgram);
	//obj2->draw(shaderProgram);
	//obj3->draw(shaderProgram);
	//obj4->draw(shaderProgram);

	water->unbindFB();
	glDisable(GL_CLIP_DISTANCE0);
	
}

void Window::Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime*3);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime*3);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime*3);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime*3);
}
