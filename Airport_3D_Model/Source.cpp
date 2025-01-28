#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL2.h>

#include "JetBridge.h"	// JetBridge class

// Variables to move the camera
GLfloat camXInit = 0.0;		GLfloat camYInit = 0.0;		GLfloat camZInit = 0.0;
GLfloat camX = camXInit;	GLfloat camY = camYInit;	GLfloat camZ = camZInit;

// Variables to move the scene
GLfloat sceRXInit = 0.0;	GLfloat sceRYInit = 0.0;	GLfloat sceRZInit = 0.0;
GLfloat sceTXInit = 0.0;	GLfloat sceTYInit = 0.0;	GLfloat sceTZInit = 0.0;

GLfloat sceRX = sceRXInit;	GLfloat sceRY = sceRYInit;	GLfloat sceRZ = sceRZInit;
GLfloat sceTX = sceTXInit;	GLfloat sceTY = sceTYInit;	GLfloat sceTZ = sceTZInit;

// Variables to move the looking position
GLfloat lookX = 0.0;		GLfloat lookY = 0.0;		GLfloat lookZ = 0.0;

// Variables to move the objects
GLfloat objRX = 0.0;		GLfloat objRY = 0.0;		GLfloat objRZ = 0.0;
GLfloat objTX = 0.0;		GLfloat objTY = 0.0;		GLfloat objTZ = 0.0;

static float dRot;

// Grid and coordinate axes for better visualization
void drawGrid()
{
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -80; line <= 80; line += step)
	{
		glVertex3f(line, -0.4, 80);
		glVertex3f(line, -0.4, -80);

		glVertex3f(80, -0.4, line);
		glVertex3f(-80, -0.4, line);
	}
	glEnd();
}

void drawAxes()
{

	glBegin(GL_LINES);

	glLineWidth(1.5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -200, 0);
	glVertex3f(0, 200, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);

	glEnd();
}

GLuint textureImage;

// Read the image to texture image
void loadTextures()
{
	// SOIL_load
	textureImage = SOIL_load_OGL_texture(
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Project-OpenGL/Airport_3D_Model/images/jetbridge/containerTexture.jpg",  // Replace with the path to your texture file
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);

	if (!textureImage) {
		printf("Texture loading failed: %s\n", SOIL_last_result());
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	loadTextures();
	// loadJetBridgeTextures(); // Load JetBridge textures
}

// Intensity of the light source
void light0(GLfloat offset, GLfloat posOffset)
{
	// (r, g, b, opacity)
	GLfloat l0amb[] = { 0.2 + offset, 0.2 + offset, 0.2 + offset, 1.0 };
	GLfloat l0diff[] = { 0.8 - offset, 0.8 - offset, 0.8 - offset, 1.0 };
	GLfloat l0spec[] = { 1.0, 1.0, 1.0, 1.0 };

	// Light source position : (x, y, z, type_of_the_light_source)
	GLfloat l0pos[] = { -10 + posOffset, 1.0, -0.5, 1.0 };

	// Set the illumination or intensity (ambiant, diffusion, specular)
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glGetLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
	glGetLightfv(GL_LIGHT0, GL_SPECULAR, l0spec);

	// Set the Light source position
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);
}

// Set Properties of light sources and materials
void setLightingandShading()
{
	// Enable light
	glEnable(GL_LIGHTING); // Tell opengl that we are setting custom lighting

	// Create light
	// Define the illumination or intensity of the light source
	GLfloat l0amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat l0diff[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat l0spec[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat l0pos[] = { -10, 1.0, -0.5, 1.0 };

	// Set the illumination or intensity (ambiant, diffusion, specular)
	glGetLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glGetLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
	glGetLightfv(GL_LIGHT0, GL_SPECULAR, l0spec);

	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

	// Seting surface colors and properties
	// Enable glColor function apply its color
	glEnable(GL_COLOR_MATERIAL);
	// glShadeModel(GL_SMOOTH);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	GLfloat specRef[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);

	GLint shiness = 128;
	glMateriali(GL_FRONT, GL_SHININESS, shiness);
}

// Drawing Function Goes Here

// terminal

void singleWallSide_terminal() {

	// front wall
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	//glTranslated(-10, 0, 0);
	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 4, 0);
	glVertex3f(-10, 4, 0);

	glEnd();
	glPopMatrix();
}

void cube() {
	glBegin(GL_QUADS);

	// Front face (z = 0.5)
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face (z = -0.5)
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	// Left face (x = -0.5)
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Right face (x = 0.5)
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	// Top face (y = 0.5)
	glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// Bottom face (y = -0.5)
	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();
}

void concreteWindowFramesVertical_terminal() {
	glPushMatrix();
	glScaled(0.1, 4, 0.25);
	glTranslated(0, 0.5, 0);
	cube();
	glPopMatrix();

	int j = 10;
	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glScaled(0.1, 4, 0.25);
		glTranslated(0 - j, 0.5, 0);
		j += 10;
		cube();
		glPopMatrix();
	}

	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glScaled(0.1, 4, 0.25);
		glTranslated(-100 + j, 0.5, 0);
		j += 10;
		cube();
		glPopMatrix();
	}
	
}

void concreteWindowFramesHorizontal_terminal() {
	glPushMatrix();
	glScaled(20, 0.1, 0.25);
	glTranslated(0, 1, 0);
	cube();
	glPopMatrix();

	int j = 13;
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glScaled(20, 0.1, 0.25);
		glTranslated(0, 1 + j, 0);
		cube();
		j += 13;
		glPopMatrix();
	}
}

void singleSide_terminal() {

	glPushMatrix();
	singleWallSide_terminal();
	glPopMatrix();

	glPushMatrix();
	concreteWindowFramesVertical_terminal();
	glPopMatrix();

	glPushMatrix();
	concreteWindowFramesHorizontal_terminal();
	glPopMatrix();
}

void walls_terminal() {
	singleSide_terminal();

	glPushMatrix();
	glTranslated(0, 0, -15);
	singleSide_terminal();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10, 0, -7.5);
	glRotated(90, 0, 1, 0);
	glScaled(0.76, 1, 1);
	singleSide_terminal();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-10, 0, -7.5);
	glRotated(90, 0, 1, 0);
	glScaled(0.76, 1, 1);
	singleSide_terminal();
	glPopMatrix();
}

void floorRoof_terminal() {
	// roof
	glPushMatrix();
	glTranslated(0, 4.15, -6);
	glScaled(22, 0.2, 22);
	cube();
	glPopMatrix();

	//floor
	glPushMatrix();
	glTranslated(0, -0.05, -7);
	glScaled(22, 0.2, 20);
	cube();
	glPopMatrix();
}

void doorFrames_terminal() {
	// top
	glPushMatrix();
	glTranslated(0, 0, 5);
	glScaled(3, 0.2, 1);
	cube();
	glPopMatrix();

	// left
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(-0.65, -1.5, 5);
	glScaled(1.5, 0.2, 1);
	cube();
	glPopMatrix();

	// right
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(-0.65, 1.5, 5);
	glScaled(1.5, 0.2, 1);
	cube();
	glPopMatrix();
}

void doorPanel_terminal() {
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	glTranslated(0, -1.5, 5.2);
	glScaled(1.5, 1.4, 0); 
	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(-1, 1, 0);

	glEnd();
	glPopMatrix();
}

void doors_terminal() {

	//door 1
	glPushMatrix();
	glTranslated(-5, 1.5, -4.5);
	doorFrames_terminal();
	doorPanel_terminal();
	glPopMatrix();

	//door 2
	glPushMatrix();
	glTranslated(5, 1.5, -4.5);
	doorFrames_terminal();
	doorPanel_terminal();
	glPopMatrix();

	//door back
	glPushMatrix();
	glTranslated(0, 2, -20.5);
	glScaled(1.5, 1.5, 1);
	doorFrames_terminal();
	doorPanel_terminal();
	glPopMatrix();
}

void concreteSupporters_terminal() {

	glPushMatrix();
	GLUquadric* quad = gluNewQuadric();

	int j = 0;
	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureImage);
		gluQuadricTexture(quad, GL_TRUE);
		glTranslatef(j, 0, 1.7);
		glRotatef(-90, 1, 0, 0);
		glRotatef(12, 1, 0, 0);
		gluCylinder(quad, 0.1, 0.06, 4.3, 30, 6);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		j += 2;
	}

	int k = 0;
	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureImage);
		gluQuadricTexture(quad, GL_TRUE);
		glTranslatef(k, 0, 1.7);
		glRotatef(-90, 1, 0, 0);
		glRotatef(12, 1, 0, 0);
		gluCylinder(quad, 0.1, 0.06, 4.3, 30, 6);
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		k -= 2;
	}

	gluDeleteQuadric(quad);
	glPopMatrix();
}

void terminal() {

	walls_terminal();
	floorRoof_terminal();
	doors_terminal();
	concreteSupporters_terminal();
}

// building right

void mainWalls_buildingR() {
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	glTranslated(-4.8, 0, -3);
	glBegin(GL_QUADS);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(15, 0, 0);
	glVertex3f(25, 0, 0);
	glVertex3f(25, 3.5, 0);
	glVertex3f(15, 3.5, 0);

	glColor3f(0.5f, 0.7f, 0.5f);
	glVertex3f(15, 0, 0);
	glVertex3f(15, 0, -15);
	glVertex3f(15, 3.5, -15);
	glVertex3f(15, 3.5, 0);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(15, 0, -15);
	glVertex3f(35, 0, -15);
	glVertex3f(35, 3.5, -15);
	glVertex3f(15, 3.5, -15);

	glColor3f(0.5f, 0.7f, 0.5f);
	glVertex3f(25, 0, 0);
	glVertex3f(35, 0, -15);
	glVertex3f(35, 3.5, -15);
	glVertex3f(25, 3.5, 0);

	glEnd();
	glPopMatrix();
}

void floor_buildingR() {
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	glTranslated(-10.8, 0.05, -1);
	glScaled(1.3, 1, 1.3);
	glBegin(GL_QUADS);

	//top
	glColor3f(0.6f, 0.5f, 0.5f);
	glVertex3f(15, 0, 0);
	glVertex3f(25, 0, 0);
	glVertex3f(35, 0, -15);
	glVertex3f(15, 0, -15);

	//bottom
	glColor3f(0.6f, 0.5f, 0.5f);
	glVertex3f(15, -0.2, 0);
	glVertex3f(25, -0.2, 0);
	glVertex3f(35, -0.2, -15);
	glVertex3f(15, -0.2, -15);

	//sides
	glColor3f(0.6f, 0.6f, 0.8f);
	glVertex3f(15, 0, 0);
	glVertex3f(25, 0, 0);
	glVertex3f(15, -0.2, 0);
	glVertex3f(25, -0.2, 0);

	glColor3f(0.6f, 0.6f, 0.8f);
	glVertex3f(25, 0, 0);
	glVertex3f(35, 0, -15);
	glVertex3f(35, -0.2, -15);
	glVertex3f(25, -0.2, 0);

	glColor3f(0.6f, 0.6f, 0.8f);
	glVertex3f(15, 0, -15);
	glVertex3f(35, 0, -15);
	glVertex3f(35, -0.2, -15);
	glVertex3f(15, -0.2, -15);

	glEnd();
	glPopMatrix();
}

void roof_buildingR() {
	glPushMatrix();
	glColor3f(1, 0.4, 0.5);
	glScaled(0.9, 1, 0.8);
	glTranslated(1, 3.5, -2);
	floor_buildingR();
	glPopMatrix();
}

void box1_buildingR() {
	glPushMatrix();
	glTranslated(12, 1, -2.5);
	glScaled(4, 2, 2);
	cube();
	glPopMatrix();
}

void doors_buildingR() {
	//door 1
	glPushMatrix();
	glTranslated(18, 1.5, -7.5);
	doorFrames_terminal();
	doorPanel_terminal();
	glPopMatrix();

	//door back
	glPushMatrix();
	glTranslated(25, 1.5, -23.3);
	doorFrames_terminal();
	doorPanel_terminal();
	glPopMatrix();
}

void sideWindow_buildingR() {

	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	glTranslated(9.7, 1, -6);
	glScaled(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);

	glColor3f(0.2f, 0.2f, 0.2f);
	glVertex3f(25.01, 0, 0);
	glVertex3f(35.01, 0, -15);
	glVertex3f(35.01, 3.5, -15);
	glVertex3f(25.01, 3.5, 0);

	glEnd();
	glPopMatrix();
}

void buildingR() {
	mainWalls_buildingR();
	floor_buildingR();
	roof_buildingR();
	box1_buildingR();
	doors_buildingR();
	sideWindow_buildingR();
}

// building left

void longerSupportBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-16, 1, -11);
	glScaled(12, 2, 3);
	cube();
	glPopMatrix();
}

void normalBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-19, 1.5, -5);
	glScaled(12, 3, 10);
	cube();
	glPopMatrix();
}

void supportBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-25, 1, -5);
	glScaled(12, 2, 8);
	cube();
	glPopMatrix();
}

void longerBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-22, 1, -15);
	glScaled(18, 2, 2);
	cube();
	glPopMatrix();
}

void floor_buildingL() {
	glPushMatrix();
	glTranslated(-22, -0.05, -8);
	glScaled(22, 0.2, 20);
	cube();
	glPopMatrix();
}

void buildingL() {
	longerSupportBuilding_buildingL();
	normalBuilding_buildingL();
	supportBuilding_buildingL();
	longerBuilding_buildingL();
	floor_buildingL();
}

// pier

void wallSegment_pier() {
	// front wall
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	//glTranslated(-10, 0, 0);
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-10, 0, 0);
	glVertex3f(-10, 2.5, 0);
	glVertex3f(-10, 2.5, -3);
	glVertex3f(-10, 0, -3);

	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-10, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2.5, 0);
	glVertex3f(-10, 2.5, 0);

	glColor3f(0.6f, 0.6f, 0.5f);
	glVertex3f(0, 0, 0);
	glVertex3f(2.5, 0, 3);
	glVertex3f(2.5, 2.5, 3);
	glVertex3f(0, 2.5, 0);

	glColor3f(0.7f, 0.5f, 0.7f);
	glVertex3f(2.5, 0, 3);
	glVertex3f(5, 0, 0);
	glVertex3f(5, 2.5, 0);
	glVertex3f(2.5, 2.5, 3);

	glColor3f(0.7f, 0.6f, 0.7f);
	glVertex3f(5, 0, 0);
	glVertex3f(15, 0, 0);
	glVertex3f(15, 2.5, 0);
	glVertex3f(5, 2.5, 0);

	glEnd();
	glPopMatrix();
}

void wallSideSegment_pier() {
	glPushMatrix();
	wallSegment_pier();
	glPopMatrix();

	glPushMatrix();
	glRotated(180, 0, 1, 0);
	glTranslated(-5, 0, 3);
	wallSegment_pier();
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(15, 0, 0);
	wallSegment_pier();
	glPopMatrix();*/

	/*glPushMatrix();
	glTranslated(30, 0, 0);
	wallSegment_pier();
	glPopMatrix();*/
}

void roofSegment_pier() {
	glPushMatrix();
	//glRotated(90, 0, 1, 0);
	//glTranslated(-10, 0, 0);
	glBegin(GL_QUADS);

	// rectangle
	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f(-10, 2.5, 0);
	glVertex3f(15, 2.5, 0);
	glVertex3f(15, 2.5, -3);
	glVertex3f(-10, 2.5, -3);

	glEnd();

	// two triangles
	glBegin(GL_TRIANGLES);

	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f(0, 2.5, 0);
	glVertex3f(2.5, 2.5, 3);
	glVertex3f(5, 2.5, 0);

	glColor3f(0.0f, 0.5f, 0.5f);
	glVertex3f(0, 2.5, -3);
	glVertex3f(2.5, 2.5, -6);
	glVertex3f(5, 2.5, -3);

	glEnd();

	glPopMatrix();
}

void completeRoofSegment_pier() {

	glPushMatrix();
	roofSegment_pier();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.24, 0);
	roofSegment_pier();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2.5, 0);
	glScaled(1, 0.1, 1);
	wallSideSegment_pier();
	glPopMatrix();
}

void scaledRoofSegment_pier() {
	glPushMatrix();
	glTranslated(0, 0, 0.5);
	glScaled(1.1, 1, 1.4);
	completeRoofSegment_pier();
	glPopMatrix();
}

void floorSegment_pier() {
	glPushMatrix();
	glTranslated(0, -2.75, 0);
	glScaled(0.95, 1, 0.9);
	scaledRoofSegment_pier();
	glPopMatrix();
}

void single_pier() {
	wallSideSegment_pier();
	scaledRoofSegment_pier();
	floorSegment_pier();
}

void pier() {
	glPushMatrix();
	single_pier();
	glPopMatrix();

	glPushMatrix();
	glTranslated(25, 0, 0);
	single_pier();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, 0, 0);
	single_pier();
	glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// Camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 1.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	// Draw a grid on the xz plane
	glColor3f(1, 1, 1);
	drawGrid();

	// draw the three axes
	drawAxes();

	// setLightingandShading();

	// Drawing
	//jetBridge();

	//terminal();
	//buildingR();
	//buildingL();
	pier();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Define the Perspective projection frustum
	// (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
	gluPerspective(120.0, aspect_ratio, 1.0, 100.0);
}

void keyboardSpecial(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		camY += 0.5;

	if (key == GLUT_KEY_DOWN)
		camY -= 0.5;

	if (key == GLUT_KEY_RIGHT)
		sceTX += 1;
	objTX -= 1;

	if (key == GLUT_KEY_LEFT)
		sceTX -= 1;
	objTX += 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 'y')
		sceRY += 1;

	if (key == 'Y')
		sceRY -= 1;

	if (key == 'l')
		objRY += 1;

	if (key == 'r')
		objRY -= 1;

	if (key == 'Z')
		sceTZ += 1;

	if (key == 'z')
		sceTZ -= 1;

	if (key == 'w')
	{
		sceTZ += 1;
		objTZ -= 1;
	}

	if (key == 's')
	{
		sceTZ -= 1;
		objTZ += 1;
	}

	if (key == 'a')
	{
		sceTY += 1;
		objTY -= 1;
	}

	if (key == 'd')
	{
		sceTY -= 1;
		objTY += 1;
	}

	if (key == '6')
		lookX += 1;

	if (key == '4')
		lookX -= 1;

	if (key == '8')
		lookY += 1;

	if (key == '2')
		lookY -= 1;

	if (key == '1')
		glEnable(GL_LIGHT0);

	if (key == '3')
		glDisable(GL_LIGHT0);

	if (key == '6')
		glShadeModel(GL_FLAT);

	if (key == '7')
		glShadeModel(GL_SMOOTH);

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bandaranaike_International_Airport_JetBridge");

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();
	glutMainLoop();
	return 0;
}