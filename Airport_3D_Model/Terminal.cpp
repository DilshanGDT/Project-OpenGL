#include "Terminal.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint textureImage;
GLuint terminalTextures[6]; // Array to store texture IDs

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

void cube_terminal() {
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
	cube_terminal();
	glPopMatrix();

	int j = 10;
	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glScaled(0.1, 4, 0.25);
		glTranslated(0 - j, 0.5, 0);
		j += 10;
		cube_terminal();
		glPopMatrix();
	}

	for (int i = 0; i < 10; i++) {
		glPushMatrix();
		glScaled(0.1, 4, 0.25);
		glTranslated(-100 + j, 0.5, 0);
		j += 10;
		cube_terminal();
		glPopMatrix();
	}

}

void concreteWindowFramesHorizontal_terminal() {
	glPushMatrix();
	glScaled(20, 0.1, 0.25);
	glTranslated(0, 1, 0);
	cube_terminal();
	glPopMatrix();

	int j = 13;
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glScaled(20, 0.1, 0.25);
		glTranslated(0, 1 + j, 0);
		cube_terminal();
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
	cube_terminal();
	glPopMatrix();

	//floor
	glPushMatrix();
	glTranslated(0, -0.05, -7);
	glScaled(22, 0.2, 20);
	cube_terminal();
	glPopMatrix();
}

void doorFrames_terminal() {
	// top
	glPushMatrix();
	glTranslated(0, 0, 5);
	glScaled(3, 0.2, 1);
	cube_terminal();
	glPopMatrix();

	// left
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(-0.65, -1.5, 5);
	glScaled(1.5, 0.2, 1);
	cube_terminal();
	glPopMatrix();

	// right
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(-0.65, 1.5, 5);
	glScaled(1.5, 0.2, 1);
	cube_terminal();
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

void nameBoard_terminal() {
	glPushMatrix();
	glTranslated(0, 4.65, 3);
	glScaled(10, 0.8, 0.2);
	cube_terminal();
	glPopMatrix();
}

void terminal() {

	walls_terminal();
	floorRoof_terminal();
	doors_terminal();
	concreteSupporters_terminal();
	nameBoard_terminal();
}