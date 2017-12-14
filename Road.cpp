//
//  Road.cpp
//  FinalProject
//
//  Created by Ying Wang on 12/10/17.
//  Copyright © 2017 Ying Wang. All rights reserved.
//

#include <stdio.h>
#include "Road.h"
#include "Window.h"

Road::Road(glm::vec2 tl, glm::vec2 tr, glm::vec2 bl, glm::vec2 br,unsigned int tex)
{

    texture = tex;
    TL.x = tl.x;
    TL.y = tl.y;
    TR.x = tr.x;
    TR.y = tr.y;
    BL.x = bl.x;
    BL.y = bl.y;
    BR.x = br.x;
    BR.y = br.y;
    
    
    toWorld = glm::mat4(1.0f);
    
    float ver[30]=
    {
		
        BL.x,0.0f,BL.y, 0.0f,0.0f,
        TL.x,0.0f,TL.y, 0.0f,1.0f,
        TR.x,0.0f,TR.y, 1.0f,1.0f,
        TR.x,0.0f,TR.y, 1.0f,1.0f,
        BR.x,0.0f,BR.y, 1.0f,0.0f,
        BL.x,0.0f,BL.y, 0.0f,0.0f,

    };

	unsigned int indices[6] = {
		0, 1, 2, 2, 3, 0
	};

    for(int i = 0; i < 30; i++)
    {
        vertices[i] = ver[i];
    }
    
	
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Road::draw(GLuint shaderProgram)
{
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
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
