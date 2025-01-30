#ifndef BUILDINGRIGHT_H
#define BUILDINGRIGHT_H

#include <GL/glut.h>

// Declare the texture array globally
extern GLuint buildingRightTextures[6];

// Declare texture-loading function
//void loadbuildingRightTextures();

// Declare the pier functions

void loadBuildingRightTextures();
void cube_buildingR();
void mainWalls_buildingR();
void floor_buildingR();
void roof_buildingR();
void box1_buildingR();
void doorFrames_buildingR();
void doorPanel_buildingR();
void doors_buildingR();
void sideWindow_buildingR();
void buildingR();

#endif

