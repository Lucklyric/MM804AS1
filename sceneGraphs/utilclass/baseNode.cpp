#include "baseNode.h"



BaseNode::BaseNode(Point3 position, pugi::xml_node node, bool isRoot): m_relativePosition(position),
m_isroot(isRoot),
m_width(40),
m_foldAngle(0),
m_parentCode(0)
{

}


BaseNode::~BaseNode() {

}
void BaseNode::translate(Vec3 vector) {
	/*tranlate the current node*/
	m_relativePosition._x += vector._x;
	m_relativePosition._y += vector._y;
	m_relativePosition._z += vector._z;
}

void BaseNode::rotate(Vec3 vector) {
	/*rotate the current node*/
	m_rotateAngle._x += vector._x;
	if (m_rotateAngle._x > 360.0f) m_rotateAngle._x -= 360.0f;

	m_rotateAngle._y += vector._y;
	if (m_rotateAngle._y > 360.0f) m_rotateAngle._y -= 360.0f;

	m_rotateAngle._z += vector._z;
	if (m_rotateAngle._z > 360.0f) m_rotateAngle._z -= 360.0f;
}