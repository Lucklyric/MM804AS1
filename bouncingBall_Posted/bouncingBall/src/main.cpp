
//  AUTHOR:  Herb Yang
//  June 22, 2015

#include <GL/freeglut.h>
#include "ball.h"
#include "box.h"
#include "block.h"
#include <time.h>
#include <iostream>
GLint screenSizeX=400, screenSizeY=600;
const int NUMBER_OF_BALLS = 20;
GLfloat radius=10;
GLfloat updateTime = 1;
GLint score = 0;
char s[10];
ball bouncingBall[NUMBER_OF_BALLS];

box wall(screenSizeY-1.0f, 1.0f, 1.0f, screenSizeX-1.0f, 0.0f,1.0f,0.0f, false);
block paddle(screenSizeX/2.0f, screenSizeY/8.0f, 30.0f, 80.0f, 0.0f, 0.5f, 0.5f, true);

// ---- display some text -----
void showText(GLfloat x, GLfloat y, char* s, GLfloat r, GLfloat g, GLfloat b){
	glColor3f(r, g, b);
	glRasterPos2f(x,y);
	while(*s){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s);
		s++;
	}
}

//----------- Display ---------------------------- 
void display(void) 
{ 
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();     //glColor3f(0, 0, 0);
	sprintf_s(s,"%d",score);
	showText(20.0f,20.0f,"Score =",0.0f, 0.0f, 1.0f);
	showText(100.0f,20.0f,s,0.0f,0.0f,1.0f);
	wall.draw();
	paddle.draw();
	for(int i =0;i<NUMBER_OF_BALLS;i++){
		bouncingBall[i].draw();
	}
	glutSwapBuffers();
	glFlush(); 
} 

//--------- Mouse handler ------------------------------------
void mouse(int button, int state, int x, int y)
{
	if(button==GLUT_LEFT_BUTTON && state ==GLUT_DOWN)
	{
		paddle.setLoc(x);
		glutPostRedisplay();
	}
}

//--------------- Initialization ------------------
void initialize(void)
{
	GLfloat x,y,incx,incy,r,g,b;
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screenSizeX, 0, screenSizeY);
	srand(time(0));
	int row=120;
	int column =radius;
	y = row; x = column;
	for(int  i =0;i<NUMBER_OF_BALLS;i++){
		incx = (rand() % 2) + 1;
		incy = (rand() % 2) + 1;
		column +=3*radius;
		if(column>screenSizeX){
			row  += 3*radius;
			column = radius;
		}
		x = column;
		y = row;
		r = rand()%10/10.0f; g = rand()%10/10.0f; b = rand()%10/10.0f;
		bouncingBall[i].setLoc(x, y, radius, r, g, b);		
		bouncingBall[i].setDir(incx,incy);
	}
}

void update(int value)
{
	// add code below
	/*Balls' update*/
	for (int i = 0; i<NUMBER_OF_BALLS; i++) {
		bouncingBall[i].move();
		if (bouncingBall[i].boxHandler(wall)) { score--; }
		if (bouncingBall[i].boxHandler(paddle)) { score++; }
		for(int j = i+1; j < NUMBER_OF_BALLS; j++) {
			bouncingBall[i].ballHandler(bouncingBall[j]);
		}
	}

	// add code above
	sprintf_s(s,"%d",score);
	showText(100.0f,20.0f,s,0.0f,0.0f,1.0f);
	glutPostRedisplay();
	glutTimerFunc(updateTime,update,0);
}
//  ------- Main ---------- 
void main(int argc, char **argv) 
{ 
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  
	glutInitWindowSize(screenSizeX, screenSizeY);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Pong");
	initialize();
	glutTimerFunc(updateTime,update,0);
	glutDisplayFunc(display); 
	glutMouseFunc(mouse);
	glutMainLoop(); 
}