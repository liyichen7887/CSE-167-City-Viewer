//
//  Water.hpp
//  Final Project-water
//
//  Created by Lin Zhou on 12/6/17.
//  Copyright © 2017 Lin Zhou. All rights reserved.
//

#ifndef Water_h
#define Water_h

#include <stdio.h>
#include <vector>
#include "Window.h"
#include "Texture.h"


#define SEA_LEVEL 0.01f
#define REFLECTION_WIDTH 820
#define REFLECTION_HEIGHT 180
#define REFRACTION_WIDTH 1280
#define REFRACTION_HEIGHT 720
#define SEA_LEVEL -0.1f
#define WAVE_SPEED 0.03

class Water{
public:
    GLuint VAO,VBO,EBO;
    GLuint uProjection, uModelView, uModel;
    glm::mat4 toWorld = glm::mat4(1.0f);
    
    std::vector<GLfloat> vertices =
    {   -10, -5, 10,
        10, -5, -10,
        -10, -5, -10,
        
        -10, -5, 10,
        10, -5, 10,
        10, -5, -10
    
    };
    
    /*
    { -10, -10, -10,
        10, -10, 10,
        10, -10, -10,
        -10, -10, 10 };*/
    std::vector<GLint> indices ={
        0, 1, 2 ,
       3,4,5
    };
    
    void bind();
    
//public:
    GLint width, height;
    
    GLuint reflectionFrameBuffer, refractionFrameBuffer;
    GLuint reflectionTexture, refractionTexture;
    GLuint reflectionDepthBuffer, refractionDepthBuffer;
    GLuint refractionDepthTexture;
    
    Texture* reflecDT;
    Texture* reflecTex;
    Texture* refracDT;
    Texture* refracTex;
    Texture* waterdudv;
    
    float moveFactor = 0.0f;
    bool first_draw = true;
    double lastTime;
    
    Water();
    Water(GLint width, GLint height);
    ~Water();
    
    enum{ REFLECTION = 0, REFRACTION = 1, DUDV = 2};
    

    //initialize reflection and refraction frame buffer objects
    void initFB();
    void initTexture();
    void initDB();
    
    void bindFB(GLuint fb);
    void unbindFB();
    
    void setActiveTexture();
    void unsetActiveTexture();
    
    void draw(GLuint shaderProgram);
    
    void SendDataToShader(GLuint sp);
    
    void cleanUp();
    
    
    
};

#endif /* Water_hpp */
