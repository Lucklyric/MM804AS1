#include "octahedronNode.h"
#include <iostream>
#include <math.h>

OctahedronNode::OctahedronNode(Point3 position, pugi::xml_node node, bool isRoot) :BaseNode(position, node, isRoot)
{
	m_color = Vec3(node.attribute("r").as_double(), node.attribute("g").as_double(), node.attribute("b").as_double());
	m_rotateAngle = Vec3(0, 0, 0);
	/*if not root store the direction from the parent*/
	if (!m_isroot) m_parentCode = node.attribute("code").as_int();
	for each (pugi::xml_node child in node.children())
	{
		/*Append the current child*/
		m_children.push_back(new OctahedronNode(Point3(0, -m_width*(sqrtf(3)) / 6), child));
	}
}

OctahedronNode::~OctahedronNode() {
	for each (OctahedronNode* child in m_children)
	{
		delete child;
		child = nullptr;
	}
}

void OctahedronNode::draw() {

	glPushMatrix();

	if (!m_isroot) {
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
		glTranslatef(m_relativePosition._x, m_relativePosition._y, m_relativePosition._z);

		/*fold the node*/
		glRotatef(-m_foldAngle, 1, 0, 0);
	}

	/*Tranlate the node*/
	glTranslatef(m_relativePosition._x, m_relativePosition._y, m_relativePosition._z);
	if (!m_isroot) {

		/*Based on the parent direction to fold the current fold angle*/
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
	/*Rotate the node*/
	glRotatef(m_rotateAngle._z, 0.0, 0.0, 1.0);
	glRotatef(m_rotateAngle._y, 0.0, 1.0, 0.0);
	glRotatef(m_rotateAngle._x, 1.0, 0.0, 0.0);

	/*Change the color*/
	glColor3d(m_color._x, m_color._y, m_color._z);

	/*Draw the node*/
	glBegin(GL_TRIANGLES);
	glVertex3f(-m_width / 2, -m_width*(sqrtf(3)) / 6, 0);
	glVertex3f(0, m_width*(sqrtf(3)) / 3, 0);
	glVertex3f(m_width / 2, -m_width*(sqrtf(3)) / 6, 0);
	glEnd();

	/*Draw children*/
	for each (OctahedronNode* child in m_children)
	{
		child->draw();
	}
	glPopMatrix();
}

void OctahedronNode::fold(GLfloat angle) {
	m_foldAngle += angle;
	if (m_foldAngle < 0.0f) m_foldAngle = 0.0f;
	if (m_foldAngle > 70.5f) m_foldAngle = 70.5f;
	for each (OctahedronNode* child in m_children)
	{
		child->fold(angle);
	}
}