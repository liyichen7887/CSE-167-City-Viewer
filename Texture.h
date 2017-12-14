//
//  Texture.hpp
//  Final Project-water
//
//  Created by Lin Zhou on 12/6/17.
//  Copyright © 2017 Lin Zhou. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <stdio.h>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <vector>

#include "soil.h"


class Texture {
public:
    int width, height;
    GLuint id;    //texture ID
    

    /**
     Creates an empty gl texture
     Set glTexImage2D Params with optional arguments internalFormat, format, type
     Set glTexparameteri settings with optional argument vector<pair<GLenum, GLint>> texParams s.t. Glenum = pname and GLint = param
     Default settings will create an empty RGB texture
     **/
    Texture(
            int width, int height,
            //glTexImage2D Params
            GLint internalFormat = GL_RGB, GLenum format = GL_RGB, GLenum type = GL_UNSIGNED_BYTE,
            //glTexParameteri settings
            std::vector<std::pair<GLenum, GLint>> texParams = {
                std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR),
                std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR),
                std::make_pair(GL_TEXTURE_WRAP_S, GL_REPEAT),
                std::make_pair(GL_TEXTURE_WRAP_T, GL_REPEAT)
            }
            );
    
    /**
     Creates a gl texture from the given path.
     Set glTexImage2D Params with optional arguments internalFormat, format, type
     Set glTexparameteri settings with optional argument vector<pair<GLenum, GLint>> texParams s.t. Glenum = pname and GLint = param
     Default settings will create repeating RGB texture
     **/
    Texture(
            std::string path,
            //glTexImage2D Params
            GLint internalFormat = GL_RGB, GLenum format = GL_RGB, GLenum type = GL_UNSIGNED_BYTE,
            int soilFormat = SOIL_LOAD_RGB,
            //glTexParameteri settings
            std::vector<std::pair<GLenum, GLint>> texParams = {
                std::make_pair(GL_TEXTURE_WRAP_S, GL_REPEAT),
                std::make_pair(GL_TEXTURE_WRAP_T, GL_REPEAT),
                std::make_pair(GL_TEXTURE_MIN_FILTER, GL_LINEAR),
                std::make_pair(GL_TEXTURE_MAG_FILTER, GL_LINEAR)
            }
            );
    
    ~Texture();
    
    GLuint getID();
};
#endif /* Texture_h */
