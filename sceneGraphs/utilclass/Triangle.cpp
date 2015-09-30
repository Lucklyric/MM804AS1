//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: Triangle.cpp
//  DESCRIPTION:
//             This code is part of the supplementary material for Chapter 2
//             Please refer to Appendix-A of the book for details.
//  ========================================================================
//  THE SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS",  WITHOUT WARRANTY OF ANY
//  KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE AND  NONINFRINGEMENT.
//  IN NO EVENT SHALL  THE AUTHOR OR THE PUBLISHER BE LIABLE FOR  ANY CLAIM,
//  DAMAGES OR  OTHER LIABILITY,  WHETHER IN AN  ACTION OF CONTRACT, TORT OR
//  OTHERWISE, ARISING FROM,  OUT OF OR  IN CONNECTION  WITH THE SOFTWARE OR
//  THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//  ========================================================================

#include <cmath>
#include "Triangle.h"
#include <gl/glut.h>
using namespace std;

float Triangle::EPS = (float)1.E-6;

float Triangle::area() const
{
    return (normal()->norm())*0.5f;
}

float Triangle::signedArea2D() const
{
    float areaSigned = area();
    float zdir = normal()->_z;
    if (zdir < 0) areaSigned = -areaSigned;
    return areaSigned;
}

float Triangle::signedArea3D(const Vec3* w) const
{
    float areaSigned = area();
    float dotProduct = normal()->dot(w);
    if (dotProduct < 0) areaSigned = -areaSigned;
    return areaSigned;
}

Vec3* Triangle::normal() const
{
    Vec3* u = _b->subtract(_a);
    Vec3* v = _c->subtract(_a);
    return u->cross(v);
}

Point3* Triangle::barycentricCoords(const Point3* p) const
{
    Vec3* w = normal();
    float areaFull = area();
    Triangle* t1 = new Triangle(p, _b, _c);
    Triangle* t2 = new Triangle(p, _c, _a);
    Triangle* t3 = new Triangle(p, _a, _b);
    float lamda1 = (t1->signedArea3D(w))/areaFull;
    float lamda2 = (t2->signedArea3D(w))/areaFull;
    float lamda3 = (t3->signedArea3D(w))/areaFull;
    return new Point3(lamda1, lamda2, lamda3);
}

Point3* Triangle::barycentricMap(const Point3* p, const Triangle* t) const
{
    Point3* bc_coords = t->barycentricCoords(p);
    Point3* temp1 = _a->scalarMult(bc_coords->_x);   //Multiply first vertex by lamda1
    Point3* temp2 = _b->scalarMult(bc_coords->_y);   //Multiply second vertex by lamda2
    Point3* temp3 = _c->scalarMult(bc_coords->_z);   //Multiply third vertex by lamda3
    return temp1->add(temp2)->add(temp3);
}

bool Triangle::isInside(const Point3* p) const
{
    Point3* bc_coords = barycentricCoords(p);
    float sum = bc_coords->_x + bc_coords->_y + bc_coords->_z;
    if(fabs(sum-1.0f) > EPS) return false;
    if(bc_coords->_x < 0 || bc_coords->_y < 0 || bc_coords->_z < 0)
        return false;
    return true;
}

void Triangle::draw() const
{
    glBegin(GL_TRIANGLES);
       glVertex4f(_a->_x, _a->_y, _a->_z, _a->_h);
       glVertex4f(_b->_x, _b->_y, _b->_z, _b->_h);
       glVertex4f(_c->_x, _c->_y, _c->_z, _c->_h);
    glEnd();
}

