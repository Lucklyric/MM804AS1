//  ========================================================================
//  AUTHOR:  Ramakrishnan Mukundan
//  BOOK:    Advanced Methods in Computer Graphics 
//           - With examples in OpenGL,  Springer, 2012.
//
//  FILE NAME: Matrix.cpp
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

#include "Matrix.h"
#include <iostream>
using namespace std;

float Matrix::EPS = (float)1.E-6;

Matrix::Matrix(const Vec3* u, const Vec3* v, const Vec3* w)
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(j==0) _v[i][j] = u->atIndex(i);
			else if (j==1) _v[i][j] = v->atIndex(i);
			else if (j==2) _v[i][j] = w->atIndex(i);
			else _v[i][j] = 0;
		}
	}
	_v[3][3] = 1.0;
}

void Matrix::identity()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j< 4; j++)
            _v[i][j] = (i == j)? 1.0f : 0.0f;
}

void Matrix::preMultiply(const Matrix* m)
{
	float temp[4][4];
	float sum;

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			sum = 0.0;
			for(int k = 0; k<4; k++)
			{
				sum += (m->valueAt(i,k))*(_v[k][j]);
			}
			temp[i][j] = sum;
		}
	}
	memcpy(_v, temp, sizeof(_v));
}


void Matrix::postMultiply(const Matrix* m)
{
	float temp[4][4];
	float sum;

	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			sum = 0.0;
			for(int k = 0; k<4; k++)
			{
				sum += (_v[i][k])*(m->valueAt(k,j));
			}
			temp[i][j] = sum;
		}
	}
	memcpy(_v, temp, sizeof(_v));
}

void Matrix::transpose()
{
	float temp[4][4];
    for(int i = 0;  i < 4; i ++)
        for(int j = 0; j < 4; j++) 
            temp[i][j] = _v[j][i] ;

	memcpy(_v, temp, sizeof(_v));
}

float Matrix::valueAt(int i, int j) const
{
	return _v[i][j];
}

void Matrix::setValue(int i, int j, float value)
{
	_v[i][j] = value;
}

Matrix* Matrix::copy()
{
	return new Matrix(_v);
}

float Matrix::inverse()
{
    float det = determinant();
	if(fabs(det) < EPS) return 0;

    float temp[4][4];
    temp[0][0] =   (_v[1][2]*_v[2][3] - _v[1][3]*_v[2][2]) *_v[3][1] 
	             + (_v[1][3]*_v[2][1] - _v[1][1]*_v[2][3]) *_v[3][2]
                 + (_v[1][1]*_v[2][2] - _v[1][2]*_v[2][1]) *_v[3][3];

    temp[0][1] =   (_v[0][3]*_v[2][2] - _v[0][2]*_v[2][3]) *_v[3][1] 
	             + (_v[0][1]*_v[2][3] - _v[0][3]*_v[2][1]) *_v[3][2]
                 + (_v[0][2]*_v[2][1] - _v[0][1]*_v[2][2]) *_v[3][3];

    temp[0][2] =   (_v[0][2]*_v[1][3] - _v[0][3]*_v[1][2]) *_v[3][1] 
	             + (_v[0][3]*_v[1][1] - _v[0][1]*_v[1][3]) *_v[3][2]
                 + (_v[0][1]*_v[1][2] - _v[0][2]*_v[1][1]) *_v[3][3];

    temp[0][3] =   (_v[0][3]*_v[1][2] - _v[0][2]*_v[1][3]) *_v[2][1] 
	             + (_v[0][1]*_v[1][3] - _v[0][3]*_v[1][1]) *_v[2][2]
                 + (_v[0][2]*_v[1][1] - _v[0][1]*_v[1][2]) *_v[2][3];

    temp[1][0] =   (_v[1][3]*_v[2][2] - _v[1][2]*_v[2][3]) *_v[3][0] 
	             + (_v[1][0]*_v[2][3] - _v[1][3]*_v[2][0]) *_v[3][2]
                 + (_v[1][2]*_v[2][0] - _v[1][0]*_v[2][2]) *_v[3][3];

    temp[1][1] =   (_v[0][2]*_v[2][3] - _v[0][3]*_v[2][2]) *_v[3][0] 
	             + (_v[0][3]*_v[2][0] - _v[0][0]*_v[2][3]) *_v[3][2]
                 + (_v[0][0]*_v[2][2] - _v[0][2]*_v[2][0]) *_v[3][3];

    temp[1][2] =   (_v[0][3]*_v[1][2] - _v[0][2]*_v[1][3]) *_v[3][0] 
	             + (_v[0][0]*_v[1][3] - _v[0][3]*_v[1][0]) *_v[3][2]
                 + (_v[0][2]*_v[1][0] - _v[0][0]*_v[1][2]) *_v[3][3];

    temp[1][3] =   (_v[0][2]*_v[1][3] - _v[0][3]*_v[1][2]) *_v[2][0] 
	             + (_v[0][3]*_v[1][0] - _v[0][0]*_v[1][3]) *_v[2][2]
                 + (_v[0][0]*_v[1][2] - _v[0][2]*_v[1][0]) *_v[2][3];

    temp[2][0] =   (_v[1][1]*_v[2][3] - _v[1][3]*_v[2][1]) *_v[3][0] 
	             + (_v[1][3]*_v[2][0] - _v[1][0]*_v[2][3]) *_v[3][1]
                 + (_v[1][0]*_v[2][1] - _v[1][1]*_v[2][0]) *_v[3][3];

    temp[2][1] =   (_v[0][3]*_v[2][1] - _v[0][1]*_v[2][3]) *_v[3][0] 
	             + (_v[0][0]*_v[2][3] - _v[0][3]*_v[2][0]) *_v[3][1]
                 + (_v[0][1]*_v[2][0] - _v[0][0]*_v[2][1]) *_v[3][3];

    temp[2][2] =   (_v[0][1]*_v[1][3] - _v[0][3]*_v[1][1]) *_v[3][0] 
	             + (_v[0][3]*_v[1][0] - _v[0][0]*_v[1][3]) *_v[3][1]
                 + (_v[0][0]*_v[1][1] - _v[0][1]*_v[1][0]) *_v[3][3];

    temp[2][3] =   (_v[0][3]*_v[1][1] - _v[0][1]*_v[1][3]) *_v[2][0] 
	             + (_v[0][0]*_v[1][3] - _v[0][3]*_v[1][0]) *_v[2][1]
                 + (_v[0][1]*_v[1][0] - _v[0][0]*_v[1][1]) *_v[2][3];

    temp[3][0] =   (_v[1][2]*_v[2][1] - _v[1][1]*_v[2][2]) *_v[3][0] 
	             + (_v[1][0]*_v[2][2] - _v[1][2]*_v[2][0]) *_v[3][1]
                 + (_v[1][1]*_v[2][0] - _v[1][0]*_v[2][1]) *_v[3][2];

    temp[3][1] =   (_v[0][1]*_v[2][2] - _v[0][2]*_v[2][1]) *_v[3][0] 
	             + (_v[0][2]*_v[2][0] - _v[0][0]*_v[2][2]) *_v[3][1]
                 + (_v[0][0]*_v[2][1] - _v[0][1]*_v[2][0]) *_v[3][2];

	temp[3][2] =   (_v[0][2]*_v[1][1] - _v[0][1]*_v[1][2]) *_v[3][0] 
	             + (_v[0][0]*_v[1][2] - _v[0][2]*_v[1][0]) *_v[3][1]
                 + (_v[0][1]*_v[1][0] - _v[0][0]*_v[1][1]) *_v[3][2];

    temp[3][3] =   (_v[0][1]*_v[1][2] - _v[0][2]*_v[1][1]) *_v[2][0] 
	             + (_v[0][2]*_v[1][0] - _v[0][0]*_v[1][2]) *_v[2][1]
                 + (_v[0][0]*_v[1][1] - _v[0][1]*_v[1][0]) *_v[2][2];

    for(int i = 0;  i < 4; i ++)
        for(int j = 0; j < 4; j++) 
            temp[i][j] /= det;

	memcpy(_v, temp, sizeof(_v));
	return det;
}

float Matrix::determinant() const
{
    return
        (   (_v[0][3] *_v[1][2] - _v[0][2] *_v[1][3]) * _v[2][1]
          + (_v[0][1] *_v[1][3] - _v[0][3] *_v[1][1]) * _v[2][2]
		  + (_v[0][2] *_v[1][1] - _v[0][1] *_v[1][2]) * _v[2][3] )*_v[3][0]
      + (   (_v[0][2] *_v[1][3] - _v[0][3] *_v[1][2]) * _v[2][0]
          + (_v[0][3] *_v[1][0] - _v[0][0] *_v[1][3]) * _v[2][2]
		  + (_v[0][0] *_v[1][2] - _v[0][2] *_v[1][0]) * _v[2][3] )*_v[3][1]
      + (   (_v[0][3] *_v[1][1] - _v[0][1] *_v[1][3]) * _v[2][0]
          + (_v[0][0] *_v[1][3] - _v[0][3] *_v[1][0]) * _v[2][1]
		  + (_v[0][1] *_v[1][0] - _v[0][0] *_v[1][1]) * _v[2][3] )*_v[3][2]
      + (   (_v[0][1] *_v[1][2] - _v[0][2] *_v[1][1]) * _v[2][0]
          + (_v[0][2] *_v[1][0] - _v[0][0] *_v[1][2]) * _v[2][1]
		  + (_v[0][0] *_v[1][1] - _v[0][1] *_v[1][0]) * _v[2][2] )*_v[3][3];
}

void Matrix::print()
{
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
        {
            cout << _v[i][j] << " ";
        }
        cout << endl;
    }
	cout << endl;
}

void Matrix::transform(Point3* point)
{
	float px = point->_x;
	float py = point->_y;
	float pz = point->_z;
	point->_x = _v[0][0]*px + _v[0][1]*py + _v[0][2]*pz + _v[0][3];
	point->_y = _v[1][0]*px + _v[1][1]*py + _v[1][2]*pz + _v[1][3];
	point->_z = _v[2][0]*px + _v[2][1]*py + _v[2][2]*pz + _v[2][3];
}
