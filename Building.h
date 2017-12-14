//
//  Building.h
//  FinalProject
//
//  Created by Ying Wang on 12/7/17.
//  Copyright © 2017 Ying Wang. All rights reserved.
//

#ifndef Building_h
#define Building_h

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


//#include "stb_image.h"

class Building
{
  
public:
 
    /*
    float vertices[180] = {
        // positions
        -5.0f, -5.0f, -5.0f,  0.0f, 0.0f,
        5.0f, -5.0f, -5.0f,  1.0f, 0.0f,
        5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        -5.0f,  5.0f, -5.0f,  0.0f, 1.0f,
        -5.0f, -5.0f, -5.0f,  0.0f, 0.0f,
        
        -5.0f, -5.0f,  5.0f,  0.0f, 0.0f,
        5.0f, -5.0f,  5.0f,  1.0f, 0.0f,
        5.0f, 5.0f,  5.0f,  1.0f, 1.0f,
        5.0f,  5.0f,  5.0f,  1.0f, 1.0f,
        -5.0f,  5.0f,  5.0f,  0.0f, 1.0f,
        -5.0f, -5.0f,  5.0f,  0.0f, 0.0f,
        
        -5.0f,  5.0f,  5.0f,  1.0f, 0.0f,
        -5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        -5.0f, -5.0f, -5.0f,  0.0f, 1.0f,
        -5.0f, -5.0f, -5.0f,  0.0f, 1.0f,
        -5.0f, -5.0f,  5.0f,  0.0f, 0.0f,
        -5.0f,  5.0f,  5.0f,  1.0f, 0.0f,
        
        5.0f,  5.0f,  5.0f,  1.0f, 0.0f,
        5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        5.0f, -5.0f, -5.0f,  0.0f, 1.0f,
        5.0f, -5.0f, -5.0f,  0.0f, 1.0f,
        5.0f, -5.0f,  5.0f,  0.0f, 0.0f,
        5.0f,  5.0f,  5.0f,  1.0f, 0.0f,
        
        -5.0f, -5.0f, -5.0f,  0.0f, 1.0f,
        5.0f, -5.0f, -5.0f,  1.0f, 1.0f,
        5.0f, -5.0f,  5.0f,  1.0f, 0.0f,
        5.0f, -5.0f,  5.0f,  1.0f, 0.0f,
        -5.0f, -5.0f,  5.0f,  0.0f, 0.0f,
        -5.0f, -5.0f, -5.0f,  0.0f, 1.0f,
        
        -5.0f,  5.0f, -5.0f,  0.0f, 1.0f,
        5.0f,  5.0f, -5.0f,  1.0f, 1.0f,
        5.0f,  5.0f,  5.0f,  1.0f, 0.0f,
        5.0f,  5.0f,  5.0f,  1.0f, 0.0f,
        -5.0f,  5.0f,  5.0f,  0.0f, 0.0f,
        -5.0f,  5.0f, -5.0f,  0.0f, 1.0f
    };
    */
    
    
    /*float vertices[180] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    */
    
    
    glm::vec3 position;
    glm::mat4 toWorld;
    unsigned int VAO, VBO;
    GLuint projection, view, model;
    bool tri;
    float length;
    float width;
    float height;
    float vertices[180];
    unsigned int texture;
    
   
    Building(float len, float wid, float hei, glm::vec3 pos, unsigned int triangle,unsigned int tex);
    
    void draw(GLuint shaderProgram);
    //unsigned int loadTexture(std::string path);
    void update(){};
};


#endif /* Building_h */
