#pragma once
#include <GL\freeglut.h>
#include <vector>
#include "../../utilclass/Point3.h"
#include "../../utilclass/pugixml/pugixml.hpp"
#include "../../utilclass/baseNode.h"
using namespace std;
class OctahedronNode:public BaseNode
{
public:
	OctahedronNode(Point3 position, pugi::xml_node node, bool isRoot=0);
	~OctahedronNode();
	/**
	* @fn	void OctahedronNode::draw();
	*
	* @brief	Draws this object.
	*
	* @author	Alvin
	* @date	2015-09-28
	*/
	void draw();

	/**
	* @fn	void OctahedronNode::fold(GLfloat angle);
	*
	* @brief	Folds the given angle.
	*
	* @author	Alvin
	* @date	2015-09-28
	*
	* @param	angle	The angle.
	*/

	void fold(GLfloat angle);

private:

	/** @brief	The childs of this node. */
	vector<OctahedronNode*> m_children;
};

