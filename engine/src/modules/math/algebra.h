#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_

#define half_pi           3.14159265358979323846264338327950288419716939937510582 * 0.5
#define quarter_pi        3.14159265358979323846264338327950288419716939937510582 * 0.25
#define pi			     3.14159265358979323846264338327950288419716939937510582
#define two_pi			 3.14159265358979323846264338327950288419716939937510582 * 2.0

#define degtorad(deg) (0.017453292f*(deg))

struct vec2;
struct vec3;
struct vec4;

struct quat;

struct mat4;

struct vec2{
	
	float x, y;
	
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
	
	float x, y, z;
	
	vec3(){ }
	vec3(float x, float y, float z) : x(x), y(y), z(z) { }
	vec3(const float* xyz) : x(xyz[0]), y(xyz[1]), z(xyz[2]) { }
	vec3(const vec2 &v) : x(v.x), y(v.y), z(1.0f) { }
	vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) { }
	
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
	
};

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
	
	float x, y, z, w;
	
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
	
};

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
	
	float m[16];
		
	mat4() { };
	mat4(const float *mat);
	mat4(const mat4 &mat);
	mat4(float a11, float a12, float a13, float a14,
	     float a21, float a22, float a23, float a24,
	     float a31, float a32, float a33, float a34,
	     float a41, float a42, float a43, float a44);
	
	operator float*();
	operator const float*() const;
	
	mat4 operator*(const mat4&) const;
	
};

void identity(mat4 &mat);

#endif //_ALGEBRA_H_
