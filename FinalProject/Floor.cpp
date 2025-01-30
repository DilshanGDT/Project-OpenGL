#include "Floor.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

void mainFloor_airport() {
	glPushMatrix();
	glBegin(GL_QUADS);

	// Front face (z = 0.5)
	glColor3f(0.4f, 0.4f, 0.4f); // Red
	glVertex3f(-80, -0.25, 80);
	glVertex3f(100, -0.25, 80);
	glVertex3f(100, -0.25, -190);
	glVertex3f(-80, -0.25, -190);

	glEnd();
	glPopMatrix();
}

void roadSegments() {
	glPushMatrix();
	glBegin(GL_QUADS);

	// Front face (z = 0.5)
	glColor3f(0.1f, 0.1f, 0.1f);
	glVertex3f(0, -0.24, 0);
	glVertex3f(3, -0.24, 0);
	glVertex3f(3, -0.24, -3);
	glVertex3f(0, -0.24, -3);

	glEnd();
	glPopMatrix();
}

void roads() {
	// main road near terminal
	glPushMatrix();
	glTranslated(-80, 0, 54.5);
	glScaled(60, 1, 1);
	roadSegments();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-80, 0, 58);
	glScaled(60, 1, 1);
	roadSegments();
	glPopMatrix();

	// road near building right door
	glPushMatrix();
	glTranslated(34, 0, 52);
	glScaled(1.5, 1, 10);
	roadSegments();
	glPopMatrix();

	// road near building left
	glPushMatrix();
	glTranslated(-76, 0, 52);
	glScaled(2, 1, 55);
	roadSegments();
	glPopMatrix();

	// road near building left
	glPushMatrix();
	glTranslated(92, 0, 52);
	glScaled(2, 1, 55);
	roadSegments();
	glPopMatrix();

	// flight to run away
	glPushMatrix();
	glTranslated(-80, 0, -110);
	glScaled(60, 1, 3);
	roadSegments();
	glPopMatrix();

	// run away 1
	glPushMatrix();
	glTranslated(-80, 0, -130);
	glScaled(60, 1, 9);
	roadSegments();
	glPopMatrix();

	// run away 2
	glPushMatrix();
	glTranslated(-80, 0, -160);
	glScaled(60, 1, 9);
	roadSegments();
	glPopMatrix();

	// flight parking
	glPushMatrix();
	glTranslated(-45, 0, 2);
	glScaled(43, 1, 40);
	roadSegments();
	glPopMatrix();

	// vehicle parking lot
	glPushMatrix();
	glTranslated(-15, 0, 80);
	glScaled(10, 1, 5);
	roadSegments();
	glPopMatrix();

	glPushMatrix();
	glTranslated(25, 0, 80);
	glScaled(10, 1, 5);
	roadSegments();
	glPopMatrix();

	// vehicle parking lot road
	// 1st parking lot
	glPushMatrix();
	glTranslated(-1.5, 0, 66);
	glScaled(1, 1, 3);
	roadSegments();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10, 0, 66);
	glScaled(1, 1, 3);
	roadSegments();
	glPopMatrix();

	// 2nd parking lot
	glPushMatrix();
	glTranslated(29, 0, 0);
	glPushMatrix();
	glTranslated(-1.5, 0, 66);
	glScaled(1, 1, 3);
	roadSegments();
	glPopMatrix();

	glPushMatrix();
	glTranslated(10, 0, 66);
	glScaled(1, 1, 3);
	roadSegments();
	glPopMatrix();
	glPopMatrix();

	// flight parking lot to run away
	glPushMatrix();
	glTranslated(10, 0, -118);
	glScaled(5, 1, 7);
	roadSegments();
	glPopMatrix();

	glPushMatrix();
	glTranslated(68, 0, -118);
	glScaled(5, 1, 7);
	roadSegments();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-40, 0, -118);
	glScaled(5, 1, 7);
	roadSegments();
	glPopMatrix();
}

void grassSegment() {
	glPushMatrix();
	glBegin(GL_QUADS);

	// Front face (z = 0.5)
	glColor3f(0.0f, 0.6f, 0.3f);
	glVertex3f(0, -0.24, 0);
	glVertex3f(3, -0.24, 0);
	glVertex3f(3, -0.24, -3);
	glVertex3f(0, -0.24, -3);

	glEnd();
	glPopMatrix();
}

void grass() {

	// near the parking
	glPushMatrix();
	glTranslated(-79.5, 0, 80);
	glScaled(21.4, 0, 7);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(56, 0, 80);
	glScaled(14.5, 0, 7);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(16, 0, 80);
	glScaled(2.8, 0, 7);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-17, 0, 64.5);
	glScaled(5, 0, 1.8);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(42.5, 0, 64.5);
	glScaled(5, 0, 1.8);
	grassSegment();
	glPopMatrix();

	// triangle shaped grass near bulidng right
	glPushMatrix();
	glTranslated(42, 0, 49.3);
	glScaled(16, 0, 15);
	glBegin(GL_QUADS);

	// Front face (z = 0.5)
	glColor3f(0.0f, 0.6f, 0.3f);
	glVertex3f(0, -0.24, 0);
	glVertex3f(3, -0.24, 0);
	glVertex3f(3, -0.24, -3);
	glVertex3f(1.9, -0.24, -3);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-68.5, 0, 1);
	glScaled(7.5, 0, 36.5);
	grassSegment();
	glPopMatrix();

	//runaway middle
	glPushMatrix();
	glTranslated(-80, 0, -119.5);
	glScaled(13, 0, 3);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-24.2, 0, -119.5);
	glScaled(11, 0, 3);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(25.8, 0, -119.5);
	glScaled(13.5, 0, 3);
	grassSegment();
	glPopMatrix();

	glPushMatrix();
	glTranslated(84, 0, -119.5);
	glScaled(5, 0, 3);
	grassSegment();
	glPopMatrix();
}

void airportFloor() {
	mainFloor_airport();
	roads();
	grass();
}