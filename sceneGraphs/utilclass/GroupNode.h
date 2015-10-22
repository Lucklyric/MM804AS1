//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: GroupNode.h
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


#if !defined(H_GROUPNODE)
#define H_GROUPNODE


#include <list>
#include <vector>
#include "pugixml/pugixml.hpp"
#include "Point3.h"
using namespace std;
enum ObjType { CUBE, SPHERE, TORUS, TEAPOT, CONE, TETRAHEDRON,OCTAHEDRON, SQUARE,OTHER};
class GroupNode 
{
private:
	list<GroupNode*> _children;
protected:
	GroupNode* _parent;
	float _tx, _ty, _tz, _angleX, _angleY, _angleZ, _foldAngle; //Add fold angle here
	bool _isWorld;
	/** @brief	The parent code. Using this for auto set translation and orientation based on the config file */
	int m_parentCode;
	/** @brief	The type. Identify the two different object of this assignment */
	ObjType _type;
    virtual void draw();
public:
	GroupNode(ObjType type = OTHER, pugi::xml_node node = pugi::xml_node(), bool isWorld = 0);
	virtual ~GroupNode();
	void addChild(GroupNode* node);
	void removeChild(GroupNode* node);
	void translate(float tx, float ty, float tz);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	bool fold(float angle);
	void inverseTransform() const;
    void render();
	GroupNode* getFirstChild() {
		if (getChildCount() == 0) return nullptr;
		return _children.front();
	}
	GroupNode* getParent() const;
	int getChildCount() const;
};

class ObjectNode : public GroupNode 
{
public:

	ObjectNode(ObjType type)
		: GroupNode(), 
		  _object(type), 
		 _scaleX(1.0f), _scaleY(1.0f), _scaleZ(1.0f),
		 _colorR(1.0f), _colorG(1.0f), _colorB(1.0f),
		 _width(40.0f)
		  {}
	//~ObjectNode() {} 
	void setObject(ObjType object, float scaleX, float scaleY, float scaleZ);
	void setColor(float colorR, float colorG, float colorB);
	float getWidth() { return  _width; }
private:
	ObjType _object;
	
	/** @brief	The width of the object. */
	float _width;
	float _scaleX, _scaleY, _scaleZ;
	float _colorR, _colorG, _colorB;
    void draw();
};

class CameraNode : public GroupNode 
{
private:
	float _fov, _aspect, _near, _far;
	static bool flag;
	void draw() {}; //does nothing!
	CameraNode()
		: GroupNode(),
		  _fov(60.0f), _aspect(1.0f), 
		  _near(1.0f), _far(1000.0f)
			{}
    CameraNode(const CameraNode&);
    CameraNode& operator = (const CameraNode&);
    static CameraNode* camera;
public:
    static CameraNode* getInstance();
	void perspective(float fov, float aspect, float near, float far);
	void projection() const;
	void viewTransform() const;
	~CameraNode() { flag = false; }
};

class LightNode : public GroupNode
{
private:
	int _glLight;
	void draw();
public:
	LightNode(int glLight)
		: GroupNode(),
		_glLight(glLight)
		{}
	void setLight(int glLight);   //added 18/8
	~LightNode() {}
};

#endif