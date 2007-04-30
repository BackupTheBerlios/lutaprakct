#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#include <float.h>

#define half_pi           3.1415926535 * 0.5
#define quarter_pi        3.1415926535 * 0.25
#define pi			      3.1415926535
#define two_pi			  3.1415926535 * 2.0
#define EPSILON           10e-6
#define degtorad(deg) (0.017453292f*(deg))

struct vec2;
struct vec3;
struct vec4;

struct quat;

struct mat4;

struct vec2{
	
	//float x, y;
    union {
        struct {
            float x,y;          
        };
        struct {
            float s,t;          
        };
        float vec_array[2];     
    };
	
	vec2(){ }
	vec2(float x, float y) : x(x), y(y) { }
	vec2(const float* xy) : x(xy[0]), y(xy[1]) { }
	vec2(const vec2 &v) : x(v.x), y(v.y) { }
	
    bool operator==(const vec2 &v) const{
        return (v.x == x && v.y == y) ? true : false;
    }

    bool operator!=(const vec2 &v) const{
        return !(*this == v );
    }
    
    vec2 & operator*=(const float &a){
        x*= a;
        y*= a;
        return *this;
    }

    vec2 & operator-=(const vec2 &v){
        x-= v.x;
        y-= v.y;
        return *this;
    }

    vec2 & operator+=(const vec2 & v){
        x+= v.x;
        y+= v.y;
        return *this;
    }
	
    vec2 operator - () const{
		return vec2(-x, -y);
	}
	
    float & operator[](int i)
    {
        return vec_array[i];
    }

    const float operator[](int i) const
    {
        return vec_array[i];
    }
	
};

inline const vec2 operator+(const vec2& u, const vec2& v){
	return vec2(u.x + v.x, u.y + v.y);
}
	
inline const vec2 operator-(const vec2& u, const vec2& v){
	return vec2(u.x - v.x, u.y - v.y);
}

inline const vec2 operator*(const float k, const vec2& v){
	return vec2(k*v.x, k*v.y);
}

inline const vec2 operator/(const vec2& v, const float k){
	return vec2(v.x/k, v.y/k);
}

inline const vec2 operator*(const vec2& u, const vec2& v){
	return vec2(u.x*v.x, u.y*v.y);
}

struct vec3{
	
	//float x, y, z;
	
    union {
        struct {
            float x,y,z;        
        };
        struct {
            float s,t,r;       
        };
        float vec_array[3];   
    };
	
	vec3(){ }
	vec3(float x, float y, float z) : x(x), y(y), z(z) { }
	vec3(const float* xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) { }
	vec3(const vec2 &v) : x(v.x), y(v.y), z(1.0f) { }
	vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) { }
	vec3(const vec4&);
	
	float normalize();
	
    bool operator==(const vec3 &v) const{
        return (v.x == x && v.y == y && v.z == z ) ? true : false;
    }

    bool operator!=(const vec3 &v) const{
        return !(*this == v );
    }
    
    vec3 & operator*=(const float &a){
        x*= a;
        y*= a;
        z*= a;
        return *this;
    }

    vec3 & operator-=(const vec3 &v){
        x-= v.x;
        y-= v.y;
        z-= v.z;
        return *this;
    }

    vec3 & operator+=(const vec3 & v){
        x+= v.x;
        y+= v.y;
        z+= v.z;
        return *this;
    }
	
    vec3 operator - () const{
		return vec3(-x, -y, -z);
	}
	
    float & operator[](int i)
    {
        return vec_array[i];
    }

    const float operator[](int i) const
    {
        return vec_array[i];
    }
	
};

inline const vec3 operator^(const vec3& u, const vec3& v){
    return vec3(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}


inline const vec3 operator+(const vec3& u, const vec3& v){
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}
	
inline const vec3 operator-(const vec3& u, const vec3& v){
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline const vec3 operator*(const float k, const vec3& v){
	return vec3(k*v.x, k*v.y, k*v.z);
}

inline const vec3 operator/(const vec3& v, const float k){
	return vec3(v.x/k, v.y/k, v.z/k);
}

inline const vec3 operator*(const vec3& u, const vec3& v){
	return vec3(u.x*v.x, u.y*v.y, u.z*v.z);
}


struct vec4{
	
	//float x, y, z, w;
	
    union {
        struct {
            float x,y,z,w; 
        };
        struct {
            float s,t,r,q;  
        };
        float vec_array[4];   
    };
	
	vec4(){ }
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	vec4(const float* xyzw) : x(xyzw[0]), y(xyzw[1]), z(xyzw[2]), w(xyzw[2]) { }
	vec4(const vec3 &v) : x(v.x), y(v.y), z(v.z), w(1.0f) { }
	vec4(const vec4 &v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
	
	
    bool operator==(const vec4 &v) const{
        return (v.x == x && v.y == y && v.z == z && v.w == w ) ? true : false;
    }

    bool operator!=(const vec4 &v) const{
        return !(*this == v );
    }
    
    vec4 & operator*=(const float &a){
        x*= a;
        y*= a;
        z*= a;
        w*= a;
        return *this;
    }

    vec4 & operator-=(const vec4 &v){
        x-= v.x;
        y-= v.y;
        z-= v.z;
        w-= v.w;
        return *this;
    }

    vec4 & operator+=(const vec4 &v){
        x+= v.x;
        y+= v.y;
        z+= v.z;
        w+= v.w;
        return *this;
    }
	
    vec4 operator - () const{
		return vec4(-x, -y, -z, -w);
	}
	
    float & operator[](int i)
    {
        return vec_array[i];
    }

    const float operator[](int i) const
    {
        return vec_array[i];
    }
	
};

inline vec3::vec3(const vec4& u)
{
	x = u.x;
	y = u.y;
	z = u.z;
}

inline const vec4 operator+(const vec4& u, const vec4& v){
	return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);
}
	
inline const vec4 operator-(const vec4& u, const vec4& v){
	return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);
}

inline const vec4 operator*(const float k, const vec4& v){
	return vec4(k*v.x, k*v.y, k*v.z, k*v.w);
}

inline const vec4 operator/(const vec4& v, const float k){
	return vec4(v.x/k, v.y/k, v.z/k, v.w/k);
}

inline const vec4 operator*(const vec4& u, const vec4& v){
	return vec4(u.x*v.x, u.y*v.y, u.z*v.z, u.w*v.w);
}

struct quat{
	
	float x, y, z, w;
	
	quat() { }
	quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
	quat(const quat &quat) : x(quat.x) , y(quat.y), z(quat.z), w(quat.w) { }
	
};


const quat operator*(const quat& a, const quat& b);
quat conjugate(quat quat);
quat axisToQuaternion(float angle, vec3& axis);

struct mat4{
	
	//float m[16];
		
    union {
        struct {
            float a00, a10, a20, a30;   // standard names for components
            float a01, a11, a21, a31;   // standard names for components
            float a02, a12, a22, a32;   // standard names for components
            float a03, a13, a23, a33;   // standard names for components
        };
        struct {
            float _11, _12, _13, _14;   // standard names for components
            float _21, _22, _23, _24;   // standard names for components
            float _31, _32, _33, _34;   // standard names for components
            float _41, _42, _43, _44;   // standard names for components
        };
        union {
            struct {
                float b00, b10, b20, p; // standard names for components
                float b01, b11, b21, q; // standard names for components
                float b02, b12, b22, r; // standard names for components
                float x, y, z, w;       // standard names for components
            };
        };
        float mat_array[16];  
    };
		
	mat4() { };
	mat4(const float *mat);
	mat4(const mat4 &mat);
	mat4(float a11, float a12, float a13, float a14,
	     float a21, float a22, float a23, float a24,
	     float a31, float a32, float a33, float a34,
	     float a41, float a42, float a43, float a44);
	
	operator float*();
	operator const float*() const;
   
    const float& operator()(const int& i, const int& j) const
    {
        return mat_array[ j * 4 + i ];
    }

    float& operator()(const int& i, const int& j)
    {
        return  mat_array[ j * 4 + i ];
    }
	
	
	mat4 operator*(const mat4&) const;
	
};

mat4 inverse(mat4 &mat);
void identity(mat4 &mat);

const vec4 operator*(const mat4&, const vec4&);
const vec4 operator*(const vec4&, const mat4&);

//TODO: ajeitar ou remover essa fun?ao
void mult_matrix_vec( const vec3 &src, vec3 &dst, mat4 &mat );
void mult_matrix_vec( vec3 & src_and_dst, mat4 &mat) ;


const vec3      vec3_null(0,0,0);

float length(quat q);
quat normalize(quat &q);
quat conjugate(quat q);
quat axisToQuaternion(float angle, vec3& axis);
quat mult(quat A, quat B);

float dot(const vec3 & v, const vec3 & w);
vec3 & normalize(vec3 & u);
// Computes u = u * s
vec3 & scale(vec3 & u, const float s);

inline float min(const float & lambda, const float & n)
{
	 return (lambda < n ) ? lambda : n;
}

inline float max(const float & lambda, const float & n)
{ 
	return (lambda > n ) ? lambda : n;
}


#endif //_ALGEBRA_H_
