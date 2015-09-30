#ifndef BALL_H
#define BALL_H
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "box.h"
const double PI  =3.141592653589793238463;
class ball{
	GLfloat lastX, lastY;
	GLfloat locX, locY, radius;
	GLfloat r,g,b;
	GLfloat vX, vY; // ball direction
public:
	void setLoc(GLfloat x, GLfloat y, GLfloat rad, GLfloat red, GLfloat green, GLfloat blue){
		locX = x;
		locY = y;
		lastX = locX;
		lastY = locY;
		radius = rad;
		r = red;
		g = green;
		b = blue;
	};
	void setDir(GLfloat a, GLfloat b){
		vX = a;
		vY = b;
	};
	void move(){
		lastX = locX;
		lastY = locY;
		locX += vX;
		locY += vY;
	};
	// add collision handler with another ball below
	void ballHandler(ball targetBall) {
		if ((pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2)) <= pow(radius + (targetBall.radius), 2)) {
			float dotProduct = ((vX - targetBall.vX)*(locX - targetBall.locX) + (vY - targetBall.vY)*(locY - targetBall.locY)) / (pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2));
	
			vX -= (dotProduct*(locX - targetBall.locX));
			vY -= (dotProduct*(locY - targetBall.locY));

			float targetVx = targetBall.vX - dotProduct*(targetBall.locX - locX);
			float targetVy = targetBall.vY - dotProduct*(targetBall.locY - locY);
			targetBall.setDir(targetVx, targetVy);
			locX = targetBall.locX + (locX - targetBall.locX) / (sqrt(pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2)) / (radius + targetBall.radius));
			locY = targetBall.locY + (locY - targetBall.locY) / (sqrt(pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2)) / (radius + targetBall.radius));
		}
	}

	// inside is to return true if the point is inside the box
	// Note: the boundary must include the radius of the ball
	

	// add collision handler with a box or a paddle below
	bool boxHandler(box targetBox) {
		bool result = false;
		bool isWall = !targetBox.isFilled();
		bool collDir[4] = { false,false,false,false };
		if (isWall) {
			if (locX < (targetBox.left() + radius)) { locX = targetBox.left() + radius; collDir[3] = true; }
			if (locX > (targetBox.right() - radius)) { locX = targetBox.right() - radius; collDir[1] = true; }
			if (locY > (targetBox.top() - radius)) { locY = targetBox.top() - radius; collDir[0] = true; }
			if (locY < (targetBox.bottom() + radius)) { locY = targetBox.bottom() + radius; collDir[2] = true; }
		}
		else
		{
			if ((locX >(targetBox.left() - radius)) && (locX < (targetBox.right() + radius)) && (locY < (targetBox.top()+radius))&& (locY > (targetBox.bottom() - radius))) {
				
				if (abs((locX - targetBox.getCenterX())/(locY - targetBox.getCenterY())) < (targetBox.getWidth()/targetBox.getHeight())) {
					if (locY > targetBox.getCenterY()) {
						locY = targetBox.top() + radius;
						collDir[0] = true;
					}
					else {
						locY = targetBox.bottom() - radius;
						collDir[2] = true;
					}
					
				}
				else {
					if (locX < targetBox.getCenterX()) {
						locX = targetBox.left() - radius;
						collDir[3] = true;
					}
					else {
						locX = targetBox.right() + radius;
						collDir[1] = true;
					}
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (collDir[i] == true)
			{
				if (isWall) {
					if (i == 2) result = true;
				}
				else {
					result = true;
				}
				if (i == 0 || i == 2) {
					vY = -vY;
				}
				else {
					vX = -vX;
				}
			}
		}
		return result;

	};



	// add collision handler with a box or a paddle above
	void draw(){
		GLfloat angle;
		glColor3f(r,g,b);// color of ball
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON); // The stack to draw the ball
		// add code below to compute and draw points on a circle
		for (int i = 0; i < 360; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(360);//get the current angle 
			float x = this->radius * cosf(theta);//calculate the x component 
			float y = this->radius * sinf(theta);//calculate the y component 
			glVertex2f(this->locX+x, this->locY+y);//output vertex 
		}
		// add code above to draw a circle
		glEnd();
		glFlush();
	}
};
#endif