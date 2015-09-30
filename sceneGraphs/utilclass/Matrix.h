//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: Matrix.h
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

#if !defined(H_MATRIX)
#define H_MATRIX

#include <string>
#include "Point3.h"
using namespace std;


class Matrix 
{
public:
	Matrix(float values[][4])
      {
          memcpy(_v, values, sizeof(_v));
      }
	Matrix()
      {
          identity();
      }
	Matrix(const Vec3* u, const Vec3* v, const Vec3* w);

	~Matrix() {}
    void identity();
	void preMultiply(const Matrix* m);
	void postMultiply(const Matrix* m);
	float valueAt(int i, int j) const;
    float determinant() const;
	void transform(Point3* p);  //changed back to void
	void transpose();  //added
	void setValue(int i, int j, float value);   //added
	float inverse();
	Matrix* copy();
    void print();
private:
	float _v[4][4];
	static float EPS;
};



#endif