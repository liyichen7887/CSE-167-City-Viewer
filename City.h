//
//  City.h
//  FinalProject
//
//  Created by Ying Wang on 12/10/17.
//  Copyright © 2017 Ying Wang. All rights reserved.
//

#ifndef City_h
#define City_h


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
#include <list>
#include "Building.h"
#include "Road.h"
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>  
#include "soil.h"

class City
{
public:
    std::vector<Building*> bds;
    std::vector<Road *> rds;
    float length;
    float width;
    float bigRoadSize;
    float smallRoadSize;
    float bdInterval;
	std::string faceBD = "building1.jpeg";
	std::string faceBD2 = "building1.jpeg";
	std::string faceBD3 = "building8.jpg";
	std::string faceBD4 = "building9.jpg";
	std::string faceBD5 = "building11.jpg";
	std::string faceBD6 = "building7.jpeg";
	std::string roadT1 = "road1.jpeg";
	std::string roadT2 = "grass.jpg";
	std::string grass = "grass2.jpg";
    City();
    void draw(GLuint shaderProgram);
    void createBlock1(float posX, float posZ);
    void createBlock2(float posX, float posZ,unsigned int tex);
    void createBlock3(float posX, float posZ);
    void createBlock4(float posX, float posZ);
    void createBlock5(float posX, float posZ);
    unsigned int texture[6];
    unsigned int roadTex1;
    unsigned int roadTex2;
    unsigned int grassTex;
    unsigned int loadTexture(std::string path);
};

#endif /* City_h */
