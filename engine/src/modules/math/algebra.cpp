

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

float length(quat quat){
	
	return sqrt(quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);
	
}

quat normalize(quat &quat){
	
  float L = length(quat);
  if (L >0){
  	  float invL = 1/L;
	  quat.x *= invL;
	  quat.y *= invL;
	  quat.z *= invL;
	  quat.w *= invL;
  }
  return quat;
}

quat conjugate(quat quat){
  quat.x = -quat.x;
  quat.y = -quat.y;
  quat.z = -quat.z;
  return quat;
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
    memcpy(m, mat, sizeof(float) * 16);
}

mat4::mat4(const mat4& mat){
    memcpy(m, mat.m, sizeof(float) * 16);
}

mat4::mat4(float a11, float a12, float a13, float a14,
           float a21, float a22, float a23, float a24,
           float a31, float a32, float a33, float a34,
           float a41, float a42, float a43, float a44)
{
	m[0] = a11;
	m[1] = a12;
	m[2] = a13;
	m[3] = a14;
	m[4] = a21;
	m[5] = a22;
	m[6] = a23;
	m[7] = a24;
	m[8] = a31;
	m[9] = a32;
	m[10] = a33;
	m[11] = a34;
	m[12] = a41;
	m[13] = a42;
	m[14] = a43;
	m[15] = a44;
}

mat4::operator const float *() const{
	return &m[0];
}

mat4::operator float *(){
	return &m[0];
}

void identity(mat4 &mat){
	mat[0] = 1;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 0;
	mat[4] = 0;
	mat[5] = 1;
	mat[6] = 0;
	mat[7] = 0;
	mat[8] = 0;
	mat[9] = 0;
	mat[10] = 1;
	mat[11] = 0;
	mat[12] = 0;
	mat[13] = 0;
	mat[14] = 0;
	mat[15] = 1;	
}

mat4 mat4::operator * (const mat4 &mat) const{
	return mat4(
	            m[0] * mat.m[0] + m[1] * mat.m[4] + m[2] * mat.m[8] + m[3] * mat.m[12],
	            m[0] * mat.m[1] + m[1] * mat.m[5] + m[2] * mat.m[9] + m[3] * mat.m[13],
	            m[0] * mat.m[2] + m[1] * mat.m[6] + m[2] * mat.m[10] + m[3] * mat.m[14],
	            m[0] * mat.m[3] + m[1] * mat.m[7] + m[2] * mat.m[11] + m[3] * mat.m[15],

	            m[4] * mat.m[0] + m[5] * mat.m[4] + m[6] * mat.m[8] + m[7] * mat.m[12],
	            m[4] * mat.m[1] + m[5] * mat.m[5] + m[6] * mat.m[9] + m[7] * mat.m[13],
	            m[4] * mat.m[2] + m[5] * mat.m[6] + m[6] * mat.m[10] + m[7] * mat.m[14],
	            m[4] * mat.m[3] + m[5] * mat.m[7] + m[6] * mat.m[11] + m[7] * mat.m[15],

	            m[8] * mat.m[0] + m[9] * mat.m[4] + m[10] * mat.m[8] + m[11] * mat.m[12],
	            m[8] * mat.m[1] + m[9] * mat.m[5] + m[10] * mat.m[9] + m[11] * mat.m[13],
	            m[8] * mat.m[2] + m[9] * mat.m[6] + m[10] * mat.m[10] + m[11] * mat.m[14],
	            m[8] * mat.m[3] + m[9] * mat.m[7] + m[10] * mat.m[11] + m[11] * mat.m[15],

	            m[12] * mat.m[0] + m[13] * mat.m[4] + m[14] * mat.m[8] + m[15] * mat.m[12],
	            m[12] * mat.m[1] + m[13] * mat.m[5] + m[14] * mat.m[9] + m[15] * mat.m[13],
	            m[12] * mat.m[2] + m[13] * mat.m[6] + m[14] * mat.m[10] + m[15] * mat.m[14],
	            m[12] * mat.m[3] + m[13] * mat.m[7] + m[14] * mat.m[11] + m[15] * mat.m[15]);
}

const vec4 operator*(const mat4& M, const vec4& v)
{
	vec4 u;
    u.x = M.m[0] * v.x + M.m[1] * v.y + M.m[2] * v.z + M.m[3] * v.w;
    u.y = M.m[4] * v.x + M.m[5] * v.y + M.m[6] * v.z + M.m[7] * v.w;
    u.z = M.m[8] * v.x + M.m[9] * v.y + M.m[10] * v.z + M.m[11] * v.w;
    u.w = M.m[12] * v.x + M.m[13] * v.y + M.m[14] * v.z + M.m[15] * v.w;
    return u;
}

const vec4 operator*(const vec4& v, const mat4& M)
{
	vec4 u;
    u.x = M.m[0] * v.x + M.m[1] * v.y + M.m[2] * v.z + M.m[3] * v.w;
    u.y = M.m[4] * v.x + M.m[5] * v.y + M.m[6] * v.z + M.m[7] * v.w;
    u.z = M.m[8] * v.x + M.m[9] * v.y + M.m[10] * v.z + M.m[11] * v.w;
    u.w = M.m[12] * v.x + M.m[13] * v.y + M.m[14] * v.z + M.m[15] * v.w;
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