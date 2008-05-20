#ifndef _MATH_VECTOR_H_
#define _MATH_VECTOR_H_

/* thaks to Marcos Slomp for the Vector class */

#define VDCTOR
#define SELF (*this)

#include <stdarg.h>
#include <math.h>

template<typename T, int K>
class Vector
{

public:

	T values [K];

	inline Vector();
	inline Vector(const double first, ...); // WORKS ONLY WITH T=FLOAT/DOUBLE !!!
	inline Vector(const Vector<T,K>& v);
	inline VDCTOR ~Vector();

	inline const int getDimension();
	inline const T getLength();
	inline void normalize();

	inline const bool operator == (const Vector<T,K>& v);
	inline const bool operator != (const Vector<T,K>& v);

	inline Vector<T,K>& operator = (const Vector<T,K>& v);

	inline T& operator [] (const int i);
	inline const T& operator [] (const int i) const;

	inline const T operator * (const Vector<T,K>& v2) const;
	inline const Vector<T,K> operator % (const Vector<T,K>& v2) const;

	inline const Vector<T,K> operator - () const;

	inline const Vector<T,K> operator + (const Vector<T,K>& v2) const;
	inline const Vector<T,K> operator - (const Vector<T,K>& v2) const;
	inline const Vector<T,K> operator * (const T s) const;
	inline const Vector<T,K> operator / (const T s) const;

	inline Vector<T,K>& operator += (const Vector<T,K>& v2);
	inline Vector<T,K>& operator -= (const Vector<T,K>& v2);
	inline Vector<T,K>& operator *= (const T s);
	inline Vector<T,K>& operator /= (const T s);
};

template<typename T, int K>
inline Vector<T,K>::Vector()
{
  for (int i = 0; i < K; i++)
    SELF[i] = 0;
}

template<typename T, int K>
inline Vector<T,K>::Vector(const double first, ...)
{
  va_list marker;
  va_start(marker, first);
  SELF[0] = (T) first;
  for (int i = 1; i < K; i++)
    SELF[i] = (T) va_arg(marker, double);
  va_end(marker);
}

template<typename T, int K>
inline Vector<T,K>::Vector(const Vector<T,K>& v)
{
  SELF = v;
}

template<typename T, int K>
inline Vector<T,K>::~Vector()
{
}

template<typename T, int K>
inline const int Vector<T,K>::getDimension()
{
  return(K);
}

template<typename T, int K>
inline const T Vector<T,K>::getLength()
{
  T tSquaredSum (0.0f);
  for (int i = 0; i < K; i++)
    tSquaredSum += (SELF[i]*SELF[i]);
  return(sqrt(tSquaredSum));
}

template<typename T, int K>
inline void Vector<T,K>::normalize()
{
  const T tLength = getLength();
  SELF /= tLength;
}

template<typename T, int K>
inline const bool Vector<T,K>::operator == (const Vector<T,K>& v)
{
  bool boEqual (true);
  for (int i = 0; i < K; i++)
    if (SELF[i] != v[i])
    {
      boEqual = false;
      break;
    }
  return(boEqual);
}

template<typename T, int K>
inline const bool Vector<T,K>::operator != (const Vector<T,K>& v)
{
  return(!(SELF == v));
}

template<typename T, int K>
inline Vector<T,K>& Vector<T,K>::operator = (const Vector<T,K>& v)
{
  for (int i = 0; i < K; i++)
    SELF[i] = v[i];
  return(SELF);
}

template<typename T, int K>
inline T& Vector<T,K>::operator [] (const int i)
{
  return(values[i]);
}

template<typename T, int K>
inline const T& Vector<T,K>::operator [] (const int i) const
{
  return(values[i]);
}

template<typename T, int K>
inline const T Vector<T,K>::operator * (const Vector<T,K>& v2) const
{
  float fDot (0.0f);
  for (int i = 0; i < K; i++)
    fDot += (SELF[i] * v2[i]);
  return (fDot);
};

template<typename T, int K>
inline const Vector<T,K> Vector<T,K>::operator % (const Vector<T,K>& v2) const
{
  Vector<T,K> vR;
  vR[0] = SELF[1]*v2[2] - SELF[2]*v2[1];
  vR[1] = SELF[2]*v2[0] - SELF[0]*v2[2];
  vR[2] = SELF[0]*v2[1] - SELF[1]*v2[0];
  return(vR);
}

template<typename T, int K>
inline const Vector<T,K> Vector<T,K>::operator - () const
{
  Vector<T,K> vR (SELF);
  vR *= -1;
  return(vR);
}

template<typename T, int K>
inline const Vector<T,K> Vector<T,K>::operator + (const Vector<T,K>& v2) const
{
  Vector<T,K> vR (SELF);
  vR += v2;
  return(vR);
};

template<typename T, int K>
inline const Vector<T,K> Vector<T,K>::operator - (const Vector<T,K>& v2) const
{
  Vector<T,K> vR (SELF);
  vR -= v2;
  return(vR);
};

template<typename T, int K>
inline const Vector<T,K> Vector<T,K>::operator * (const T s) const
{
  Vector<T,K> vR (SELF);
  vR *= s;
  return(vR);
};

template<typename T, int K>
inline const Vector<T,K> Vector<T,K>::operator / (const T s) const
{
  Vector<T,K> vR (SELF);
  vR /= s;
  return(vR);
};

template<typename T, int K>
inline Vector<T,K>& Vector<T,K>::operator += (const Vector<T,K>& v2)
{
  for (int i = 0; i < K; i++)
    SELF[i] += v2[i];
  return(SELF);
}

template<typename T, int K>
inline Vector<T,K>& Vector<T,K>::operator -= (const Vector<T,K>& v2)
{
  for (int i = 0; i < K; i++)
    SELF[i] -= v2[i];
  return(SELF);
}

template<typename T, int K>
inline Vector<T,K>& Vector<T,K>::operator *= (const T s)
{
  for (int i = 0; i < K; i++)
    SELF[i] *= s;
  return(SELF);
}

template<typename T, int K>
inline Vector<T,K>& Vector<T,K>::operator /= (const T s)
{
  for (int i = 0; i < K; i++)
    SELF[i] /= s;
  return(SELF);
}

//------------------------------------------------------------------------------
//-- shortcuts -----------------------------------------------------------------
//------------------------------------------------------------------------------
#define VectorNf(N) Vector<float,N>              // single precision ND vector
//------------------------------------------------------------------------------
typedef VectorNf(2) Vector2f;                    // single precision 2D vector
typedef VectorNf(3) Vector3f;                    // single precision 3D vector
typedef VectorNf(4) Vector4f;                    // single precision 4D vector
//------------------------------------------------------------------------------
#define VectorNd(N) Vector<double,N>             // double precision ND vector
//------------------------------------------------------------------------------
typedef VectorNd(2) Vector2d;                    // double precision 2D vector
typedef VectorNd(3) Vector3d;                    // double precision 3D vector
typedef VectorNd(4) Vector4d;                    // double precision 4D vector


#undef inline
#undef VDCTOR
#undef SELF

#endif // _MATH_VECTOR_H_
