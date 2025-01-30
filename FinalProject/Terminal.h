#ifndef TERMINAL_H
#define TERMINAL_H

#include <GL/glut.h>

// Declare the texture array globally
extern GLuint terminalTextures[6];
extern GLuint textureImage;

// Declare texture-loading function
//void loadTerminalTextures();

// Declare the pier functions
void loadTerminalTextures();
void singleWallSide_terminal();
void cube_terminal();
void concreteWindowFramesVertical_terminal();
void concreteWindowFramesHorizontal_terminal();
void singleSide_terminal();
void walls_terminal();
void floorRoof_terminal();
void doorFrames_terminal();
void doorPanel_terminal();
void doors_terminal();
void concreteSupporters_terminal();
void nameBoard_terminal();
void terminal();

#endif
