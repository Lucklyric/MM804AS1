//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: Point3.cpp
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

#include <iostream>
#include <cmath>
#include "Point3.h"
using namespace std;

float Point3::EPS = (float)1.E-6;

Point3* Point3::add(const Point3* p) const
{
	return new Point3(_x + p->_x, _y + p->_y, _z + p->_z);
}

Vec3* Point3::subtract(const Point3* p) const
{
	return new Vec3(_x - p->_x, _y - p->_y, _z - p->_z);
}

Point3* Point3::scalarMult(float term) const
{
	return new Point3(_x*term, _y*term, _z*term);
}

Point3* Point3::lerp(float t, const Point3* p) const
{
	return new Point3( (1-t)*_x + t*p->_x, (1-t)*_y + t*p->_y, (1-t)*_z + t*p->_z);
}

float Point3::norm() const
{
	return sqrt(_x*_x + _y*_y + _z*_z);
}

float Point3::atIndex(int i) const
{
	if (i==0) return _x;
	else if (i==1) return _y;
	else if (i==2) return _z;
	else if (i==3) return _h;
	else return 0;
}

Point3* Point3::negate() const
{
	return new Point3(-_x, -_y, -_z);
}

void Point3::print() const
{
	cout << "[ " << _x << ", " << _y << ", " << _z << ", " << _h << " ]" << endl;
}

float Vec3::RADTODEG = 180.0f/3.14159265f;

Vec3* Vec3::add(const Vec3* p) const{
	return new Vec3(_x + p->_x, _y + p->_y, _z + p->_z);
}

Vec3* Vec3::negate() const{
	return new Vec3(-_x, -_y, -_z);
}

void Vec3::normalize()
{
	float length = norm();
	if(length < EPS) return;

	_x /= length;
	_y /= length;
	_z /= length;
}

float Vec3::dot(const Vec3* v) const
{
	return _x*v->_x + _y*v->_y + _z*v->_z;
}


Vec3* Vec3::cross(const Vec3* v) const
{
	return new Vec3(_y*v->_z - _z*v->_y, _z*v->_x - _x*v->_z, _x*v->_y - _y*v->_x);
}

float Vec3::angle(const Vec3* v) const
{
	float magnitude = norm()*(v->norm());
	float angle = acos(dot(v)/magnitude);
	return angle*RADTODEG;
}

float Vec3::angle2(const Vec3* v) const
{
	float magnitude = norm()*(v->norm());
	float angle = atan2((cross(v)->norm()), dot(v));
	return angle*RADTODEG;
}

float Vec3::signedAngle(const Vec3* v, const Vec3* w) const
{
	 Vec3* n = cross(v);
	float angle = angle2(v);
	if(n->dot(w) < 0) angle = -angle;
	delete n;
	return angle;
}

Vec3* Vec3:: reflect(const Vec3* n) const
{
	float term = 2*dot(n);
	Vec3* r = (n->scalarMult(term))->subtract(this);
	return r;
}


const Vec3* Vec3::X_AXIS = new Vec3(1, 0, 0);
const Vec3* Vec3::Y_AXIS = new Vec3(0, 1, 0);
const Vec3* Vec3::Z_AXIS = new Vec3(0, 0, 1);
