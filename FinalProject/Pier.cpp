#include "Pier.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint pierTextures[6]; // Array to store texture IDs

void loadPierTextures() {
	// Example for loading textures
	const char* textureFiles[] = {
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/window.jpg"
	};

	for (int i = 0; i < 1; i++) {
		pierTextures[i] = SOIL_load_OGL_texture(
			textureFiles[i],
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if (!pierTextures[i]) {
			printf("Texture loading failed for %s: %s\n", textureFiles[i], SOIL_last_result());
		}
		else {
			printf("Successfully loaded texture: %s\n", textureFiles[i]);
		}
	}
}

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

	// single side
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
}

void singleWindow_pier() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, pierTextures[0]);

	glPushMatrix();
	glTranslated(0.8, 0.6, 0);
	glScaled(1.2, 0.6, 1);

	glBegin(GL_QUADS);

	// Windows
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-8, 0.5, 0.01);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2, 0.5, 0.01);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2, 2.5, 0.01);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-8, 2.5, 0.01);

	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void allWindowsOneSide_pier() {
	singleWindow_pier();

	glPushMatrix();
	glTranslated(25.5, 0, 0);
	glScaled(2, 1, 1);
	singleWindow_pier();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, 0, 0);
	glScaled(2, 1, 1);
	singleWindow_pier();
	glPopMatrix();

	glPushMatrix();
	glTranslated(65, 0, 0);
	singleWindow_pier();
	glPopMatrix();
}

void windows_pier() {
	allWindowsOneSide_pier();

	glPushMatrix();
	glTranslated(0, 0, -3.1);
	allWindowsOneSide_pier();
	glPopMatrix();
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
	glTranslated(-0.25, 0, 0.5);
	glScaled(1.1, 1, 1.4);
	completeRoofSegment_pier();
	glPopMatrix();
}

void floorSegment_pier() {
	glPushMatrix();
	glTranslated(0.13, -2.75, 0);
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

	windows_pier();
}

void twoPiers() {
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glScaled(0.8, 0.8, 0.8);
	glTranslated(28, 0, -6);
	pier();
	glPopMatrix();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glScaled(0.8, 0.8, 0.8);
	glTranslated(30, 0, 34);
	pier();
	glPopMatrix();
}
