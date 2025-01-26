#ifndef JETBRIDGE_H
#define JETBRIDGE_H

#include <GL/glut.h>

// Declare the texture array globally
extern GLuint jetBridgeTextures[6]; 

// Declare texture-loading function
void loadJetBridgeTextures();

// Declare the jet bridge functions
void container_jetBridge();
void containerGlass_jetBridge();
void containerConnector_jetBridge();
void containerBigger_jetBridge();
void containerGlassBigger_jetBridge();
void stands_jetBridge();
void standBase_jetBridge();
void completeStand_jetBridge();
void standTire_jetBridge();
void rotator_jetBridge();
void jetBridge();

#endif

