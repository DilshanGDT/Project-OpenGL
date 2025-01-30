#include "BuildingRight.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint buildingRightTextures[6]; // Array to store texture IDs

void loadBuildingRightTextures() {
	// Example for loading textures
	const char* textureFiles[] = {
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/window.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/door.jpg"
	};

	for (int i = 0; i < 2; i++) {
		buildingRightTextures[i] = SOIL_load_OGL_texture(
			textureFiles[i],
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if (!buildingRightTextures[i]) {
			printf("Texture loading failed for %s: %s\n", textureFiles[i], SOIL_last_result());
		}
		else {
			printf("Successfully loaded texture: %s\n", textureFiles[i]);
		}
	}
}

void cube_buildingR() {
	glBegin(GL_QUADS);

	// Front face (z = 0.5)
	glColor3f(0.3f, 0.2f, 0.3f); // Red
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face (z = -0.5)
	glColor3f(0.3f, 0.2f, 0.3f); // Green
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	// Left face (x = -0.5)
	glColor3f(0.3f, 0.2f, 0.3f); // Blue
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	// Right face (x = 0.5)
	glColor3f(0.3f, 0.2f, 0.3f); // Yellow
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	// Top face (y = 0.5)
	glColor3f(0.3f, 0.2f, 0.3f); // Magenta
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	// Bottom face (y = -0.5)
	glColor3f(0.5f, 0.5f, 0.5f); // Cyan
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();
}

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
	cube_buildingR();
	glPopMatrix();
}

void doorFrames_buildingR() {
	// top
	glPushMatrix();
	glTranslated(0, 0, 5);
	glScaled(3, 0.2, 1);
	cube_buildingR();
	glPopMatrix();

	// left
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(-0.65, -1.5, 5);
	glScaled(1.5, 0.2, 1);
	cube_buildingR();
	glPopMatrix();

	// right
	glPushMatrix();
	glRotated(90, 0, 0, 1);
	glTranslated(-0.65, 1.5, 5);
	glScaled(1.5, 0.2, 1);
	cube_buildingR();
	glPopMatrix();
}

void doorPanel_buildingR() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, buildingRightTextures[1]);

	glPushMatrix();
	glTranslated(0, -1.5, 5.2);
	glScaled(1.5, 1.4, 0);
	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 0, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 1, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, 0);

	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void doors_buildingR() {
	//door 1
	glPushMatrix();
	glTranslated(18, 1.5, -7.5);
	doorFrames_buildingR();
	doorPanel_buildingR();
	glPopMatrix();

	//door back
	glPushMatrix();
	glTranslated(13, 1.5, -23.3);
	doorFrames_buildingR();
	doorPanel_buildingR();
	glPopMatrix();
}

void sideWindow_buildingR() {

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, buildingRightTextures[0]);

	glPushMatrix();
	glTranslated(9.7, 1, -6);
	glScaled(0.5, 0.5, 0.5);

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(25.01f, 0.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(35.01f, 0.0f, -15.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(35.01f, 3.5f, -15.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(25.01f, 3.5f, 0.0f);

	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void buildingR() {
	mainWalls_buildingR();
	floor_buildingR();
	roof_buildingR();
	box1_buildingR();
	doors_buildingR();
	sideWindow_buildingR();
}