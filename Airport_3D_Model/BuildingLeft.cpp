#include "BuildingLeft.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint buildingLeftTextures[6]; // Array to store texture IDs

void cube_buildingL() {
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

void longerSupportBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-16, 1, -11);
	glScaled(12, 2, 3);
	cube_buildingL();
	glPopMatrix();
}

void normalBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-19, 1.5, -5);
	glScaled(12, 3, 10);
	cube_buildingL();
	glPopMatrix();
}

void supportBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-25, 1, -5);
	glScaled(12, 2, 8);
	cube_buildingL();
	glPopMatrix();
}

void longerBuilding_buildingL() {
	glPushMatrix();
	glTranslated(-22, 1, -15);
	glScaled(18, 2, 2);
	cube_buildingL();
	glPopMatrix();
}

void floor_buildingL() {
	glPushMatrix();
	glTranslated(-22, -0.05, -8);
	glScaled(22, 0.2, 20);
	cube_buildingL();
	glPopMatrix();
}

void buildingL() {
	longerSupportBuilding_buildingL();
	normalBuilding_buildingL();
	supportBuilding_buildingL();
	longerBuilding_buildingL();
	floor_buildingL();
}