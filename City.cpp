//
//  City.cpp
//  FinalProject
//
//  Created by Ying Wang on 12/10/17.
//  Copyright © 2017 Ying Wang. All rights reserved.
//

#include <stdio.h>
#include "City.h"
#include "Window.h"

City::City()
{
    length = 112.0f;
    width = 112.0f;
    bigRoadSize = 5.0f;
    smallRoadSize = 2.0f;
    bdInterval = 1.0f;
    
    texture[0] = loadTexture(faceBD);
    texture[1] = loadTexture(faceBD2);
    texture[2] = loadTexture(faceBD3);
    texture[3] = loadTexture(faceBD4);
    texture[4] = loadTexture(faceBD5);
    texture[5] = loadTexture(faceBD6);
    
    roadTex1 = loadTexture(roadT1);
    roadTex2 = loadTexture(roadT2);
    grassTex = loadTexture(grass);
    // block 1
    
    unsigned int blockCount[4];
    blockCount[0] = 0;
    blockCount[1] = 0;
    blockCount[2] = 0;
    blockCount[3] = 0;

    float zz = -50.0f;
    for(int p = 0; p < 3; p ++){
        float xx = -50.0f;
        srand((unsigned)time(NULL));
        for(int q = 0; q < 3; q++){
            if(q == 1 && p == 1){
                createBlock3(xx, zz);
            }
            else{
                unsigned int index = rand() % 4;
                std::cout << "p " << p << "q " << q << " bt " << index << std::endl;
                while((index == 0 && blockCount[0] >= 3) ||
                      (index == 1 && blockCount[1] >= 2) ||
                      (index == 2 && blockCount[2] >= 2) ||
                      (index == 3 && blockCount[3] >= 1))
                {
                    index = rand() % 4;
                }
                if(index == 0){
                    srand((unsigned)time(NULL));
                    createBlock1(xx,zz);
                    blockCount[0]++;
                }
                else if(index == 1){
                    srand((unsigned)time(NULL));
                    if(blockCount[1] == 0)
                        createBlock2(xx,zz, texture[5]);
                    else
                        createBlock2(xx,zz, texture[3]);
                    blockCount[1]++;
                }
                else if(index == 2){
                    srand((unsigned)time(NULL));
                    createBlock4(xx,zz);
                    blockCount[2]++;
                }
                else if(index == 3){
                    srand((unsigned)time(NULL));
                    createBlock5(xx,zz);
                    blockCount[3]++;
                }
            }
           
            xx = xx + 35.0f;
        }
        zz = zz + 35.0f;
    }
    //glm::vec3 rd1Pos = glm::vec3(-50.f+32.5f,0.0f,-50.0f+50.f);
    //glm::vec3 rd2Pos = glm::vec3(-50.f+32.5f+35.0f,0.0f,-50.0f+50.f);
    glm::vec2 TL1 = glm::vec2(30.0f-50.f,0.0f-50.0f);
    glm::vec2 TR1 = glm::vec2(35.0f-50.f,0.0f-50.0f);
    glm::vec2 BL1 = glm::vec2(30.0f-50.f,100.0f-50.0f);
    glm::vec2 BR1 = glm::vec2(35.0f-50.f,100.0f-50.0f);
    
    glm::vec2 TL2 = glm::vec2(30.0f-50.f+35.0f,0.0f-50.0f);
    glm::vec2 TR2 = glm::vec2(35.0f-50.f+35.0f,0.0f-50.0f);
    glm::vec2 BL2 = glm::vec2(30.0f-50.f+35.0f,100.0f-50.0f);
    glm::vec2 BR2 = glm::vec2(35.0f-50.f+35.0f,100.0f-50.0f);
    
    /*
    glm::vec2 TL5 = glm::vec2(30.0f-50.f+35.0f,0.0f-50.0f);
    glm::vec2 TR5 = glm::vec2(35.0f-50.f+35.0f,0.0f-50.0f);
    glm::vec2 BL5 = glm::vec2(30.0f-50.f+35.0f,100.0f-50.0f);
    glm::vec2 BR5 = glm::vec2(35.0f-50.f+35.0f,100.0f-50.0f);
    
    glm::vec2 TL6 = glm::vec2(30.0f-50.f+35.0f,0.0f-50.0f);
    glm::vec2 TR6 = glm::vec2(35.0f-50.f+35.0f,0.0f-50.0f);
    glm::vec2 BL6 = glm::vec2(30.0f-50.f+35.0f,100.0f-50.0f);
    glm::vec2 BR6 = glm::vec2(35.0f-50.f+35.0f,100.0f-50.0f);
    */
    glm::vec2 TL3 = glm::vec2(0.0f-50.0f,35.0f-50.f);
    glm::vec2 TR3 = glm::vec2(0.0f-50.0f,30.0f-50.f);
    glm::vec2 BL3 = glm::vec2(100.0f-50.0f,35.0f-50.f);
    glm::vec2 BR3 = glm::vec2(100.0f-50.0f,30.0f-50.f);
    
    glm::vec2 TL4 = glm::vec2(0.0f-50.0f,35.0f-50.f+35.0f);
    glm::vec2 TR4 = glm::vec2(0.0f-50.0f,30.0f-50.f+35.0f);
    glm::vec2 BL4 = glm::vec2(100.0f-50.0f,35.0f-50.f+35.0f);
    glm::vec2 BR4 = glm::vec2(100.0f-50.0f,30.0f-50.f+35.0f);
    
    glm::vec2 TL5 = glm::vec2(37.0-50.0f,65.0f-50.f);
    glm::vec2 TR5 = glm::vec2(35.0f-50.0f,65.0f-50.f);
    glm::vec2 BL5 = glm::vec2(65.0f-50.0f,37.0f-50.f);
    glm::vec2 BR5 = glm::vec2(65.0f-50.0f,35.0f-50.f);
    
    glm::vec2 TL6 = glm::vec2(35.0f-50.0f,65.0f-50.f);
    glm::vec2 TR6 = glm::vec2(35.0f-50.0f,63.0f-50.f);
    glm::vec2 BL6 = glm::vec2(65.0f-50.0f,35.0f-50.f);
    glm::vec2 BR6 = glm::vec2(65.0f-50.0f,33.0f-50.f);
    
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
    rds.push_back(new Road(TL2,TR2,BL2,BR2, roadTex1));
    rds.push_back(new Road(TL3,TR3,BL3,BR3, roadTex1));
    rds.push_back(new Road(TL4,TR4,BL4,BR4, roadTex1));
    rds.push_back(new Road(TL5,TR5,BL5,BR5, roadTex1));
    rds.push_back(new Road(TL6,TR6,BL6,BR6, roadTex1));
    
}

void City::draw(GLuint shaderProgram)
{
     int count = 0;
    for(auto it = bds.begin();it != bds.end(); ++it)
    {
        //unsigned int texture = (*it)->loadTexture(faceBD);
        
        //if (count/4 == 0)
        //    texture = (*it)->loadTexture(faceBD);
        //else if (count/4 == 1)
            //texture = (*it)->loadTexture(faceBD2);
        (*it)->draw(shaderProgram);
        count ++;
    }
    
    for(auto it = rds.begin();it != rds.end(); ++it)
    {
        (*it)->draw(shaderProgram);
    }
    
}

void City::createBlock1(float posX, float posZ)
{
 
   float z = 0.0f+posZ;

    for(int i = 0; i < 3; i++)
    {
        
         float x = 0.0f+posX;
        srand((unsigned)time(NULL));
        for(int j = 0; j < 3; j++){
            
            
            int rdTexture = rand() % 5;
            float rdHeight = rand() % 8 + 15;
            glm::vec3 bd1Pos = glm::vec3(x+1.75f,0.0f,z+1.75f);
            bds.push_back(new Building(3.5f,3.5f,rdHeight,bd1Pos,0,texture[rdTexture]));
            
            rdTexture = rand() % 5;
            rdHeight = rand() % 8 + 10;
            glm::vec3 bd2Pos = glm::vec3(x+6.25f,0.0f,z+1.75f);
            bds.push_back(new Building(3.5f,3.5f,rdHeight,bd2Pos,0,texture[rdTexture]));
            
            rdTexture = rand() % 5;
            rdHeight = rand() % 8 + 20;
            glm::vec3 bd3Pos = glm::vec3(x+1.75f,0.0f,z+6.25f);
            bds.push_back(new Building(3.5f,3.5f,rdHeight,bd3Pos,0,texture[rdTexture]));
            
            rdTexture = rand() % 5;
            rdHeight = rand() % 8 + 10;
            glm::vec3 bd4Pos = glm::vec3(x+6.25f,0.0f,z+6.25f);
            bds.push_back(new Building(3.5f,3.5f,rdHeight,bd4Pos,0,texture[rdTexture]));
            
            
            glm::vec2 TL1 = glm::vec2(x+3.5f,z);
            glm::vec2 TR1 = glm::vec2(x+4.5f,z);
            glm::vec2 BL1 = glm::vec2(x+3.5f,z+8.0f);
            glm::vec2 BR1 = glm::vec2(x+4.5f,z+8.0f);
            rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
            
            TL1 = glm::vec2(x,z+4.5f);
            TR1 = glm::vec2(x,z+3.5f);
            BL1 = glm::vec2(x+8.0f,z+4.5f);
            BR1 = glm::vec2(x+8.0f,z+3.5f);
            rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
            
            x = x + 11.0f;
        }
        z = z + 11.0f;
    }
    
    glm::vec2 TL1 = glm::vec2(posX+8.0f,posZ);
    glm::vec2 TR1 = glm::vec2(posX+11.0f,posZ);
    glm::vec2 BL1 = glm::vec2(posX+8.0f,posZ+30.0f);
    glm::vec2 BR1 = glm::vec2(posX+11.0f,posZ+30.0f);
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
    
    TL1 = glm::vec2(posX+19.0f,posZ);
    TR1 = glm::vec2(posX+22.0f,posZ);
    BL1 = glm::vec2(posX+19.0f,posZ+30.0f);
    BR1 = glm::vec2(posX+22.0f,posZ+30.0f);
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
    
    TL1 = glm::vec2(posX,posZ+11.0f);
    TR1 = glm::vec2(posX,posZ+8.0f);
    BL1 = glm::vec2(posX+30.0f,posZ+11.0f);
    BR1 = glm::vec2(posX+30.0f,posZ+8.0f);
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
    
    TL1 = glm::vec2(posX,posZ+22.0f);
    TR1 = glm::vec2(posX,posZ+19.0f);
    BL1 = glm::vec2(posX+30.0f,posZ+22.0f);
    BR1 = glm::vec2(posX+30.0f,posZ+19.0f);
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
}


void City::createBlock2(float posX, float posZ,unsigned int tex)
{
    float z = 0.0f+posZ;
    for(int i = 0; i < 2; i++)
    {
    float x = 0.0f+posX;
    
    for(int j = 0; j < 5; j++){
        
        
        
        float rdHeight = rand() % 7 + 4;
        glm::vec3 bd1Pos = glm::vec3(x+2.2f,0.0f,z+7.0f);
        //unsigned int rdTexture = rand() % 4;
        
            bds.push_back(new Building(4.4f,14.0f,rdHeight,bd1Pos,0,tex));

        if(i!=5){
            glm::vec2 TL1 = glm::vec2(x+4.4f,z);
            glm::vec2 TR1 = glm::vec2(x+6.4f,z);
            glm::vec2 BL1 = glm::vec2(x+4.4f,z+14.0f);
            glm::vec2 BR1 = glm::vec2(x+6.4f,z+14.0f);
            rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
        }
        
        x = x + 6.4f;
    }
    z = z + 16.0f;
    }
    glm::vec2 TL1 = glm::vec2(posX,posZ+16.0f);
    glm::vec2 TR1 = glm::vec2(posX,posZ+14.0f);
    glm::vec2 BL1 = glm::vec2(posX+30.0f,posZ+16.0f);
    glm::vec2 BR1 = glm::vec2(posX+30.0f,posZ+14.0f);
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
}

// with triangle
void City::createBlock3(float posX, float posZ)
{
    float x = posX ;
    float z = posZ+ 28.0f;
    float rdHeight;
    for(int i = 0; i<4;i++){
        
        //int rdTexture = rand() % 4;
            rdHeight = rand() % 5 + 20;
            glm::vec3 bd1Pos = glm::vec3(x+5.5f/2,0.0f,z-5.5f/2);
            bds.push_back(new Building(5.5f,5.5f,rdHeight,bd1Pos,1,texture[2]));
            glm::vec3 bd2Pos = glm::vec3(x+5.5f/2+2.0f,0.0f,z-5.5f/2);
            //bds.push_back(new Building(5.5f,5.5f,rdHeight,bd1Pos,2,texture3));
        x =x+7.5f;
        z =z-7.5f;
    }
    x =posX+ 28.0f;
    z = posZ+2.0f;
    
    //for(int i = 0; i<4;i++){
        
     //   rdHeight = rand() % 5 + 20;
     //   glm::vec3 bd1Pos = glm::vec3(x-5.5f/2,0.0f,z+5.5f/2);
     //   bds.push_back(new Building(5.5f,5.5f,rdHeight,bd1Pos,2,texture3));
        
     //   x =x-7.5f;
     //   z =z+7.5f;
    //}
    int rdTexture = rand() % 5;
    rdHeight = rand() % 5 + 10;
    glm::vec3 bd2Pos = glm::vec3(posX+5.5f/2,0.0f,posZ+10.25f);
    bds.push_back(new Building(5.5f,5.0f,rdHeight,bd2Pos,0,texture[rdTexture]));

    rdTexture = rand() % 5;
    //rdHeight = rand() % 5 + 30;
    glm::vec3 bd5Pos = glm::vec3(posX+5.5f/2,0.0f,posZ+10.25f+7.5f);
    bds.push_back(new Building(5.5f,5.0f,rdHeight,bd5Pos,0,texture[rdTexture]));
    
    rdTexture = rand() % 5;
    rdHeight = rand() % 5 + 10;
    glm::vec3 bd3Pos = glm::vec3(posX+7.5f+5.5f/2,0.0f,posZ+5.0f);
    bds.push_back(new Building(5.5f,10.0f,rdHeight,bd3Pos,0,texture[rdTexture]));
    
    rdTexture = rand() % 5;
    rdHeight = rand() % 5 + 10;
    glm::vec3 bd4Pos = glm::vec3(posX+17.5f,0.0f,posZ+2.0f);
    bds.push_back(new Building(5.5f,4.0f,rdHeight,bd4Pos,0,texture[rdTexture]));
    
    glm::vec2 TL1 = glm::vec2(posX+30.0f,posZ+2.0f);
    glm::vec2 TR1 = glm::vec2(posX+2.0f,posZ+30.0f);
    glm::vec2 BL1 = glm::vec2(posX+30.0f,posZ+30.0f);
    glm::vec2 BR1 = glm::vec2(posX+30.0f,posZ+2.0f);
    
    rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex2));
    
    glm::vec2 TL2 = glm::vec2(posX,posZ+28.0f);
    glm::vec2 TR2 = glm::vec2(posX+28.0f,posZ);
    glm::vec2 BL2 = glm::vec2(posX,posZ);
    glm::vec2 BR2 = glm::vec2(posX,posZ+28.0f);
    
    rds.push_back(new Road(TL2,TR2,BL2,BR2, roadTex2));
    
}

void City::createBlock4(float posX, float posZ)
{
    float z = 0.0f+posZ;
    for(int i = 0; i < 4; i++)
    {
        float x = 0.0f+posX;
        
        for(int j = 0; j < 10; j++){
            
            
            
            float rdHeight = rand() % 10 + 8;
            glm::vec3 bd1Pos = glm::vec3(x+2.55f/2.0f,0.0f,z+5.25f/2.0f);
            int rdTexture = rand() % 5;
            bds.push_back(new Building(2.55f,5.25f,rdHeight,bd1Pos,0,texture[rdTexture]));
            
            glm::vec2 TL1 = glm::vec2(x+2.55f,z);
            glm::vec2 TR1 = glm::vec2(x+2.55f+0.5f,z);
            glm::vec2 BL1 = glm::vec2(x+2.55f,z+5.25f);
            glm::vec2 BR1 = glm::vec2(x+2.55f+0.5f,z+5.25f);
            
            rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
            
            
            x = x + 2.55f+0.5f;
        }
        
        
        z = z + 5.25f + 3.0f;
        if(i != 3){
        glm::vec2 TL1 = glm::vec2(posX,z);
        glm::vec2 TR1 = glm::vec2(posX,z-3.0f);
        glm::vec2 BL1 = glm::vec2(posX+30.0f,z);
        glm::vec2 BR1 = glm::vec2(posX+30.0f,z-3.0f);
        
        rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
        }
    }
    
  //  rds.push_back(new Road(TL1,TR1,BL1,BR1, roadTex1));
}

void City::createBlock5(float posX, float posZ)
{
    
    float z = 0.0f+posZ;
    float x = 0.0f+posX;
    for(int i = 0; i < 3; i++)
    {

            glm::vec3 bd1Pos = glm::vec3(x+3.5f*30.0f/9.0f,0.0f,z+(30.0f/9.0f));
            bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
        
            glm::vec3 bd2Pos = glm::vec3(x+3.5f*30.0f/9.0f,0.0f,z+30.f-(30.0f/9.0f));
            bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd2Pos,0,texture[0]));
            x = x + 30.0f/9.0f;
    }
    
    z = 0.0f+posZ;
    x = 0.0f+posX;
    for(int i = 0; i < 3; i++)
    {

        glm::vec3 bd1Pos = glm::vec3(x+(30.0f/9.0f),0.0f,z+3.5f*30.0f/9.0f);
        bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
        
     
        glm::vec3 bd2Pos = glm::vec3(x+30.f-(30.0f/9.0f),0.0f,z+3.5f*30.0f/9.0f);
        bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd2Pos,0,texture[0]));
        z = z + 30.0f/9.0f;
    }
    
    //(3,2)
    glm::vec3 bd1Pos = glm::vec3(posX+(30.0f/9.0f)*2.5f,0.0f,posZ+(30.0f/9.0f)*1.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    //(7,2)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*6.5f,0.0f,posZ+(30.0f/9.0f)*1.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    //(2,3)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*1.5f,0.0f,posZ+(30.0f/9.0f)*2.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    //(8,3)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*7.5f,0.0f,posZ+(30.0f/9.0f)*2.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    
    //(2,7)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*1.5f,0.0f,posZ+(30.0f/9.0f)*6.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    //(8,7)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*7.5f,0.0f,posZ+(30.0f/9.0f)*6.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    //(3,8)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*2.5f,0.0f,posZ+(30.0f/9.0f)*7.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    //(7,8)
    bd1Pos = glm::vec3(posX+(30.0f/9.0f)*6.5f,0.0f,posZ+(30.0f/9.0f)*7.5f);
    bds.push_back(new Building(30.0f/9.0f,30.0f/9.0f,7,bd1Pos,0,texture[0]));
    
        
       /* glm::vec2 TL1 = glm::vec2(posX+(30.0f/9.0f)*2.0f,posZ+(30.0f/9.0f)*2.0f);
        glm::vec2 TR1 = glm::vec2(posX+(30.0f/9.0f)*7.0f,posZ+(30.0f/9.0f)*2.0f);
        glm::vec2 BL1 = glm::vec2(posX+(30.0f/9.0f)*2.0f,posZ+(30.0f/9.0f)*7.0f);
        glm::vec2 BR1 = glm::vec2(posX+(30.0f/9.0f)*7.0f,posZ+(30.0f/9.0f)*7.0f);
        rds.push_back(new Road(TL1,TR1,BL1,BR1, grassTex));
    
        TR1 = glm::vec2(posX+(30.0f/9.0f)*1.0f,posZ+(30.0f/9.0f)*3.0f);
        BR1 = glm::vec2(posX+(30.0f/9.0f)*2.0f,posZ+(30.0f/9.0f)*3.0f);
        TL1 = glm::vec2(posX+(30.0f/9.0f)*1.0f,posZ+(30.0f/9.0f)*6.0f);
        BL1 = glm::vec2(posX+(30.0f/9.0f)*2.0f,posZ+(30.0f/9.0f)*6.0f);
        rds.push_back(new Road(TL1,TR1,BL1,BR1, grassTex));
    
        TR1 = glm::vec2(posX+(30.0f/9.0f)*7.0f,posZ+(30.0f/9.0f)*3.0f);
        BR1 = glm::vec2(posX+(30.0f/9.0f)*8.0f,posZ+(30.0f/9.0f)*3.0f);
        TL1 = glm::vec2(posX+(30.0f/9.0f)*7.0f,posZ+(30.0f/9.0f)*6.0f);
        BL1 = glm::vec2(posX+(30.0f/9.0f)*8.0f,posZ+(30.0f/9.0f)*6.0f);
        rds.push_back(new Road(TL1,TR1,BL1,BR1, grassTex));
    
        TR1 = glm::vec2(posX+(30.0f/9.0f)*3.0f,posZ+(30.0f/9.0f)*1.0f);
        BR1 = glm::vec2(posX+(30.0f/9.0f)*6.0f,posZ+(30.0f/9.0f)*1.0f);
        TL1 = glm::vec2(posX+(30.0f/9.0f)*3.0f,posZ+(30.0f/9.0f)*2.0f);
        BL1 = glm::vec2(posX+(30.0f/9.0f)*6.0f,posZ+(30.0f/9.0f)*2.0f);
        rds.push_back(new Road(TL1,TR1,BL1,BR1, grassTex));
    
        TR1 = glm::vec2(posX+(30.0f/9.0f)*3.0f,posZ+(30.0f/9.0f)*7.0f);
        BR1 = glm::vec2(posX+(30.0f/9.0f)*6.0f,posZ+(30.0f/9.0f)*7.0f);
        TL1 = glm::vec2(posX+(30.0f/9.0f)*3.0f,posZ+(30.0f/9.0f)*8.0f);
        BL1 = glm::vec2(posX+(30.0f/9.0f)*6.0f,posZ+(30.0f/9.0f)*8.0f);
        rds.push_back(new Road(TL1,TR1,BL1,BR1, grassTex));
        */
    glm::vec2 TL1 = glm::vec2(posX,posZ);
    glm::vec2 TR1 = glm::vec2(posX+30.0f,posZ);
    glm::vec2 BL1 = glm::vec2(posX,posZ+30.0f);
    glm::vec2 BR1 = glm::vec2(posX+30.0f,posZ+30.0f);
    rds.push_back(new Road(TL1,TR1,BL1,BR1, grassTex));
    
}



unsigned int City::loadTexture(std::string path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    //unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	unsigned char *data = SOIL_load_image(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        //stbi_image_free(data);
		SOIL_free_image_data(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        //stbi_image_free(data);
		SOIL_free_image_data(data);
    }
    
    return textureID;
}



