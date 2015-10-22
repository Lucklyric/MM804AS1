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
#include "../../utilclass/GroupNode.h"
using namespace std;
GLint screenSizeX = 800, screenSizeY = 600;
OctahedronNode* octahedronRoot = nullptr;
GroupNode* world = nullptr;
GroupNode* octRootGroup = nullptr;
int status = 0; //0-idle state,1-unfolding,2-folding;
//----------- draw ---------------------------- 
void draw()
{
	//ctahedronRoot->draw();
	world->render();
}

void setupRootWithConfigFile(void) {
	pugi::xml_document configDoc;
	/*Input the xml config file*/
	configDoc.load_file("config.xml");

	//octahedronRoot = new OctahedronNode(Point3(0, 0, 0), configDoc.child("root"), true);
	/*According to the config file initialize the word*/
	world = new GroupNode(OCTAHEDRON,configDoc.child("root"),true);
	/*Get the Cube root groupnode*/
	octRootGroup = world->getFirstChild();
}

/**
* @fn	void closeFun()
*
* @brief	Closes the fun.
* 			Deal with the memory before kill the program
*
* @author	Alvin
* @date	2015-10-20
*/

void closeFun() {
	if (world) delete world;
	world = nullptr;
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
	/*Setting up projection*/
	gluPerspective(60.0f, (float)screenSizeX / screenSizeY, 0.01f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	/*Enable Z test*/
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
//----------- Display ---------------------------- 
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*Setting up camera*/
	gluLookAt(0, 0, 350, 0, 0, 5, 0, 1.0f, 0);
	glColor3f(0, 0, 0);
	/*Render the world*/
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
		/*set to folding state*/
		status = 2; 
	case 'F':
		//squareRoot->fold(5.0);
		octRootGroup->fold(5.0);
		break;
	case 'u':
		/*set to unfolding state*/
		status = 1; 
	case 'U':
		//squareRoot->fold(-5.0);
		octRootGroup->fold(-5.0);
		break;
	case 'a':
		//squareRoot->translate(Vec3(-1, 0, 0));
		octRootGroup->translate(-1, 0, 0);
		break;
	case 'A':
		//squareRoot->translate(Vec3(1, 0, 0));
		octRootGroup->translate(1, 0, 0);
		break;
	case 'b':
		//squareRoot->translate(Vec3(0, -1, 0));
		octRootGroup->translate(0, -1, 0);
		break;
	case 'B':
		//squareRoot->translate(Vec3(0, 1, 0));
		octRootGroup->translate(0, 1, 0);
		break;
	case 'c':
		//squareRoot->translate(Vec3(0, 0, -1));
		octRootGroup->translate(0, 0, -1);
		break;
	case 'C':
		//squareRoot->translate(Vec3(0, 0, 1));
		octRootGroup->translate(0, 0, 1);
		break;
	case 'x':
		//squareRoot->rotate(Vec3(-1, 0, 0));
		octRootGroup->rotateX(-1);
		break;
	case 'X':
		//squareRoot->rotate(Vec3(1, 0, 0));
		octRootGroup->rotateX(1);
		break;
	case 'y':
		//squareRoot->rotate(Vec3(0, -1, 0));
		octRootGroup->rotateY(-1);
		break;
	case 'Y':
		//squareRoot->rotate(Vec3(0, 1, 0));
		octRootGroup->rotateY(1);
		break;
	case 'z':
		//squareRoot->rotate(Vec3(0, 0, -1));
		octRootGroup->rotateZ(-1);
		break;
	case 'Z':
		//squareRoot->rotate(Vec3(0, 0, 1));
		octRootGroup->rotateZ(1);
		break;
	case 'q':
		closeFun();
		exit(0);
	default:
		break;
	}
	glutPostRedisplay();
}

void update(int value) {
	switch (status)
	{
	case 1:
		if (octRootGroup->fold(-1.0)) status = 0;
		break;
	case 2:
		if (octRootGroup->fold(1.0)) status = 0;
		break;
	default:
		break;
	}
	glutPostRedisplay();
	/*Update*/
	glutTimerFunc(1, update, 0);
}


//  ------- Main ---------- 
void main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenSizeX, screenSizeY);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Octanhedron");
	initialize();
	glutTimerFunc(1, update, 0);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyInput);
	glutCloseFunc(closeFun);
	glutMainLoop();
}