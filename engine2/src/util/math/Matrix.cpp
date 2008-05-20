
#include "Matrix.h"

void identity(Matrix4f& mat){

	mat.m[0] = 1.0;
	mat.m[1] = 0;
	mat.m[2] = 0;
	mat.m[3] = 0;
	mat.m[4] = 0;
	mat.m[5] = 1.0;
	mat.m[6] = 0;
	mat.m[7] = 0;
	mat.m[8] = 0;
	mat.m[9] = 0;
	mat.m[10] = 1.0;
	mat.m[11] = 0;
	mat.m[12] = 0;
	mat.m[13] = 0;
	mat.m[14] = 0;
	mat.m[15] = 1.0;
	
}

void translate(Matrix4f& m, float x, float y, float z){

	m.m[12] += x; 
	m.m[13] += y; 
	m.m[14] += z;
	
}

void scale(Matrix4f& m, float x, float y, float z){

	m.m[0] *= x; m.m[5] *= y; m.m[10] *= z;
	
}

#define A(row,col)  a.m[(col<<2)+row]
#define B(row,col)  b.m[(col<<2)+row]
#define P(row,col)  product.m[(col<<2)+row]

void multiply(Matrix4f& product, Matrix4f& a, Matrix4f& b){

	for (int i = 0; i < 4; i++) {
		float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
		P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
		P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
		P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
		P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
	}	
	
}
#undef A
#undef B
#undef P

#define TRANSPOSE4(dst, src)            \
{                                        \
    for (int j = 0; j < 4; j++)          \
    {                                    \
        for (int i = 0; i < 4; i++)      \
        {                                \
            dst.m[(j*4)+i] = src.m[(i*4)+j]; \
        }                                \
    }                                    \
}

void transpose(Matrix4f& final, Matrix4f& m){

		TRANSPOSE4(final, m)
	
}

