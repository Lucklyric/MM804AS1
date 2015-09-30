#pragma once
#include <GL\freeglut.h>
#include <vector>
#include "Point3.h"
#include "pugixml/pugixml.hpp"
using namespace std;
class BaseNode
{
public:
	BaseNode(Point3 position, pugi::xml_node node, bool isRoot = 0);
	virtual ~BaseNode() ;

	/**
	 * @fn	virtual void BaseNode::draw() = 0;
	 *
	 * @brief	Draws this object.
	 *
	 * @author	Alvin
	 * @date	2015-09-28
	 */
	virtual void draw() = 0;


	/**
	* @fn	virtual void BaseNode::fold(bool type = 0);
	*
	* @brief	Folds with the given type.
	*
	* @author	Alvin
	* @date	2015-09-28
	*
	* @param	type	true to type.
	*/
	virtual void fold(GLfloat angle) = 0;

	/**
	* @fn	void BaseNode::translate(Vec3 vector);
	*
	* @brief	Translates wiht the given vector.
	*
	* @author	Alvin
	* @date	2015-09-28
	*
	* @param	vector	The vector to apply the translation.
	*/
	void translate(Vec3 vector);

	/**
	* @fn	void BaseNode::rotate(Vec3 vector);
	*
	* @brief	Rotates with the given vector.
	*
	* @author	Alvin
	* @date	2015-09-28
	*
	* @param	vector	The vector .
	*/

	void rotate(Vec3 vector);
protected:
	/** @brief	The width of the square. */
	GLfloat m_width;

	/** @brief	The relative position to the parent. */
	Point3 m_relativePosition;

	/** @brief	The rotate angle. */
	Vec3 m_rotateAngle;

	/** @brief	The fold angle. */
	GLfloat m_foldAngle;

	/** @brief	The parent code. */
	int m_parentCode;

	/** @brief	The color of the square. */
	Vec3 m_color;

	/** @brief	Whether the node is a root. */
	bool m_isroot;

};

