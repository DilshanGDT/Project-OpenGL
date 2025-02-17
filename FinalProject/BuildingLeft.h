#ifndef BUILDINGLEFT_H
#define BUILDINGLEFT_H

#include <GL/glut.h>

// Declare the texture array globally
extern GLuint buildingLeftTextures[3];

// Declare texture-loading function
//void loadPierTextures();

// Declare the pier functions
void loadBuildingLeftTextures();
void cube_buildingL();
void longerSupportBuilding_buildingL();
void normalBuilding_buildingL();
void supportBuilding_buildingL();
void longerBuilding_buildingL();
void floor_buildingL();
void buildingL();

#endif
