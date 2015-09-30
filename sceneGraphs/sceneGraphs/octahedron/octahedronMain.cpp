/**
* @file	cubeMain.cpp
*
* @brief	Implements the cube main class.
*
* @author	Alvin
* @date	2015-09-28
*/

#include <GL/freeglut.h>
#include <math.h>
#include <iostream>
#include "octahedronNode.h"
using namespace std;
GLint screenSizeX = 800, screenSizeY = 600;
OctahedronNode* octahedronRoot = nullptr;
//----------- draw ---------------------------- 
void draw()
{
	octahedronRoot->draw();
}

void setupRootWithConfigFile(void) {
	pugi::xml_document configDoc;
	configDoc.load_file("config.xml");

	octahedronRoot = new OctahedronNode(Point3(0, 0, 0), configDoc.child("root"), true);
}

/**
* @fn	void setupProjection()
*
* @brief	Sets up the projection.
*
* @author	Alvin
* @date	2015-09-28
*/

void setupProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)screenSizeX / screenSizeY, 0.01f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
//----------- Display ---------------------------- 
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 350, 0, 0, 5, 0, 1.0f, 0);
	glColor3f(0, 0, 0);// specify color in r,g,b
	draw();
	glutSwapBuffers();
	glFlush();

}


//--------------- Initialization ------------------
void initialize(void)
{
	/*Init all squares based on the confige file*/
	setupRootWithConfigFile();
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glLineWidth(2.0);// specify width of line
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	setupProjection();
}

/**
* @fn	void keyInput(unsigned char key, int x, int y)
*
* @brief	Key input.
*
* @author	Alvin
* @date	2015-09-28
*
* @param	key	The key.
* @param	x  	The x coordinate.
* @param	y  	The y coordinate.
*/

void keyInput(unsigned char key, int x, int y) {
	switch (key) {
	case 'f':
		octahedronRoot->fold(1.0);
		break;
	case 'u':
		octahedronRoot->fold(-1.0);
		break;
	case 'a':
		octahedronRoot->translate(Vec3(-1, 0, 0));
		break;
	case 'A':
		octahedronRoot->translate(Vec3(1, 0, 0));
		break;
	case 'b':
		octahedronRoot->translate(Vec3(0, -1, 0));
		break;
	case 'B':
		octahedronRoot->translate(Vec3(0, 1, 0));
		break;
	case 'c':
		octahedronRoot->translate(Vec3(0, 0, -1));
		break;
	case 'C':
		octahedronRoot->translate(Vec3(0, 0, 1));
		break;
	case 'x':
		octahedronRoot->rotate(Vec3(-1, 0, 0));
		break;
	case 'X':
		octahedronRoot->rotate(Vec3(1, 0, 0));
		break;
	case 'y':
		octahedronRoot->rotate(Vec3(0, -1, 0));
		break;
	case 'Y':
		octahedronRoot->rotate(Vec3(0, 1, 0));
		break;
	case 'z':
		octahedronRoot->rotate(Vec3(0, 0, -1));
		break;
	case 'Z':
		octahedronRoot->rotate(Vec3(0, 0, 1));
		break;
	default:
		break;
	}
	glutPostRedisplay();
}



//  ------- Main ---------- 
void main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenSizeX, screenSizeY);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Cube");
	initialize();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyInput);
	glutMainLoop();
	delete octahedronRoot;
	octahedronRoot = nullptr;
}