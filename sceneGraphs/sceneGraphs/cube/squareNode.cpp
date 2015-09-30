#include "squareNode.h"
#include <iostream>
#include <math.h>
SquareNode::SquareNode(Point3 position, pugi::xml_node node, bool isRoot):BaseNode(position,node,isRoot)
{
	m_color = Vec3(node.attribute("r").as_double(), node.attribute("g").as_double(), node.attribute("b").as_double());
	m_rotateAngle = Vec3(0, 0, 0);
	/*if not root store the direction from the parent*/
	if (!m_isroot) m_parentCode = node.attribute("code").as_int();
	for each (pugi::xml_node child in node.children())
	{
		int code = child.attribute("code").as_int();
		Point3 childPosition;
		switch (code)
		{
			case 0:
				childPosition = Point3(0, -m_width / 2.0f, 0);
				break;
			case 1:
				childPosition = Point3(-m_width/2.0f, 0, 0);
				break;
			case 2:
				childPosition = Point3(0, m_width / 2.0f, 0);
				break;
			case 3:
				childPosition = Point3(m_width / 2.0f, 0, 0);
				break;
			default:
				break;
		}
		/*Append the current child*/
		m_children.push_back(new SquareNode(childPosition, child));
	}
}

SquareNode::~SquareNode() {
	for each (SquareNode* child in m_children)
	{
		delete child;
		child = nullptr;
	}
}

void SquareNode::draw() {
	glPushMatrix();
	if (!m_isroot) {
		/*Return back to the parent's origin*/
		glTranslatef(m_relativePosition._x, m_relativePosition._y, m_relativePosition._z);

		/*Based on the parent direction to fold the current fold angle*/
		switch (m_parentCode)
		{
		case 0:
			glRotatef(-m_foldAngle, 1, 0, 0);
			break;
		case 1:
			glRotatef(m_foldAngle, 0, 1, 0);
			break;
		case 2:
			glRotatef(m_foldAngle, 1, 0, 0);
			break;
		case 3:
			glRotatef(-m_foldAngle, 0, 1, 0);
			break;
		default:
			break;
		}
	}

	/*Tranlate the node*/
	glTranslatef(m_relativePosition._x,m_relativePosition._y,m_relativePosition._z);

	/*Rotate the node*/
	glRotatef(m_rotateAngle._z, 0.0, 0.0, 1.0);
	glRotatef(m_rotateAngle._y, 0.0, 1.0, 0.0);
	glRotatef(m_rotateAngle._x, 1.0, 0.0, 0.0);
	
	/*Change the color*/
	glColor3d(m_color._x, m_color._y, m_color._z);
	
	/*Draw the node*/
	glRectf(-m_width / 2, -m_width / 2, m_width / 2, m_width / 2);
	
	/*Draw children*/
	for each (SquareNode* child in m_children)
	{
		child->draw();
	}
	glPopMatrix();
}

void SquareNode::fold(GLfloat angle) {
	m_foldAngle += angle;
	if (m_foldAngle < 0.0f) m_foldAngle = 0.0f;
	if (m_foldAngle > 90.0f) m_foldAngle = 90.0f;
	for each (SquareNode* child in m_children)
	{
		child->fold(angle);
	}
}