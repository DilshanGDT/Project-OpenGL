#include "BuildingLeft.h"
#include <GL/glut.h>
#include <stdio.h>
#include <SOIL2.h>

GLuint buildingLeftTextures[3]; // Array to store texture IDs

void loadBuildingLeftTextures() {
	// Example for loading textures
	const char* textureFiles[] = {
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/door.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/door.jpg",
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Sample Program/images/terminal/door.jpg"
	};

	for (int i = 0; i < 3; i++) {
		buildingLeftTextures[i] = SOIL_load_OGL_texture(
			textureFiles[i],
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
		);

		if (!buildingLeftTextures[i]) {
			printf("Texture loading failed for %s: %s\n", textureFiles[i], SOIL_last_result());
		}
		else {
			printf("Successfully loaded texture: %s\n", textureFiles[i]);
		}
	}
}

void cube_buildingL() {
	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	// Draw Cube with Different Textures for Different Pairs of Faces
	glBegin(GL_QUADS);

	// Bind the first texture for Front and Back faces
	glBindTexture(GL_TEXTURE_2D, buildingLeftTextures[0]);

	// Front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// Back face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);

	// Bind the second texture for Left and Right faces
	glBindTexture(GL_TEXTURE_2D, buildingLeftTextures[1]);

	// Left face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// Right face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);

	// Bind the third texture for Top and Bottom faces
	glBindTexture(GL_TEXTURE_2D, buildingLeftTextures[2]);

	// Top face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	// Bottom face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();
}

//void cube_buildingL() {
//	glBegin(GL_QUADS);
//
//	// Front face (z = 0.5)
//	glColor3f(0.3f, 0.2f, 0.3f); // Red
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//
//	// Back face (z = -0.5)
//	glColor3f(0.3f, 0.3f, 0.3f); // Green
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//
//	// Left face (x = -0.5)
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//
//	// Right face (x = 0.5)
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//
//	// Top face (y = 0.5)
//	glColor3f(1.0f, 0.0f, 1.0f); // Magenta
//	glVertex3f(-0.5f, 0.5f, -0.5f);
//	glVertex3f(-0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, 0.5f, 0.5f);
//	glVertex3f(0.5f, 0.5f, -0.5f);
//
//	// Bottom face (y = -0.5)
//	glColor3f(0.0f, 1.0f, 1.0f); // Cyan
//	glVertex3f(-0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, -0.5f);
//	glVertex3f(0.5f, -0.5f, 0.5f);
//	glVertex3f(-0.5f, -0.5f, 0.5f);
//
//	glEnd();
//}

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