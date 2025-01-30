#ifndef PIER_H
#define PIER_H

#include <GL/glut.h>

// Declare the texture array globally
extern GLuint pierTextures[6];

// Declare texture-loading function
//void loadPierTextures();

// Declare the pier functions
void loadPierTextures();
void wallSegment_pier();
void wallSideSegment_pier();
void singleWindow_pier();
void allWindowsOneSide_pier();
void windows_pier();
void roofSegment_pier();
void completeRoofSegment_pier();
void scaledRoofSegment_pier();
void floorSegment_pier();
void single_pier();
void pier();
void twoPiers();

#endif
