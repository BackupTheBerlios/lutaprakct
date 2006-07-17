

#include "algebra.h"
#include <cmath>
#include <memory.h>
#include <stdlib.h>

float vec3::normalize(){
	
	float norm = sqrt(x * x + y * y + z * z);
	if (norm > EPSILON)
		norm = 1 / norm;
	else
		norm = 0;
	x *= norm;
	y *= norm;
	z *= norm;
	return norm;
	
}

float length(quat q){
	
	return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	
}

quat normalize(quat &q){
	
  float L = length(q);
  if (L >0){
  	  float invL = 1/L;
	  q.x *= invL;
	  q.y *= invL;
	  q.z *= invL;
	  q.w *= invL;
  }
  return q;
}

quat conjugate(quat q){
  q.x = -q.x;
  q.y = -q.y;
  q.z = -q.z;
  return q;
}

const quat operator*(const quat& a, const quat& b)
{
	return quat(
		a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
		a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
		a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x,
		a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
	);
}

//usado para criar o quaternion de rotacao a redor do eixo axis e angulo angle
quat axisToQuaternion(float angle, vec3& axis){
	
	angle *= 0.5;
	
	float sinx = sin(angle);
	float cosx = cos(angle);
	
	quat q;
	q.x = axis.x * sinx;
    q.y = axis.y * sinx;
    q.z = axis.z * sinx;
    q.w = cosx;
	
	return q;
	
}

mat4::mat4(const float* mat){
    memcpy(mat_array, mat, sizeof(float) * 16);
}

mat4::mat4(const mat4& mat){
    memcpy(mat_array, mat.mat_array, sizeof(float) * 16);
}

mat4::mat4(float a11, float a12, float a13, float a14,
           float a21, float a22, float a23, float a24,
           float a31, float a32, float a33, float a34,
           float a41, float a42, float a43, float a44)
{
	mat_array[0] = a11;
	mat_array[1] = a12;
	mat_array[2] = a13;
	mat_array[3] = a14;
	mat_array[4] = a21;
	mat_array[5] = a22;
	mat_array[6] = a23;
	mat_array[7] = a24;
	mat_array[8] = a31;
	mat_array[9] = a32;
	mat_array[10] = a33;
	mat_array[11] = a34;
	mat_array[12] = a41;
	mat_array[13] = a42;
	mat_array[14] = a43;
	mat_array[15] = a44;
}

mat4::operator const float *() const{
	return &mat_array[0];
}

mat4::operator float *(){
	return &mat_array[0];
}

void identity(mat4 &mat){
	mat.mat_array[0] = 1;
	mat.mat_array[1] = 0;
	mat.mat_array[2] = 0;
	mat.mat_array[3] = 0;
	mat.mat_array[4] = 0;
	mat.mat_array[5] = 1;
	mat.mat_array[6] = 0;
	mat.mat_array[7] = 0;
	mat.mat_array[8] = 0;
	mat.mat_array[9] = 0;
	mat.mat_array[10] = 1;
	mat.mat_array[11] = 0;
	mat.mat_array[12] = 0;
	mat.mat_array[13] = 0;
	mat.mat_array[14] = 0;
	mat.mat_array[15] = 1;	
}

mat4 mat4::operator * (const mat4 &mat) const{
	return mat4(
	            mat_array[0] * mat.mat_array[0] + mat_array[1] * mat.mat_array[4] + mat_array[2] * mat.mat_array[8] + mat_array[3] * mat.mat_array[12],
	            mat_array[0] * mat.mat_array[1] + mat_array[1] * mat.mat_array[5] + mat_array[2] * mat.mat_array[9] + mat_array[3] * mat.mat_array[13],
	            mat_array[0] * mat.mat_array[2] + mat_array[1] * mat.mat_array[6] + mat_array[2] * mat.mat_array[10] + mat_array[3] * mat.mat_array[14],
	            mat_array[0] * mat.mat_array[3] + mat_array[1] * mat.mat_array[7] + mat_array[2] * mat.mat_array[11] + mat_array[3] * mat.mat_array[15],

	            mat_array[4] * mat.mat_array[0] + mat_array[5] * mat.mat_array[4] + mat_array[6] * mat.mat_array[8] + mat_array[7] * mat.mat_array[12],
	            mat_array[4] * mat.mat_array[1] + mat_array[5] * mat.mat_array[5] + mat_array[6] * mat.mat_array[9] + mat_array[7] * mat.mat_array[13],
	            mat_array[4] * mat.mat_array[2] + mat_array[5] * mat.mat_array[6] + mat_array[6] * mat.mat_array[10] + mat_array[7] * mat.mat_array[14],
	            mat_array[4] * mat.mat_array[3] + mat_array[5] * mat.mat_array[7] + mat_array[6] * mat.mat_array[11] + mat_array[7] * mat.mat_array[15],

	            mat_array[8] * mat.mat_array[0] + mat_array[9] * mat.mat_array[4] + mat_array[10] * mat.mat_array[8] + mat_array[11] * mat.mat_array[12],
	            mat_array[8] * mat.mat_array[1] + mat_array[9] * mat.mat_array[5] + mat_array[10] * mat.mat_array[9] + mat_array[11] * mat.mat_array[13],
	            mat_array[8] * mat.mat_array[2] + mat_array[9] * mat.mat_array[6] + mat_array[10] * mat.mat_array[10] + mat_array[11] * mat.mat_array[14],
	            mat_array[8] * mat.mat_array[3] + mat_array[9] * mat.mat_array[7] + mat_array[10] * mat.mat_array[11] + mat_array[11] * mat.mat_array[15],

	            mat_array[12] * mat.mat_array[0] + mat_array[13] * mat.mat_array[4] + mat_array[14] * mat.mat_array[8] + mat_array[15] * mat.mat_array[12],
	            mat_array[12] * mat.mat_array[1] + mat_array[13] * mat.mat_array[5] + mat_array[14] * mat.mat_array[9] + mat_array[15] * mat.mat_array[13],
	            mat_array[12] * mat.mat_array[2] + mat_array[13] * mat.mat_array[6] + mat_array[14] * mat.mat_array[10] + mat_array[15] * mat.mat_array[14],
	            mat_array[12] * mat.mat_array[3] + mat_array[13] * mat.mat_array[7] + mat_array[14] * mat.mat_array[11] + mat_array[15] * mat.mat_array[15]);
}

/*
    calculate the determinent of a 2x2 matrix in the from

    | a1 a2 |
    | b1 b2 |

*/
float det2x2(float a1, float a2, float b1, float b2)
{
    return a1 * b2 - b1 * a2;
}

/*
    calculate the determinent of a 3x3 matrix in the from

    | a1 a2 a3 |
    | b1 b2 b3 |
    | c1 c2 c3 |

*/
float det3x3(float a1, float a2, float a3, 
                         float b1, float b2, float b3, 
                         float c1, float c2, float c3)
{
    return a1 * det2x2(b2, b3, c2, c3) - b1 * det2x2(a2, a3, c2, c3) + c1 * det2x2(a2, a3, b2, b3);
}

mat4 inverse(mat4 &A){
	
	mat4 B;
    float det,oodet;

    B.a00 =  det3x3(A.a11, A.a21, A.a31, A.a12, A.a22, A.a32, A.a13, A.a23, A.a33);
    B.a10 = -det3x3(A.a10, A.a20, A.a30, A.a12, A.a22, A.a32, A.a13, A.a23, A.a33);
    B.a20 =  det3x3(A.a10, A.a20, A.a30, A.a11, A.a21, A.a31, A.a13, A.a23, A.a33);
    B.a30 = -det3x3(A.a10, A.a20, A.a30, A.a11, A.a21, A.a31, A.a12, A.a22, A.a32);

    B.a01 = -det3x3(A.a01, A.a21, A.a31, A.a02, A.a22, A.a32, A.a03, A.a23, A.a33);
    B.a11 =  det3x3(A.a00, A.a20, A.a30, A.a02, A.a22, A.a32, A.a03, A.a23, A.a33);
    B.a21 = -det3x3(A.a00, A.a20, A.a30, A.a01, A.a21, A.a31, A.a03, A.a23, A.a33);
    B.a31 =  det3x3(A.a00, A.a20, A.a30, A.a01, A.a21, A.a31, A.a02, A.a22, A.a32);

    B.a02 =  det3x3(A.a01, A.a11, A.a31, A.a02, A.a12, A.a32, A.a03, A.a13, A.a33);
    B.a12 = -det3x3(A.a00, A.a10, A.a30, A.a02, A.a12, A.a32, A.a03, A.a13, A.a33);
    B.a22 =  det3x3(A.a00, A.a10, A.a30, A.a01, A.a11, A.a31, A.a03, A.a13, A.a33);
    B.a32 = -det3x3(A.a00, A.a10, A.a30, A.a01, A.a11, A.a31, A.a02, A.a12, A.a32);

    B.a03 = -det3x3(A.a01, A.a11, A.a21, A.a02, A.a12, A.a22, A.a03, A.a13, A.a23);
    B.a13 =  det3x3(A.a00, A.a10, A.a20, A.a02, A.a12, A.a22, A.a03, A.a13, A.a23);
    B.a23 = -det3x3(A.a00, A.a10, A.a20, A.a01, A.a11, A.a21, A.a03, A.a13, A.a23);
    B.a33 =  det3x3(A.a00, A.a10, A.a20, A.a01, A.a11, A.a21, A.a02, A.a12, A.a22);

    det = (A.a00 * B.a00) + (A.a01 * B.a10) + (A.a02 * B.a20) + (A.a03 * B.a30);

    oodet = 1.0 / det;

    B.a00 *= oodet;
    B.a10 *= oodet;
    B.a20 *= oodet;
    B.a30 *= oodet;

    B.a01 *= oodet;
    B.a11 *= oodet;
    B.a21 *= oodet;
    B.a31 *= oodet;

    B.a02 *= oodet;
    B.a12 *= oodet;
    B.a22 *= oodet;
    B.a32 *= oodet;

    B.a03 *= oodet;
    B.a13 *= oodet;
    B.a23 *= oodet;
    B.a33 *= oodet;

    return B;
	
	
}

const vec4 operator*(const mat4& M, const vec4& v)
{
	vec4 u;
    u.x = M.mat_array[0] * v.x + M.mat_array[1] * v.y + M.mat_array[2] * v.z + M.mat_array[3] * v.w;
    u.y = M.mat_array[4] * v.x + M.mat_array[5] * v.y + M.mat_array[6] * v.z + M.mat_array[7] * v.w;
    u.z = M.mat_array[8] * v.x + M.mat_array[9] * v.y + M.mat_array[10] * v.z + M.mat_array[11] * v.w;
    u.w = M.mat_array[12] * v.x + M.mat_array[13] * v.y + M.mat_array[14] * v.z + M.mat_array[15] * v.w;
    return u;
}

const vec4 operator*(const vec4& v, const mat4& M)
{
	vec4 u;
    u.x = M.mat_array[0] * v.x + M.mat_array[1] * v.y + M.mat_array[2] * v.z + M.mat_array[3] * v.w;
    u.y = M.mat_array[4] * v.x + M.mat_array[5] * v.y + M.mat_array[6] * v.z + M.mat_array[7] * v.w;
    u.z = M.mat_array[8] * v.x + M.mat_array[9] * v.y + M.mat_array[10] * v.z + M.mat_array[11] * v.w;
    u.w = M.mat_array[12] * v.x + M.mat_array[13] * v.y + M.mat_array[14] * v.z + M.mat_array[15] * v.w;
    return u;
}


float dot(const vec3& v, const vec3& w)
{
    return v.x*w.x + v.y*w.y + v.z*w.z;
}

vec3 & normalize(vec3& u)
{
    float norm = sqrtf(u.x * u.x + u.y * u.y + u.z * u.z);
    if (norm > EPSILON)
        norm = 1 / norm;
    else
        norm = 0;
    return scale(u,norm); 
}

vec3 & scale(vec3& u, const float s)
{
    u.x *= s;
    u.y *= s;
    u.z *= s;
    return u;
}

void mult_matrix_vec( const vec3 &src, vec3 &dst, mat4 &mat )
{
		float w = (
			src.x * mat.a30 +
			src.y * mat.a31 + 
			src.z * mat.a32 +
			mat.a33          );

        dst.x  = (
			src.x * mat.a00 +
			src.y * mat.a01 +
			src.z * mat.a02 +
			mat.a03          ) / w;
		dst.y  = (
			src.x * mat.a10 +
			src.y * mat.a11 +
			src.z * mat.a12 +
			mat.a13          ) / w;
		dst.z  = (
			src.x * mat.a20 +
			src.y * mat.a21 + 
			src.z * mat.a22 +
			mat.a23          ) / w;
}
    
void mult_matrix_vec( vec3 & src_and_dst, mat4 &mat) 
{ mult_matrix_vec(vec3(src_and_dst), src_and_dst, mat); }