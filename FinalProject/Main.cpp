// Libraries and Dependencies
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <SOIL2.h>

#include "Pier.h"			// Pier class
#include "BuildingLeft.h"	// Left Building class
#include "BuildingRight.h"	// Right Building class
#include "Terminal.h"		// Terminal class
#include "Floor.h"			// Airport floor class
#include "JetBridge.h"		// Jetbridge

int frameNumber = 0;

// Lighting Toggles
bool isl1On = true;
bool isl2On = true;
bool isl3On = true;

// Lightning
GLfloat light1_pos[] = { -10.0, 1.0, -0.5, 1.0 };	// First light position
GLfloat light2_pos[] = { 10.0, 1.0, -0.5, 1.0 };	// Second light position
GLfloat light3_pos[] = { 0.0, 10.0, 0.0, 1.0 };		// Third light position

void setLightingAndShading() {
	glEnable(GL_LIGHTING);

	// First Light Source (GL_LIGHT0) - White light
	GLfloat l0amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat l0diff[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat l0spec[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0spec);
	glLightfv(GL_LIGHT0, GL_POSITION, light1_pos);

	// Second Light Source (GL_LIGHT1) - Yellow tinted light
	GLfloat l1amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat l1diff[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat l1spec[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l1amb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l1diff);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l1spec);
	glLightfv(GL_LIGHT1, GL_POSITION, light2_pos);

	// Third Light Source (GL_LIGHT2) - Same color as the first two
	GLfloat l2amb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat l2diff[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat l2spec[] = { 0.2, 0.2, 0.2, 1.0 };
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, l2amb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, l2diff);
	glLightfv(GL_LIGHT2, GL_SPECULAR, l2spec);
	glLightfv(GL_LIGHT2, GL_POSITION, light3_pos);

	// Enable material properties for color interaction
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Material specular reflection
	GLfloat specRef[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Enable smooth shading and normalize normals
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
}

std::tuple<float, float, float> calculateNormal(
	const std::tuple<float, float, float>& v1,
	const std::tuple<float, float, float>& v2,
	const std::tuple<float, float, float>& v3)
{
	float x1 = std::get<0>(v2) - std::get<0>(v1);
	float y1 = std::get<1>(v2) - std::get<1>(v1);
	float z1 = std::get<2>(v2) - std::get<2>(v1);

	float x2 = std::get<0>(v3) - std::get<0>(v1);
	float y2 = std::get<1>(v3) - std::get<1>(v1);
	float z2 = std::get<2>(v3) - std::get<2>(v1);

	float nx = y1 * z2 - z1 * y2;
	float ny = z1 * x2 - x1 * z2;
	float nz = x1 * y2 - y1 * x2;

	// Normalize the normal vector
	float length = sqrt(nx * nx + ny * ny + nz * nz);
	return { nx / length, ny / length, nz / length };
}

// Variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

// Variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

// Variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

GLuint textures[6];

void loadTextures() {
	// Example for loading textures
	const char* textureFiles[] = {
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/sky.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/door.jpg"
	};

	for (int i = 0; i < 2; i++) {
		textures[i] = SOIL_load_OGL_texture(
			textureFiles[i],
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if (!textures[i]) {
			printf("Texture loading failed for %s: %s\n", textureFiles[i], SOIL_last_result());
		}
		else {
			printf("Successfully loaded texture: %s\n", textureFiles[i]);
		}
	}
}

// Grid and coordinate axes for better visualization
void drawGrid() {
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -20; line <= 20; line += step) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);

		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();
}

void drawAxes() {
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

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	loadJetBridgeTextures();
	loadTerminalTextures();
	loadBuildingLeftTextures();
	loadBuildingRightTextures();
	loadPierTextures();
	loadTextures();
}

// --------- airplane from blender coordinates --------------

std::vector<std::vector<std::tuple<float, float, float>>> airplaneFaces;

// Read vertices from the file
void loadVerticesFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Could not open file: " << filename << std::endl;
		return;
	}

	std::string line;
	std::vector<std::tuple<float, float, float>> face;
	while (getline(file, line)) {
		if (line.find("Vertex") != std::string::npos) {
			std::istringstream ss(line.substr(line.find("[") + 1));
			float x, y, z;
			char comma;
			ss >> x >> comma >> y >> comma >> z;
			face.emplace_back(x, y, z);

			if (face.size() == 3) {
				airplaneFaces.push_back(face);
				face.clear();
			}
		}
	}
	file.close();
}

// Draw the airplane using vertices data
void drawAirplane() {
	glColor3f(0.5f, 0.5f, 0.5f); // Set the color of the airplane

	for (const auto& face : airplaneFaces) {
		if (face.size() < 3) continue;

		// Calculate normal for the face
		auto normal = calculateNormal(face[0], face[1], face[2]);
		glNormal3f(std::get<0>(normal), std::get<1>(normal), std::get<2>(normal));

		glBegin(GL_TRIANGLES);
		for (const auto& vertex : face) {
			glVertex3f(std::get<0>(vertex), std::get<1>(vertex), std::get<2>(vertex));
		}
		glEnd();
	}
}

// Environment

void mainBuildings() {

	glPushMatrix();
	glTranslated(0, 0, 45);
	glScaled(2, 2, 2);

	terminal();
	buildingR();
	buildingL();
	twoPiers();

	glPopMatrix();
}

void lightTower() {

	GLUquadricObj* quad = gluNewQuadric();

	glPushMatrix();
	glColor3f(0.3, 0.5, 0.5);
	glRotated(-90, 1, 0, 0);
	gluCylinder(quad, 0.2, 0.1, 4, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(0, 4, 0);
	gluSphere(quad, 0.3, 20, 20);
	glPopMatrix();
}

void lightTowers() {
	
	// terminal front
	glPushMatrix();
	glTranslated(-78, 0, 58.5);
	lightTower();
	glPopMatrix();

	int j = 20;
	for (int i = 0; i < 9; i++) {
		glPushMatrix();
		glTranslated(-78 + j, 0, 58.5);
		lightTower();
		j += 19;
		glPopMatrix();
	}

	// terminal left
	glPushMatrix();
	glTranslated(-78, 0, 50.5);
	lightTower();
	glPopMatrix();

	j = 20;
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(-78, 0, 58.5 - j);
		lightTower();
		j += 21;
		glPopMatrix();
	}

	//other towers (back of the terminal)
	glPushMatrix();
	glTranslated(-63, 0, 5);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-43, 0, 5);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-23, 0, 5);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, 0, 5);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(68, 0, 5);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(91, 0, 5);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(91, 0, 29);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(91, 0, 50);
	lightTower();
	glPopMatrix();

	//runaway 1
	glPushMatrix();
	glTranslated(95, -3, -158.5);
	lightTower();
	glPopMatrix();

	j = 20;
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(95 - j, -3, -158.5);
		lightTower();
		j += 21;
		glPopMatrix();
	}

	//runaway 2
	glPushMatrix();
	glTranslated(95, -3, -188.5);
	lightTower();
	glPopMatrix();

	j = 20;
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(95 - j, -3, -188.5);
		lightTower();
		j += 21;
		glPopMatrix();
	}

	//flight parking
	glPushMatrix();
	glTranslated(92, 0, -124);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(45, 0, -124);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-8, 0, -124);
	lightTower();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-58, 0, -124);
	lightTower();
	glPopMatrix();
}

void tree() {
	glPushMatrix();
	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.2, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();
}

void tree2() {
	glPushMatrix();
	glBegin(GL_TRIANGLES);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(45, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-45, 0, 1, 0);
	glBegin(GL_TRIANGLES);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.5, 0, 0);
	glVertex3f(0.5, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0.8, 0.5, 0.3);
	glVertex3f(-0.4, 0.6, 0);
	glVertex3f(0.4, 0.6, 0);
	glVertex3f(0, 1.6, 0);

	glEnd();
	glPopMatrix();
}

void trees() {

	// terminal left
	int j = 0;
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glTranslated(-75 + j, 0, 75);
		glScaled(2, 2, 2);
		tree();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 12; i++) {
		glPushMatrix();
		glTranslated(-75 + j, 0, 65);
		glScaled(2, 2, 2);
		tree2();
		j += 5;
		glPopMatrix();
	}

	// terminal middle
	glPushMatrix();
	glTranslated(20, 0, 75);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 0, 68.5);
	glScaled(2, 2, 2);
	tree2();
	glPopMatrix();

	glPushMatrix();
	glTranslated(20, 0, 62);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	// terminal right
	j = 0;
	for (int i = 0; i < 9; i++) {
		glPushMatrix();
		glTranslated(58 + j, 0, 75);
		glScaled(2, 2, 2);
		tree();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 9; i++) {
		glPushMatrix();
		glTranslated(58 + j, 0, 65);
		glScaled(2, 2, 2);
		tree2();
		j += 5;
		glPopMatrix();
	}

	// building right
	j = 0;
	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glTranslated(50 + j, 0, 45);
		glScaled(2, 2, 2);
		tree2();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 7; i++) {
		glPushMatrix();
		glTranslated(55 + j, 0, 38);
		glScaled(2, 2, 2);
		tree();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glTranslated(60 + j, 0, 31);
		glScaled(2, 2, 2);
		tree2();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 5; i++) {
		glPushMatrix();
		glTranslated(65 + j, 0, 24);
		glScaled(2, 2, 2);
		tree();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 4; i++) {
		glPushMatrix();
		glTranslated(70 + j, 0, 17);
		glScaled(2, 2, 2);
		tree2();
		j += 5;
		glPopMatrix();
	}

	j = 0;
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glTranslated(75 + j, 0, 10);
		glScaled(2, 2, 2);
		tree();
		j += 5;
		glPopMatrix();
	}

	// near left building
	j = 0;
	for (int i = 0; i < 13; i++) {
		glPushMatrix();
		glTranslated(-56.5, 0, -4 - j);
		glScaled(3, 3, 3);
		tree2();
		j += 8;
		glPopMatrix();
	}

	// near runaway
	glPushMatrix();
	glTranslated(-75, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-65, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-15, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(32, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(38, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(52, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();

	glPushMatrix();
	glTranslated(58, 0, -123.8);
	glScaled(2, 2, 2);
	tree();
	glPopMatrix();
}

void jetBridges() {

	// set 1 left
	glPushMatrix();
	glTranslated(-3, 1, -9);
	glRotated(40, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 1, -49);
	glRotated(40, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-3, 1, -89);
	glRotated(40, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 1, -9);
	glRotated(140, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 1, -49);
	glRotated(140, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-20, 1, -89);
	glRotated(140, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	// set 2 right
	glPushMatrix();
	glTranslated(62, 1, -12);
	glRotated(40, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(62, 1, -52);
	glRotated(40, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(62, 1, -92);
	glRotated(40, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(44, 1, -12);
	glRotated(140, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(44, 1, -52);
	glRotated(140, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();

	glPushMatrix();
	glTranslated(44, 1, -92);
	glRotated(140, 0, 1, 0);
	glScaled(1.5, 1.5, 1.5);
	jetBridge();
	glPopMatrix();
}

void airplaneCorrectAngle() {
	glPushMatrix();
	glScaled(30, 20, 35);
	glTranslated(0, 0, 0);
	glRotated(-90, 1, 0, 0);
	drawAirplane();
	glPopMatrix();
}

void airplane() {
	glPushMatrix();
	glRotated(-40, 0, 1, 0);
	glTranslated(5, -5, -20);
	airplaneCorrectAngle();
	glPopMatrix();
}

void airplaneMovable() {
	glPushMatrix();
	glRotated(-40, 0, 1, 0);
	glTranslated(5, -5, -20);
	airplaneCorrectAngle();
	glPopMatrix();
}

void airplaneParking() {
	// middle set
	airplane();

	glPushMatrix();
	glTranslated(0, 0, -40);
	airplane();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -80);
	airplane();
	glPopMatrix();

	// right set
	glPushMatrix();
	glTranslated(65, 0, 0);
	airplane();
	glPopMatrix();

	/*glPushMatrix();
	glTranslated(65, 0, -40);
	airplane();
	glPopMatrix();*/

	/*glPushMatrix();
	glTranslated(65, 0, -80);
	airplane();
	glPopMatrix();*/

	//left set
	glPushMatrix();
	glRotated(80, 0, 1, 0);
	glTranslated(-6, 0, -25);
	airplane();
	glPopMatrix();

	glPushMatrix();
	glRotated(80, 0, 1, 0);
	glTranslated(74, 0, -38);
	airplane();
	glPopMatrix();
}

void movablePlane(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslated(65 + x, 0, -40 + z);
	glRotated(y, 0, 1, 0);
	airplaneMovable();
	glPopMatrix();
}

void animatedPlane() {
	glPushMatrix();
	glTranslated(-40, 0, -138);
	glRotated(130, 0, 1, 0);
	airplane();
	glPopMatrix();
}

void fullEnvironment() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);  // Bind your texture here

	glPushMatrix();

	// Create a new quadric object for the sphere
	GLUquadricObj* quad = gluNewQuadric();

	// Enable automatic texture coordinate generation for the sphere
	gluQuadricTexture(quad, GL_TRUE);

	// Draw the sphere with the texture
	gluSphere(quad, 170, 100, 100);

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 1.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	// Draw the floor
	//drawFloor();

	// Draw the grid
	//drawGrid();

	// Draw the axes
	drawAxes();

	// Set the lighting
	setLightingAndShading();

	mainBuildings();
	airportFloor();

	// Draw the airplane model
	airplaneParking();
	lightTowers();
	trees();
	jetBridges();

	// animated plane
	glPushMatrix();
	glTranslated(10 * (frameNumber % 30)/1.5 - 10, (frameNumber % 30) / 1.5, 0);
	animatedPlane();
	glPopMatrix();

	// movable plane
	glPushMatrix();
	/*glTranslated(objRX, 0, objRZ);
	glRotated(objRY, 0, 1, 0);*/
	movablePlane(objRX, objRY, objRZ);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0, -55);
	fullEnvironment();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void doFrame(int v)
{
	frameNumber++;
	glutPostRedisplay();
	glutTimerFunc(80, doFrame, 0);
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_MODELVIEW);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Define the Perspective projection frustum 
	// (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
	gluPerspective(120.0, aspect_ratio, 1.0, 100.0);
}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camY += 0.5;

	if (key == GLUT_KEY_DOWN)
		camY -= 0.5;

	if (key == GLUT_KEY_RIGHT)
		sceTX -= 0.5;

	if (key == GLUT_KEY_LEFT)
		sceTX += 0.5;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {

	//move one plane
	if (key == 'j')
		objRY += 0.5;

	if (key == 'l')
		objRY -= 0.5;

	if (key == 'i')
		objRX += 0.5;

	if (key == 'k')
		objRX -= 0.5;

	if (key == 'Z')
		sceTZ += 0.5;

	if (key == 'z')
		sceTZ -= 0.5;

	if (key == 'w')
		sceTX += 0.5;

	if (key == 's')
		sceTX -= 0.5;

	if (key == 'y')
		sceRY += 0.5;

	if (key == 'Y')
		sceRY -= 0.5;

	if (key == '1')
		if (!isl1On) {
			glEnable(GL_LIGHT0);
			isl1On = true;
		}
		else {
			glDisable(GL_LIGHT0);
			isl1On = false;
		}
	if (key == '2')
		if (!isl1On) {
			glEnable(GL_LIGHT1);
			isl1On = true;
		}
		else {
			glDisable(GL_LIGHT1);
			isl1On = false;
		}

	if (key == '3') {
    if (!isl3On) {
        glEnable(GL_LIGHT2);
        isl3On = true;
    } else {
        glDisable(GL_LIGHT2);
        isl3On = false;
    }
}

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT with command-line arguments
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Bandaranaike International Ariport 3D Model");

	loadVerticesFromFile("C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/object_vertices/aeroPlaneFaces.txt"); // Load vertices from the file

	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(500, doFrame, 0);
	init();
	glutMainLoop();
	return 0;
}