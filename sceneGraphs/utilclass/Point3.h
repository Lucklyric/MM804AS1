//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: Point3.h
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

#if !defined(H_POINT)
#define H_POINT

class Vec3;

class Point3 
{
protected:
	static float EPS;
public:
	float _x, _y, _z, _h;
    Point3(float x, float y, float z = 0)
		: _x(x), _y(y), _z(z), _h(1.0)
	       {}
	Point3()
		: _x(0.0), _y(0.0), _z(0.0), _h(1.0)
	       {}
	virtual ~Point3() {}
	float norm() const;
	float atIndex(int i) const;
	virtual Point3* add(const Point3* p) const;
	Vec3* subtract(const Point3* p) const;
	Point3* scalarMult(float term) const;
	Point3* lerp(float t, const Point3* p) const;
	virtual Point3* negate() const;
	void print() const;
};


class Vec3 : public Point3
{
private:
	static float RADTODEG;
public:
	Vec3(float x, float y, float z = 0)
		: Point3(x, y, z)
			{ _h = 0; }
	Vec3()
			{ _h = 0; }
	~Vec3() {}
	Vec3* add(const Vec3* p) const;
	Vec3* negate() const;
	float dot(const Vec3* v) const;
	Vec3* cross(const Vec3* v) const;
	Vec3* reflect(const Vec3* n) const;
	float angle(const Vec3* v) const;
	float angle2(const Vec3* v) const;
	float signedAngle(const Vec3* v, const Vec3* w) const;
	void normalize();

	static const Vec3* X_AXIS;
	static const Vec3* Y_AXIS;
	static const Vec3* Z_AXIS;
};

#endif