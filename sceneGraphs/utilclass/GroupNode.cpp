//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: GroupNode.cpp
//  DESCRIPTION:
//             This code is part of the supplementary material for Chapter 3
//             Please refer to Appendix-B of the book for details.
//  ========================================================================
//  THE SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS",  WITHOUT WARRANTY OF ANY
//  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE AND  NONINFRINGEMENT.
//  IN NO EVENT SHALL  THE AUTHOR OR THE PUBLISHER BE LIABLE FOR  ANY CLAIM,
//  DAMAGES OR  OTHER LIABILITY,  WHETHER IN AN  ACTION OF CONTRACT, TORT OR
//  OTHERWISE, ARISING FROM,  OUT OF OR  IN CONNECTION  WITH THE SOFTWARE OR
//  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//  ========================================================================

#include "GroupNode.h"
#include <gl/glut.h>
#include <iostream>

GroupNode::GroupNode(ObjType type,pugi::xml_node node, bool isWorld)
	: _parent(NULL),
	_tx(0.0), _ty(0.0), _tz(0.0),
	_angleX(0.0), _angleY(0.0), _angleZ(0.0), _foldAngle(0.0),_isWorld(isWorld),_type(type)
{
	/* if not world store the direction from the parent 
	 * if the node is world store the root GroupNode
	 * if the node is empty means it is an object node just return
	 */
	if (node.empty()) return;

	/* World have a child which is the root groupnode*/
	if (_isWorld) {
		GroupNode* rootGroup = new GroupNode(type, node);
		addChild(rootGroup);
	}
	else {
		/* The parent code in config.xml file indicates the 
		 * relationship between the parent. Based on this 
		 * code we can set translation.
		 */
		m_parentCode = node.attribute("code").as_int();

		/* Initialize the object node*/
		ObjectNode* object = new ObjectNode(type);
		addChild(object);
		
		/* Set the color*/
		object->setColor(node.attribute("r").as_double(), node.attribute("g").as_double(), node.attribute("b").as_double());
		
		/* Go through all the child node*/
		for each (pugi::xml_node child in node.children())
		{
			int code = child.attribute("code").as_int();
			Point3 childTranlation;

			/* SQUARE for subquestion 1*/
			if (type == SQUARE) {
				switch (code)
				{
				case 0:
					childTranlation = Point3(0, -object->getWidth() / 2.0f, 0);
					break;
				case 1:
					childTranlation = Point3(-object->getWidth() / 2.0f, 0, 0);
					break;
				case 2:
					childTranlation = Point3(0, object->getWidth() / 2.0f, 0);
					break;
				case 3:
					childTranlation = Point3(object->getWidth() / 2.0f, 0, 0);
					break;
				default:
					break;
				}
			}
			/* OCTAHEDRON for subquestion 2*/
			else if(type == OCTAHEDRON) {
				childTranlation = Point3(0, -object->getWidth()*(sqrtf(3)) / 6);
			}
			
			/* Initilize the next groupnode*/
			GroupNode* childGroup = new GroupNode(type, child);

			/* Set the predefined translation and add to current goupnode*/
			childGroup->translate(childTranlation._x, childTranlation._y, childTranlation._z);
			addChild(childGroup);
		}
	}
}

GroupNode::~GroupNode() {
	for each(GroupNode* child in _children) {
		delete child;
		child = nullptr;
	}
	_children.clear();
}

void GroupNode::addChild(GroupNode* node)
{
	_children.push_back(node);
	node->_parent = this;
}

void GroupNode::removeChild(GroupNode* node)
{
	_children.remove(node);
	delete node;
	node = nullptr;
}

int GroupNode::getChildCount() const
{
	return _children.size();
}

GroupNode* GroupNode::getParent() const
{
	return _parent;
}

void GroupNode::translate(float tx, float	ty, float tz)
{
	_tx += tx;
	_ty += ty;
	_tz += tz;
}

void GroupNode::rotateX(float angle)
{
	_angleX += angle;
}

void GroupNode::rotateY(float angle)
{
	_angleY += angle;
}

void GroupNode::rotateZ(float angle)
{
	_angleZ += angle;
}

void GroupNode::render()
{
    if (this->_parent != NULL) return;
	draw();
}

bool GroupNode::fold(float angle) {
	bool isFinished = false;
	/* Update the fold angle*/
	_foldAngle += angle;
	if (_type == SQUARE) {
		if (_foldAngle < 0.0f) { _foldAngle = 0.0f; isFinished = true; }
		if (_foldAngle > 90.0f) { _foldAngle = 90.0f; isFinished = true; }
	}
	else if (_type == OCTAHEDRON) {
		if (_foldAngle < 0.0f) { _foldAngle = 0.0f; isFinished = true; }
		if (_foldAngle > 70.5f) { _foldAngle = 70.5f; isFinished = true; }
	}
	/*Update the child node*/
	for each (GroupNode* child in _children)
	{
		if (child->getChildCount() != 0) child->fold(angle);
	}
	return isFinished;
}

void GroupNode::draw()
{
	list<GroupNode*>::iterator i;
	glPushMatrix();
	if (!_isWorld) {
		if (_type == SQUARE) {
			/*Return back to the parent's origin*/
			glTranslatef(_tx, _ty, _tz);
			/*Based on the parent direction to fold the current fold angle*/
			switch (m_parentCode)
			{
			case 0:
				glRotatef(-_foldAngle, 1, 0, 0);
				break;
			case 1:
				glRotatef(_foldAngle, 0, 1, 0);
				break;
			case 2:
				glRotatef(_foldAngle, 1, 0, 0);
				break;
			case 3:
				glRotatef(-_foldAngle, 0, 1, 0);
				break;
			default:
				break;
			}
		}
		else if (_type == OCTAHEDRON)
		{
			/*Return back to the parent's origin*/
			switch (m_parentCode)
			{
			case 0:
				glRotatef(120.0f, 0, 0, 1);
				break;
			case 1:
				glRotatef(0, 0, 0, 1);
				break;
			case 2:
				glRotatef(-120.0f, 0, 0, 1);
				break;
			default:
				break;
			}
			glTranslatef(_tx, _ty, _tz);

			/*fold the node*/
			glRotatef(-_foldAngle, 1, 0, 0);
		}
	}
	
	    glTranslated(_tx, _ty, _tz);
		if (_type == OCTAHEDRON)
		{
			if (!_isWorld) {
				/*Based on the parent direction force back to correspond coordinate*/
				switch (m_parentCode)
				{
				case 0:
					glRotatef(60.0f, 0, 0, 1);
					break;
				case 1:
					glRotatef(180.f, 0, 0, 1);
					break;
				case 2:
					glRotatef(-60.0f, 0, 0, 1);
					break;
				default:
					break;
				}
			}
		}
		glRotatef(_angleZ, 0.0f, 0.0f, 1.0f);
		glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
		glRotatef(_angleX, 1.0f, 0.0f, 0.0f);

		for(i = _children.begin(); i != _children.end(); i++)
			(*i)->draw();

	glPopMatrix();
}

void GroupNode::inverseTransform() const
{
		glRotatef(-_angleX, 1.0f, 0.0f, 0.0f);
		glRotatef(-_angleY, 0.0f, 1.0f, 0.0f);
		glRotatef(-_angleZ, 0.0f, 0.0f, 1.0f);
		glTranslated(-_tx, -_ty, -_tz);
}

void ObjectNode::draw()
{
	glColor3f(_colorR, _colorG, _colorB);
	glPushMatrix();
	    glTranslated(_tx, _ty, _tz);
		glRotatef(_angleZ, 0.0f, 0.0f, 1.0f);
		glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
		glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
		glScalef(_scaleX, _scaleY, _scaleZ);
		switch (_object)
		{
			case CUBE: glutSolidCube(1.0); break;
			case SPHERE: glutSolidSphere(1.0, 36, 18); break;
			case TORUS: glutSolidTorus(0.2, 1.0, 36, 18); break;
			case TEAPOT: glutSolidTeapot(1.0); break;
			case CONE: glutSolidCone(1.0, 1.0, 36, 10); break;
			case TETRAHEDRON: glutSolidTetrahedron(); break;
			case SQUARE:
				/*Draw the node*/
				glRectf(-_width / 2, -_width / 2, _width / 2, _width / 2);
				break;
			case OCTAHEDRON:
				/*Draw the node*/
				glBegin(GL_TRIANGLES);
				glVertex3f(-_width / 2, -_width*(sqrtf(3)) / 6, 0);
				glVertex3f(0, _width*(sqrtf(3)) / 3, 0);
				glVertex3f(_width / 2, -_width*(sqrtf(3)) / 6, 0);
				glEnd();
				break;
		}
		glEnd();
	glPopMatrix();
}

void ObjectNode::setObject(ObjType object, float scaleX, float scaleY, float scaleZ)
{
	_object = object;
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;
}

void ObjectNode::setColor(float colorR, float colorG, float colorB)
{
	_colorR = colorR;
	_colorG = colorG;
	_colorB = colorB;
}

CameraNode* CameraNode::camera = NULL;
bool CameraNode::flag = false;
CameraNode* CameraNode::getInstance()
{
	if(!flag)
	{
		camera = new CameraNode();
		flag = true;
	}
	return camera;
}

void CameraNode::perspective(float fov, float aspect, float mnear, float mfar)
{
	_fov = fov;
	_aspect = aspect;
	_near = mnear;
	_far = mfar;
}

void CameraNode::projection() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_fov, _aspect, _near, _far);
}

void CameraNode::viewTransform() const
{
	if(flag)
	{
		GroupNode* node = camera;
		while(node)
		{
			node->inverseTransform();
			node = node->getParent();
		}
	}
}

void LightNode::draw()
{
	float position[3] = {0};

	glPushMatrix();
	    glTranslated(_tx, _ty, _tz);
		glRotatef(_angleZ, 0.0f, 0.0f, 1.0f);
		glRotatef(_angleY, 0.0f, 1.0f, 0.0f);
		glRotatef(_angleX, 1.0f, 0.0f, 0.0f);
		glLightfv(_glLight, GL_POSITION, position);
	glPopMatrix();
}

void LightNode::setLight(int glLight)
{
	_glLight = glLight;
}