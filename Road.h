//
//  Road.h
//  FinalProject
//
//  Created by Ying Wang on 12/10/17.
//  Copyright © 2017 Ying Wang. All rights reserved.
//

#ifndef Road_h
#define Road_h

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
//#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Road
{
public:
    float length;
    float width;
    glm::vec2 TL;
    glm::vec2 TR;
    glm::vec2 BL;
    glm::vec2 BR;
    unsigned int texture;
    glm::mat4 toWorld;
    unsigned int VAO, VBO, EBO;
    GLuint projection, view, model;
    float vertices[30];
    glm::vec2 pos;
    Road(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br,unsigned int tex);
    void draw(GLuint shaderProgram);
    
    
};
#endif /* Road_h */
