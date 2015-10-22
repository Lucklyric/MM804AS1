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
	void ballHandler(ball &targetBall) {
		/*Detect whether the length between two balls is less or equal to the sum of two balls radius*/
		if ((pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2)) <= pow(radius + (targetBall.radius), 2)) {
			/*Equation given from assignment*/
			GLfloat dotProduct = ((vX - targetBall.vX)*(locX - targetBall.locX) + (vY - targetBall.vY)*(locY - targetBall.locY)) / (pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2));
	
			/*Update the current ball's volocity*/
			vX -= (dotProduct*(locX - targetBall.locX));
			vY -= (dotProduct*(locY - targetBall.locY));

			/*Update the target ball's volocity*/
			GLfloat targetVx = targetBall.vX - dotProduct*(targetBall.locX - locX);
			GLfloat targetVy = targetBall.vY - dotProduct*(targetBall.locY - locY);
			targetBall.setDir(targetVx, targetVy);

			/*If two ball's current has overlaping need force to extend the distance to each other to avoid some issues*/
			locX = targetBall.locX + (locX - targetBall.locX) / (sqrt(pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2)) / (radius + targetBall.radius));
			locY = targetBall.locY + (locY - targetBall.locY) / (sqrt(pow(locX - targetBall.locX, 2) + pow(locY - targetBall.locY, 2)) / (radius + targetBall.radius));
		}
	}

	// inside is to return true if the point is inside the box
	// Note: the boundary must include the radius of the ball
	

	// add collision handler with a box or a paddle below
	bool boxHandler(box targetBox) {
		bool result = false;
		/*Check if it is a wll or paddle*/
		bool isWall = !targetBox.isFilled();
		/*Store the collision of 4 direction*/
		bool collDir[4] = { false,false,false,false };

		if (isWall) {
			/*Wall's collision*/
			if (locX < (targetBox.left() + radius)) { locX = targetBox.left() + radius; collDir[3] = true; }
			if (locX > (targetBox.right() - radius)) { locX = targetBox.right() - radius; collDir[1] = true; }
			if (locY > (targetBox.top() - radius)) { locY = targetBox.top() - radius; collDir[0] = true; }
			if (locY < (targetBox.bottom() + radius)) { locY = targetBox.bottom() + radius; collDir[2] = true; }
		}
		else
		{
			/*Paddle collision*/
			if ((locX >(targetBox.left() - radius)) && (locX < (targetBox.right() + radius)) && (locY < (targetBox.top()+radius))&& (locY > (targetBox.bottom() - radius))) {
				/*Handle the overlaping problem*/
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
		/* According to the collDir result return true for wall decrease the mark and for paddle increase the mark
		 * Also update the ball's velocity here
		 */
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
		glColor3f(r,g,b);// color of ball
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON); // The stack to draw the ball
		// add code below to compute and draw points on a circle
		for (int i = 0; i < 360; i++) {
			/*get the current angle*/ 
			GLfloat theta = 2.0f * 3.1415926f * float(i) / float(360);
			/*calculate the x component*/
			GLfloat x = this->radius * cosf(theta); 
			/*calculate the y component*/
			GLfloat y = this->radius * sinf(theta);
			/*output vertex*/
			glVertex2f(this->locX+x, this->locY+y);
		}
		// add code above to draw a circle
		glEnd();
		glFlush();
	}
};
#endif