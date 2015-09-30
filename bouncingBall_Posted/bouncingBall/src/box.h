#ifndef BOX_H
#define BOX_H
class box {
	GLfloat ty,by, lx,rx;		//boundary
	GLfloat cr, cg, cb;		// color of box default to white
	bool fillFlag;          // true if it is solid
public:
	box(GLfloat t, GLfloat b, GLfloat l, GLfloat r, GLfloat red, GLfloat green, GLfloat blue, bool f){
		ty = t;
		by = b;
		lx = l;
		rx = r;
		cr = red;
		cg = green;
		cb = blue;
		fillFlag = f;
	};
	void setBox(GLfloat t, GLfloat b, GLfloat l, GLfloat r){
		ty = t;
		by = b;
		lx = l;
		rx = r;
	};
	bool isFilled(){
		return fillFlag;
	}
	GLfloat top(){
		return ty;
	};
	GLfloat bottom(){
		return by;
	};
	GLfloat left(){
		return lx;
	};
	GLfloat right(){
		return rx;
	};
	GLfloat getWidth() {
		return (rx - lx);
	};
	GLfloat getHeight() {
		return (ty - by);
	};
	GLfloat getCenterX() {
		return (lx + getWidth() / 2.0f);
	};
	GLfloat getCenterY() {
		return (by + getHeight() / 2.0f);
	};
	void draw(){
		glColor3f(cr,cg,cb);// color of box
		if(fillFlag)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}	
		//glBegin(GL_POLYGON); // The stack to draw the wall
		// add code below to draw a rectangle
		glRectf(lx, ty, rx, by);
		// add code above 	
		//glEnd();
		glFlush();
	};
};
#endif