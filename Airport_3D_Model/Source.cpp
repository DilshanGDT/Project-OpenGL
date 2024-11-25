#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL2.h>

// Variables to move the camera
GLfloat camXInit = 0.0;
GLfloat camYInit = 0.0;
GLfloat camZInit = 0.0;

GLfloat camX = camXInit;
GLfloat camY = camYInit;
GLfloat camZ = camZInit;

// Variables to move the scene
GLfloat sceRXInit = 0.0;
GLfloat sceRYInit = 0.0;
GLfloat sceRZInit = 0.0;
GLfloat sceTXInit = 0.0;
GLfloat sceTYInit = 0.0;
GLfloat sceTZInit = 0.0;

GLfloat sceRX = sceRXInit;
GLfloat sceRY = sceRYInit;
GLfloat sceRZ = sceRZInit;
GLfloat sceTX = sceTXInit;
GLfloat sceTY = sceTYInit;
GLfloat sceTZ = sceTZInit;

// Variables to move the looking position
GLfloat lookX = 0.0;
GLfloat lookY = 0.0;
GLfloat lookZ = 0.0;

// Variables to move the objects
GLfloat objRX = 0.0;
GLfloat objRY = 0.0;
GLfloat objRZ = 0.0;
GLfloat objTX = 0.0;
GLfloat objTY = 0.0;
GLfloat objTZ = 0.0;

GLfloat openDoorAngle = 60;
GLfloat openDoorZ = -0.05;
GLfloat openDoorXInit = -0.4;
GLfloat closeDoorAngle = 0;
GLfloat closeDoorZ = 0;
GLfloat closeDoorXInit = -0.5;

GLfloat doorAngle = closeDoorAngle;
GLfloat doorZ = closeDoorZ;
GLfloat doorXInit = closeDoorXInit;

static float dRot;

// Grid and coordinate axes for better visualization
void drawGrid()
{
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -20; line <= 20; line += step)
	{
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);

		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
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

// For texture image
GLuint glassTexture;
GLuint containerTexture;

// Read the image to texture image
void loadTextures()
{
	// SOIL_load
	glassTexture = SOIL_load_OGL_texture(
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Project-OpenGL/Airport_3D_Model/images/glassTexture.jpg", // Replace with the path to your texture file
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	if (!glassTexture)
	{
		printf("Texture loading failed: %s\n", SOIL_last_result());
	}

	containerTexture = SOIL_load_OGL_texture(
		"C:/Users/Dilshan/Documents/VS Code/CSC_3081/Project-OpenGL/Airport_3D_Model/images/containerTexture.jpg", // Replace with the path to your texture file
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	if (!containerTexture)
	{
		printf("Texture loading failed: %s\n", SOIL_last_result());
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

	loadTextures();
}

// Intensity of the light source
void light0(GLfloat offset, GLfloat posOffset)
{
	// (r, g, b, opacity)
	GLfloat l0amb[] = {0.2 + offset, 0.2 + offset, 0.2 + offset, 1.0};
	GLfloat l0diff[] = {0.8 - offset, 0.8 - offset, 0.8 - offset, 1.0};
	GLfloat l0spec[] = {1.0, 1.0, 1.0, 1.0};

	// Light source position : (x, y, z, type_of_the_light_source)
	GLfloat l0pos[] = {-10 + posOffset, 1.0, -0.5, 1.0};

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
	GLfloat l0amb[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat l0diff[] = {0.8, 0.8, 0.8, 1.0};
	GLfloat l0spec[] = {1.0, 1.0, 1.0, 1.0};

	GLfloat l0pos[] = {-10, 1.0, -0.5, 1.0};

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

	GLfloat specRef[] = {0.7, 0.7, 0.7, 1.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);

	GLint shiness = 128;
	glMateriali(GL_FRONT, GL_SHININESS, shiness);
}

// Jet Bridge
/*
void container_jetBridge() {
	glBegin(GL_QUADS);

	// Front Face (Red)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(2, 1, 0);
	glVertex3f(0, 1, 0);

	// Back Face (Red)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, -1);
	glVertex3f(2, 0, -1);
	glVertex3f(2, 1, -1);
	glVertex3f(0, 1, -1);

	// Bottom Face (Green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(2, 0, 0);
	glVertex3f(2, 0, -1);
	glVertex3f(0, 0, -1);

	// Top Face (Green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 1, 0);
	glVertex3f(2, 1, 0);
	glVertex3f(2, 1, -1);
	glVertex3f(0, 1, -1);

	glEnd();
}
*/

void container_jetBridge()
{
	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, containerTexture);

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

/*
void containerGlass_jetBridge() {
	glBegin(GL_QUADS);

	// Front Face (Blue)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.2, 0.1, 0.01);
	glVertex3f(1.8, 0.1, 0.01);
	glVertex3f(1.8, 0.9, 0.01);
	glVertex3f(0.2, 0.9, 0.01);

	// Back Face (Blue)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.2, 0.1, -1.01);
	glVertex3f(1.8, 0.1, -1.01);
	glVertex3f(1.8, 0.9, -1.01);
	glVertex3f(0.2, 0.9, -1.01);

	glEnd();
}
*/

void containerGlass_jetBridge()
{
	// Enable texturing
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, glassTexture);

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
	glBegin(GL_QUADS);

	// Front Face (Red)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(3, 1.2, 0);
	glVertex3f(0, 1.2, 0);

	// Back Face (Red)
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0, 0, -1.2);
	glVertex3f(3, 0, -1.2);
	glVertex3f(3, 1.2, -1.2);
	glVertex3f(0, 1.2, -1.2);

	// Bottom Face (Green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);
	glVertex3f(3, 0, -1.2);
	glVertex3f(0, 0, -1.2);

	// Top Face (Green)
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 1.2, 0);
	glVertex3f(3, 1.2, 0);
	glVertex3f(3, 1.2, -1.2);
	glVertex3f(0, 1.2, -1.2);

	glEnd();

	glPushMatrix();
	glRotated(90, 0, 1, 0);
	// glTranslated(-0.1, -0.1, 0);

	glBegin(GL_QUADS);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(1.2, 0, 0);
	glVertex3f(1.2, 1.2, 0);
	glVertex3f(0, 1.2, 0);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 3);
	glVertex3f(1.2, 0, 3);
	glVertex3f(1.2, 1.2, 3);
	glVertex3f(0, 1.2, 3);

	glEnd();

	glPopMatrix();
}

void containerGlassBigger_jetBridge()
{
	glBegin(GL_QUADS);

	// Front Face (Blue)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.2, 0.1, 0.01);
	glVertex3f(2.8, 0.1, 0.01);
	glVertex3f(2.8, 1.1, 0.01);
	glVertex3f(0.2, 1.1, 0.01);

	// Back Face (Blue)
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.2, 0.1, -1.21);
	glVertex3f(2.8, 0.1, -1.21);
	glVertex3f(2.8, 1.1, -1.21);
	glVertex3f(0.2, 1.1, -1.21);

	glEnd();
}

void containerConnector_jetBridge()
{
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	// glTranslated(-0.1, -0.1, 0);

	glBegin(GL_QUADS);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glVertex3f(1.2, 0, 0);
	glVertex3f(1.2, 1.2, 0);
	glVertex3f(0, 1.2, 0);

	// Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0, 0, 3);
	glVertex3f(1.2, 0, 3);
	glVertex3f(1.2, 1.2, 3);
	glVertex3f(0, 1.2, 3);

	glEnd();

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
	glPushMatrix();
	glTranslated(3, 0.1, -0.1);
	container_jetBridge();
	containerGlass_jetBridge();
	glPopMatrix();

	// containerConnector_jetBridge();
	// containerConnector_jetBridge();
	// containerBigger_jetBridge();
	// containerGlassBigger_jetBridge();

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
	//  (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
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

int main(int argc, char **argv)
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