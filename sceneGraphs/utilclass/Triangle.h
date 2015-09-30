//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: Triangle.h
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

#if !defined(H_TRIANGLE)
#define H_TRIANGLE

#include "Point3.h"
class Triangle 
{
private:
	static float EPS;	
	const Point3 *_a, *_b, *_c;
public:
    Triangle(const Point3* a, const Point3* b, const Point3* c)
		: _a(a), _b(b), _c(c)
	       {}
	~Triangle() {}
	float area() const;
	float signedArea2D() const;
	float signedArea3D(const Vec3* w) const;
    Point3* barycentricCoords(const Point3* p) const;
    Point3* barycentricMap(const Point3* p, const Triangle* t) const;
    Vec3* normal() const;
    bool isInside(const Point3* p) const;
    void draw() const;
};

#endif