#include "BuildingLeft.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint buildingLeftTextures[6]; // Array to store texture IDs

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