//
//  Building.cpp
//  FinalProject
//
//  Created by Ying Wang on 12/7/17.
//  Copyright © 2017 Ying Wang. All rights reserved.
//


#include <iostream>
#include "Building.h"
#include "Window.h"

using namespace std;

Building::Building(float len, float wid, float hei, glm::vec3 pos, unsigned int triangle, unsigned int tex)
{
    texture = tex;
    tri = triangle;
    toWorld = glm::mat4(1.0f);
    //toWorld = glm::translate(glm::mat4(1.f), glm::vec3(0, 100, 100))*glm::mat4(1.0f);
    length = len;
    width = wid;
    height = hei;
    position = pos;
   
    
    float minX = position.x - length / 2.0;
    float maxX = position.x + length / 2.0;
    float minY = 0.0f;
    float maxY = height;
    float minZ = position.z - width / 2.0;
    float maxZ = position.z + width / 2.0;
    
    if(tri == 0){
    float ver[180] = {
        // positions
        // back
        minX, minY, minZ,  0.0f, 0.0f,
        maxX, minY, minZ,  1.0f, 0.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        minX, maxY, minZ,  0.0f, 1.0f,
        minX, minY, minZ,  0.0f, 0.0f,
     
        // front
        minX, minY, maxZ,  0.0f, 0.0f,
        maxX, minY, maxZ,  1.0f, 0.0f,
        maxX, maxY, maxZ,  1.0f, 1.0f,
        maxX, maxY, maxZ,  1.0f, 1.0f,
        minX, maxY, maxZ,  0.0f, 1.0f,
        minX, minY, maxZ,  0.0f, 0.0f,
     
        // left
        minX, maxY, maxZ,  0.0f, 0.0f,
        minX, maxY, minZ,  1.0f, 0.0f,
        minX, minY, minZ,  1.0f, 1.0f,
        minX, minY, minZ,  1.0f, 1.0f,
        minX, minY, maxZ,  0.0f, 1.0f,
        minX, maxY, maxZ,  0.0f, 0.0f,
     
        // right
        maxX, maxY, maxZ,  0.0f, 0.0f,
        maxX, maxY, minZ,  1.0f, 0.0f,
        maxX, minY, minZ,  1.0f, 1.0f,
        maxX, minY, minZ,  1.0f, 1.0f,
        maxX, minY, maxZ,  0.0f, 1.0f,
        maxX, maxY, maxZ,  0.0f, 0.0f,
     
        // bottom
        minX, minY, minZ,  0.0f, 1.0f,
        maxX, minY, minZ,  1.0f, 1.0f,
        maxX, minY, maxZ,  1.0f, 0.0f,
        maxX, minY, maxZ,  1.0f, 0.0f,
        minX, minY, maxZ,  0.0f, 0.0f,
        minX, minY, minZ,  0.0f, 1.0f,
     
        // top
        minX, maxY, minZ,  0.0f, 1.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        maxX, maxY, maxZ,  1.0f, 0.0f,
        maxX, maxY, maxZ,  1.0f, 0.0f,
        minX, maxY, maxZ,  0.0f, 0.0f,
        minX, maxY, minZ,  0.0f, 1.0f
    };
        for(int i = 0; i < 180; i++)
        {
            vertices[i] = ver[i];
        }
        
    }
    else if(tri == 1){
    
    
    // triangle building
     float ver[180] = {
     // positions          // texture Coords
     
     // back
     minX, minY, minZ,  0.0f, 0.0f,
     maxX, minY, minZ,  1.0f, 0.0f,
     maxX, maxY, minZ,  1.0f, 1.0f,
     maxX, maxY, minZ,  1.0f, 1.0f,
     minX, maxY, minZ,  0.0f, 1.0f,
     minX, minY, minZ,  0.0f, 0.0f,
     
     // front
     minX, minY, maxZ,  0.0f, 0.0f,
     maxX, minY, minZ,  1.0f, 0.0f,
     maxX, maxY, minZ,  1.0f, 1.0f,
     maxX, maxY, minZ,  1.0f, 1.0f,
     minX, maxY, maxZ,  0.0f, 1.0f,
     minX, minY, maxZ,  0.0f, 0.0f,
     
     //left
     minX, maxY, maxZ,  0.0f, 0.0f,
     minX, maxY, minZ,  1.0f, 0.0f,
     minX, minY, minZ,  1.0f, 1.0f,
     minX, minY, minZ,  1.0f, 1.0f,
     minX, minY, maxZ,  0.0f, 1.0f,
     minX, maxY, maxZ,  0.0f, 0.0f,
    
     //right
         minX, minY, maxZ,  0.0f, 0.0f,
         maxX, minY, minZ,  1.0f, 0.0f,
         maxX, maxY, minZ,  1.0f, 1.0f,
         maxX, maxY, minZ,  1.0f, 1.0f,
         minX, maxY, maxZ,  0.0f, 1.0f,
         minX, minY, maxZ,  0.0f, 0.0f,
     
     //bottom
     minX, minY, minZ,  0.0f, 1.0f,
     maxX, minY, minZ,  1.0f, 1.0f,
      maxX, minY, minZ, 1.0f, 1.0f,
      maxX, minY, minZ,  1.0f, 1.0f,
     minX, minY, maxZ,  0.0f, 0.0f,
     minX, minY, minZ,  0.0f, 1.0f,
     
     // top
     minX, maxY, minZ,  0.0f, 1.0f,
     maxX, maxY, minZ,  1.0f, 1.0f,
     maxX, maxY, minZ,  1.0f, 1.0f,
    maxX, maxY, minZ,  1.0f, 1.0f,
     minX, maxY, maxZ,  0.0f, 0.0f,
     minX, maxY, minZ,  0.0f, 1.0f
     };
    
        for(int i = 0; i < 180; i++)
        {
            vertices[i] = ver[i];
        }
        
    }

    else{
        float ver[180] = {
        //back
        minX, minY, maxZ,  0.0f, 0.0f,
        maxX, minY, minZ,  1.0f, 0.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        minX, maxY, maxZ,  0.0f, 1.0f,
        minX, minY, maxZ,  0.0f, 0.0f,
        
        // front
        minX, minY, maxZ,  0.0f, 0.0f,
        maxX, minY, maxZ,  1.0f, 0.0f,
        maxX, maxY, maxZ,  1.0f, 1.0f,
        maxX, maxY, maxZ,  1.0f, 1.0f,
        minX, maxY, maxZ,  0.0f, 1.0f,
        minX, minY, maxZ,  0.0f, 0.0f,
        
        //back
        minX, minY, maxZ,  0.0f, 0.0f,
        maxX, minY, minZ,  1.0f, 0.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        minX, maxY, maxZ,  0.0f, 1.0f,
        minX, minY, maxZ,  0.0f, 0.0f,
        
        // right
        maxX, maxY, maxZ,  0.0f, 0.0f,
        maxX, maxY, minZ,  1.0f, 0.0f,
        maxX, minY, minZ,  1.0f, 1.0f,
        maxX, minY, minZ,  1.0f, 1.0f,
        maxX, minY, maxZ,  0.0f, 1.0f,
        maxX, maxY, maxZ,  0.0f, 0.0f,
        
        // bottom
        minX, minY, maxZ,  0.0f, 1.0f,
        maxX, minY, minZ,  1.0f, 1.0f,
        maxX, minY, maxZ,  1.0f, 0.0f,
        maxX, minY, maxZ,  1.0f, 0.0f,
        minX, minY, maxZ,  0.0f, 0.0f,
        minX, minY, maxZ,  0.0f, 1.0f,
        
        // top
        minX, maxY, maxZ,  0.0f, 1.0f,
        maxX, maxY, minZ,  1.0f, 1.0f,
        maxX, maxY, maxZ,  1.0f, 0.0f,
        maxX, maxY, maxZ,  1.0f, 0.0f,
        minX, maxY, maxZ,  0.0f, 0.0f,
            minX, maxY, maxZ,  0.0f, 1.0f};
        for(int i = 0; i < 180; i++)
        {
            vertices[i] = ver[i];
        }
    }
    
    
    
    
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}


void Building::draw(GLuint shaderProgram){
    
    
    
    glm::mat4 modelview = Window::V * toWorld;
    
    projection = glGetUniformLocation(shaderProgram, "projection");
    view = glGetUniformLocation(shaderProgram, "view");
    model = glGetUniformLocation(shaderProgram, "model");
    // Now send these values to the shader program
    glUniformMatrix4fv(projection, 1, GL_FALSE, &Window::P[0][0]);
    glUniformMatrix4fv(view, 1, GL_FALSE, &modelview[0][0]);
    glUniformMatrix4fv(model, 1, GL_FALSE, &toWorld[0][0]);
    
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}


