//
//  Water.cpp
//  Final Project-water
//
//  Created by Lin Zhou on 12/6/17.
//  Copyright © 2017 Lin Zhou. All rights reserved.
//

#include "Water.h"

Water::Water(){

    bind();
    initFB();
    
    waterdudv = new Texture("waterDUDV.png");
}

Water::Water(GLint width, GLint height){
    //generate vertices and indices
    
    int l = floor(-width/2), r = floor(width / 2), u = floor(-height / 2), d = floor(height / 2);
    vertices.clear();
    indices.clear();
    
    //generate vertices
    for (int h = floor(-height / 2); h < floor(height / 2); h++) {
        for (int w = floor(-width / 2); w < floor(width / 2); w++) {
            vertices.push_back(w);
            vertices.push_back(SEA_LEVEL);
            vertices.push_back(h);

        }
    }
    
    //generate indices
    for (int h = 0; h < height - 1; h++) {
        for (int w = 0; w < width - 1; w++) {
            indices.push_back(h*width + w);
            indices.push_back((h + 1)*width + w);
            indices.push_back((h + 1)*width + (w + 1));
            
            indices.push_back((h + 1)*width + (w + 1));
            indices.push_back(h*width + (w + 1));
            indices.push_back(h*width + w);
        }
    }
    this->width = width;
    this->height = height;
    
    bind();
    initFB();
    
    waterdudv = new Texture("waterDUDV.png");
}

Water::~Water(){

}

void Water::bind(){
    // Create array object and buffers. Remember to delete your buffers when the object is destroyed!
    glGenVertexArrays(1, &VAO);
    //vertices
    glGenBuffers(1, &VBO);
    //ebo
    glGenBuffers(1, &EBO);
    
    // Bind the Vertex Array Object (VAO) first, then bind the associated buffers to it.
    // Consider the VAO as a container for all your buffers.
    glBindVertexArray(VAO);
    
    // Now bind a VBO to it as a GL_ARRAY_BUFFER. The GL_ARRAY_BUFFER is an array containing relevant data to what
    // you want to draw, such as vertices, normals, colors, etc.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData populates the most recently bound buffer with data starting at the 3rd argument and ending after
    // the 2nd argument number of indices. How does OpenGL know how long an index spans? Go to glVertexAttribPointer.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &(vertices[0]), GL_STATIC_DRAW);
    // Enable the usage of layout location 0 (check the vertex shader to see what this is)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
                          3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
                          GL_FLOAT, // What type these components are
                          GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
                          3*sizeof(GLfloat), // Offset between consecutive indices. Since each of our vertices has 3 floats, they should have the size of 3 floats in between
                          (GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

    // We've sent the vertex data over to OpenGL, but there's still something missing.
    // In what order should it draw those vertices? That's why we'll need a GL_ELEMENT_ARRAY_BUFFER for this.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indices.size(), &indices[0], GL_STATIC_DRAW);
    
    // Unbind the currently bound buffer so that we don't accidentally make unwanted changes to it.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the VAO now so we don't accidentally tamper with it.
    // NOTE: You must NEVER unbind the element array buffer associated with a VAO!
    glBindVertexArray(0);
}

void Water::initFB(){
    
    //reflection
    glGenFramebuffers(1, &this->reflectionFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->reflectionFrameBuffer);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    
    //texture
    
//    glGenTextures(1, &reflectionTexture);
//    glBindTexture(GL_TEXTURE_2D, reflectionTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, REFLECTION_WIDTH, REFLECTION_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflectionTexture, 0);
//    glBindTexture(GL_TEXTURE_2D, 0);
    
    reflecTex = new Texture(REFLECTION_WIDTH, REFLECTION_HEIGHT);
    reflectionTexture = reflecTex->id;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflectionTexture, 0);

    //depth buffer
    glGenRenderbuffers(1, &reflectionDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, reflectionDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFLECTION_WIDTH, REFLECTION_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflectionDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Water::initFrameBuffers - Failed to create reflection frame buffer" << std::endl;
    //unbind all
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    

    //refraction
    glGenFramebuffers(1, &this->refractionFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, this->refractionFrameBuffer);
    //attach color buffer
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    
    //texture
    /*
    glGenTextures(1, &refractionTexture);
    glBindTexture(GL_TEXTURE_2D, refractionTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionTexture, 0);*/
    
    refracTex = new Texture(REFRACTION_WIDTH, REFRACTION_HEIGHT);
    refractionTexture = refracTex->id;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionTexture, 0);
    
    //depth texture
    refracDT= new Texture(REFRACTION_WIDTH, REFRACTION_HEIGHT, GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT);
    refractionDepthTexture = refracDT->id;
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, refractionDepthTexture, 0);
     /*
    glGenTextures(1, &refractionDepthTexture);
    glBindTexture(GL_TEXTURE_2D, refractionDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, REFRACTION_WIDTH, REFRACTION_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refractionDepthTexture, 0);*/
    
    //depth buffer
    
//    glGenRenderbuffers(1, &refractionDepthBuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, refractionDepthBuffer);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, REFRACTION_WIDTH, REFRACTION_HEIGHT);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, refractionDepthBuffer);
//    
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, refractionDepthBuffer);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "Water::initFrameBuffers - Failed to create refraction frame buffer with enum "<< glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Water::bindFB(GLuint fb_id){
    GLuint buffer;
    GLuint texture;
    GLuint w, h;
    glBindTexture(GL_TEXTURE_2D, 0);
    if(fb_id == REFLECTION){
        w = REFLECTION_WIDTH;
        h = REFLECTION_HEIGHT;
        buffer = reflectionFrameBuffer;
        

        
//        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, reflectionTexture);
        
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, reflectionTexture);
//
    }
    else {
        w = REFRACTION_WIDTH;
        h = REFRACTION_HEIGHT;
        buffer = refractionFrameBuffer;
        

        
//        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, refractionTexture);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, buffer);
    glViewport(0, 0, w, h);
}

void Water::unbindFB(){
    //unbind texture
//    glBindTexture((GL_TEXTURE_2D), 0);
//    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Window::width, Window::height);
}

void Water::SendDataToShader(GLuint shaderProgram){
    glUniform1i(glGetUniformLocation(shaderProgram, "reflectionTexture"), REFLECTION);
    glUniform1i(glGetUniformLocation(shaderProgram, "refractionTexture"), REFRACTION);
    glUniform1i(glGetUniformLocation(shaderProgram, "dudv"), DUDV);
    
    uProjection = glGetUniformLocation(shaderProgram, "projection");
    uModelView = glGetUniformLocation(shaderProgram, "modelview");
    uModel = glGetUniformLocation(shaderProgram, "model");
    
    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
    glm::mat4 modelview = Window::V;
    glUniformMatrix4fv(uModelView, 1, GL_FALSE, &modelview[0][0]);
    glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
    
    //update move factor with time
    if (first_draw) {
        lastTime = glfwGetTime();
        moveFactor += WAVE_SPEED * lastTime;
        first_draw = false;
    }
    else {
        double curTime = glfwGetTime();
        moveFactor += WAVE_SPEED * (curTime - lastTime);
        lastTime = curTime;
    }
    moveFactor = fmod(moveFactor, 1.0f);
    glUniform1f(glGetUniformLocation(shaderProgram, "moveFactor"), moveFactor);
}

void Water::setActiveTexture(){
    //bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflectionTexture);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refractionTexture);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, waterdudv->id);
}

void Water::unsetActiveTexture(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,0);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Water::draw(GLuint shaderProgram){
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(true);
//
//    setActiveTexture();
    SendDataToShader(shaderProgram);
     setActiveTexture();
    
    // Calculate the combination of the model and view (camera inverse) matrices
	 glm::mat4 modelview = Window::V;
    // We need to calculate this because modern OpenGL does not keep track of any matrix other than the viewport (D)
    // Consequently, we need to forward the projection, view, and model matrices to the shader programs
    // Get the location of the uniform variables "projection" and "modelview"
//    uProjection = glGetUniformLocation(shaderProgram, "projection");
//    uModelView = glGetUniformLocation(shaderProgram, "modelview");
//    uModel = glGetUniformLocation(shaderProgram, "model");
//
//    glUniformMatrix4fv(uProjection, 1, GL_FALSE, &Window::P[0][0]);
//    glUniformMatrix4fv(uModelView, 1, GL_FALSE, &modelview[0][0]);
//    glUniformMatrix4fv(uModel, 1, GL_FALSE, &toWorld[0][0]);
    // Now draw the object. We simply need to bind the VAO associated with it.
    
    glBindVertexArray(VAO);
    // Tell OpenGL to draw with triangles
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    // Unbind the VAO when we're done so we don't accidentally draw extra stuff or tamper with its bound buffers
    glBindVertexArray(0);
    unsetActiveTexture();
    glDisableVertexAttribArray(0);
    glDisable(GL_BLEND);
}
