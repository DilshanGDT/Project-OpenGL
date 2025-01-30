#include "JetBridge.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint jetBridgeTextures[6]; // Array to store texture IDs

void loadJetBridgeTextures() {
	// Example for loading textures
	const char* textureFiles[] = {
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/jetbridge/containerTexture.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/jetbridge/glassTexture.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/jetbridge/acTexture.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/jetbridge/ironPipeTexture.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/jetbridge/rubberTexture.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/jetbridge/standBaseTexture.jpg"
	};

	for (int i = 0; i < 6; i++) {
		jetBridgeTextures[i] = SOIL_load_OGL_texture(
			textureFiles[i],
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if (!jetBridgeTextures[i]) {
			printf("Texture loading failed for %s: %s\n", textureFiles[i], SOIL_last_result());
		}
		else {
			printf("Successfully loaded texture: %s\n", textureFiles[i]);
		}
	}
}

void container_jetBridge()
{
	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[0]);

	glBegin(GL_QUADS);

	// Front Face with texture
	glColor3f(1.0f, 1.0f, 1.0f); // White to avoid blending
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2, 1, 0);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1, 0);

	// Back Face with texture
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2, 0, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2, 1, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1, -1);

	// Bottom Face with texture
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2, 0, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, -1);

	// Top Face with texture
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2, 1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2, 1, -1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1, -1);

	glEnd();

	glDisable(GL_TEXTURE_2D); // Disable texturing
}

void containerGlass_jetBridge()
{
	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[1]);

	glBegin(GL_QUADS);

	// Front Face with texture
	glColor3f(1.0f, 1.0f, 1.0f); // White color to avoid blending with color
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, 0.1, 0.01);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.8, 0.1, 0.01);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.8, 0.9, 0.01);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, 0.9, 0.01);

	// Back Face with texture
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.2, 0.1, -1.01);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.8, 0.1, -1.01);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.8, 0.9, -1.01);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.2, 0.9, -1.01);

	glEnd();

	// Disable texturing
	glDisable(GL_TEXTURE_2D);
}

void containerBigger_jetBridge()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[0]);

	glBegin(GL_QUADS);

	// Front Face
	glColor3f(1.0f, 1.0f, 1.0f); // White to avoid blending
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(3, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(3, 1.2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1.2, 0);

	// Back Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -1.2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(3, 0, -1.2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(3, 1.2, -1.2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1.2, -1.2);

	// Bottom Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(3, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(3, 0, -1.2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, -1.2);

	// Top Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 1.2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(3, 1.2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(3, 1.2, -1.2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1.2, -1.2);

	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -1.2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 1.2, -1.2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1.2, 0);

	// Right Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(3, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(3, 0, -1.2);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(3, 1.2, -1.2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(3, 1.2, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void containerGlassBigger_jetBridge()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[1]);

	glBegin(GL_QUADS);

	// Front Face (Texture Applied)
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.1, 0.01);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.8, 0.1, 0.01);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.8, 1.1, 0.01);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 1.1, 0.01);

	// Back Face (Texture Applied)
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2, 0.1, -1.21);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(2.8, 0.1, -1.21);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(2.8, 1.1, -1.21);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2, 1.1, -1.21);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void containerConnector_jetBridge()
{
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	// glTranslated(-0.1, -0.1, 0);

	glBegin(GL_QUADS);

	// Blue
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0, 0, 0);
	glVertex3f(1.2, 0, 0);
	glVertex3f(1.2, 1.2, 0);
	glVertex3f(0, 1.2, 0);

	// Blue
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0, 0, 3);
	glVertex3f(1.2, 0, 3);
	glVertex3f(1.2, 1.2, 3);
	glVertex3f(0, 1.2, 3);

	glEnd();

	glPopMatrix();
}

void stands_jetBridge() {

	GLUquadric* quad = gluNewQuadric();

	// Right Stand (Texture A)
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[3]);
	gluQuadricTexture(quad, GL_TRUE);
	glTranslatef(0, -0.2, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.07, 0.04, 1.7, 30, 6);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Cone on Right Stand (Texture B)
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[4]);
	gluQuadricTexture(quad, GL_TRUE);
	glTranslatef(0, 1.5, 0);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.04, 0.0, 0.2, 30, 6);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Left Stand (Texture A)
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[3]);
	gluQuadricTexture(quad, GL_TRUE);
	glTranslatef(0, -0.2, -1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.07, 0.04, 1.7, 30, 6);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Cone on Left Stand (Texture B)
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[4]);
	gluQuadricTexture(quad, GL_TRUE);
	glTranslatef(0, 1.5, -1);
	glRotatef(-90, 1, 0, 0);
	gluCylinder(quad, 0.04, 0.0, 0.2, 30, 6);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	gluDeleteQuadric(quad);
}

void standBase_jetBridge() {
	// Apply textureC to all sides
	glPushMatrix();
	glRotated(90, 0, 1, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[2]); // Assuming textureC is properly loaded and initialized

	glBegin(GL_QUADS);

	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.2, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.2, 0.2, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0.2, 0);

	// Back Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, -0.4);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.2, 0, -0.4);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.2, 0.2, -0.4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0.2, -0.4);

	// Bottom Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0.2, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.2, 0.2, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.2, 0.2, -0.4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0.2, -0.4);

	// Top Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.2, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.2, 0, -0.4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0, -0.4);

	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, -0.4);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0, 0.2, -0.4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 0.2, 0);

	// Right Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.2, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.2, 0, -0.4);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.2, 0.2, -0.4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.2, 0.2, 0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void completeStand_jetBridge() {

	glPushMatrix();
	stands_jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.2, -0.4, 0.1);
	standBase_jetBridge();
	glPopMatrix();
}

void standTire_jetBridge() {
	glPushMatrix();
	glTranslated(15, -1.8, 1);
	glColor3f(0.1f, 0.1f, 0.1f); // Black color for tire
	glutSolidTorus(0.4f, 1.3f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslated(15, -1.8, -7);
	glColor3f(0.1f, 0.1f, 0.1f); // Black color for tire
	glutSolidTorus(0.4f, 1.3f, 30, 30);
	glPopMatrix();
}

void rotator_jetBridge() {

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, 4.6, 0);
	glRotated(90, 1, 0, 0);
	GLUquadricObj* quad = gluNewQuadric();

	gluQuadricTexture(quad, GL_TRUE);
	gluQuadricNormals(quad, GLU_SMOOTH); // Set normals for lighting
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[3]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	gluCylinder(quad, 0.2f, 0.3f, 1.0f, 20, 20);
	glDisable(GL_TEXTURE_2D);
	gluDeleteQuadric(quad);

	glPopMatrix();

	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	glTranslated(0, 3.6, 0);
	glScaled(0.75, 0.1, 0.75);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jetBridgeTextures[5]);
	glutSolidCube(1);
	glDisable(GL_TEXTURE_2D);
	//glRotated(90, 1, 0, 0);
	glPopMatrix();
}

void jetBridge() {
	glPushMatrix();
	glTranslated(3, 0.1, -0.1);
	container_jetBridge();
	containerGlass_jetBridge();
	glPopMatrix();

	glPushMatrix();
	containerConnector_jetBridge();
	containerBigger_jetBridge();
	containerGlassBigger_jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2, 0.1, -0.1);
	container_jetBridge();
	containerGlass_jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-4, 0.1, -0.1);
	container_jetBridge();
	containerGlass_jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(3, 0, 0);
	glScaled(1.2, 1.2, 1.2);
	completeStand_jetBridge();
	glPopMatrix();

	glPushMatrix();
	glScaled(0.2, 0.2, 0.2);
	standTire_jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2, -4.4, -0.6);
	rotator_jetBridge();
	glPopMatrix();
}