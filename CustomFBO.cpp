#include "CustomFBO.h"

CustomFBO::CustomFBO(int width, int height)
{
	initFBO(width, height);
}

CustomFBO::~CustomFBO()
{
	deleteFBO();
}

void CustomFBO::deleteFBO()
{
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1, &depthMap);
	glDeleteTextures(1, &colorMap);
}

void CustomFBO::initFBO(int width, int height)
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	// Create two textures to hold color buffers
	glGenTextures(1, &depthMap);
	glGenTextures(1, &colorMap);

	// Set up the first framebuffer's depth buffer
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

	// Set up the second framebuffer's color buffer
	glBindTexture(GL_TEXTURE_2D, colorMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorMap, 0);



	// check error
	GLenum err = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (err == GL_FRAMEBUFFER_COMPLETE) {
		//cout << "fbo ready!" << endl;
	}
}



void CustomFBO::update(int width, int height)
{
	deleteFBO();
	initFBO(width, height);
}
