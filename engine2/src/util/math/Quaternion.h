#ifndef _MATH_QUATERNION_H_
#define _MATH_QUATERNION_H_

/* thaks to Marcos Slomp for the Quaternion class */

#include "Vector.h"

#define VDCTOR
#define SELF (*this)

//------------------------------------------------------------------------------
template<typename T>
class Quaternion : public Vector<T,4>
{
public:
	inline Quaternion(const T x=0, const T y=0, const T z=0, const T w=1);
	inline Quaternion(const Quaternion<T>& q);
	inline VDCTOR ~Quaternion();

	inline Quaternion<T>& operator () (const T x, const T y, const T z, const T w);

	inline Quaternion<T> operator ! ();
	inline Quaternion<T> operator ~ ();

	inline Quaternion<T> operator * (const Quaternion<T>& q) const;

	inline void fromAxisAngle(const T x, const T y, const T z, const T theta);
	inline void toAxisAngle(T& x, T& y, T& z, T& theta);

	// WARNING: Not yet implemented...
  inline void fromEulerAngles(const T Rx, const T Ry, const T Rz);
	// WARNING: Not yet implemented...
	inline void toEulerAngles(T& Rx, T& Ry, T& Rz);

  inline void fromPitchYawRoll(const T pitch, const T yaw, const T roll);
  // WARNING: Not yet implemented...
  inline void toPitchYawRoll(T& pitch, T& yaw, T& roll);

	inline void fromMatrix(const T Ux, const T Uy, const T Uz, const T Vx, const T Vy, const T Vz, const T Nx, const T Ny, const T Nz);
  inline void fromMatrix(const Vector<T,3>& U, const Vector<T,3>& V, const Vector<T,3>& N);
	inline void toMatrix(T& Ux, T& Uy, T& Uz, T& Vx, T& Vy, T& Vz, T& Nx, T& Ny, T& Nz);
  inline void toMatrix(Vector<T,3>& U, Vector<T,3>& V, Vector<T,3>& N);
	inline void toVectorU(T& Ux, T& Uy, T& Uz);
	inline void toVectorV(T& Vx, T& Vy, T& Vz);
	inline void toVectorN(T& Nx, T& Ny, T& Nz);
  inline void toVectorU(Vector<T,3>& U);
  inline void toVectorV(Vector<T,3>& V);
  inline void toVectorN(Vector<T,3>& N);

protected:
private:

};

template<typename T>
inline Quaternion<T>::Quaternion(const T x, const T y, const T z, const T w)
{
  SELF(x, y, z, w);
}

template<typename T>
inline Quaternion<T>::Quaternion(const Quaternion<T>& q)
{
  SELF = q;
}

template<typename T>
inline Quaternion<T>::~Quaternion()
{
}

template<typename T>
inline Quaternion<T>& Quaternion<T>::operator () (const T x, const T y, const T z, const T w)
{
	SELF[0] = x;
	SELF[1] = y;
	SELF[2] = z;
	SELF[3] = w;
	return(SELF);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator ! ()
{
	Quaternion<T> q;
	const float fLength = sqrt(SELF[0]*SELF[0] + SELF[1]*SELF[1] + SELF[2]*SELF[2] + SELF[3]*SELF[3]);
	q = (~SELF);
	q[0] /= fLength;
	q[1] /= fLength;
	q[2] /= fLength;
	q[3] /= fLength;
	return(q);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator ~ ()
{
	Quaternion<T> q (-SELF[0], -SELF[1], -SELF[2], SELF[3]);
	return(q);
}

template<typename T>
inline Quaternion<T> Quaternion<T>::operator * (const Quaternion<T>& q) const
{
  Quaternion<T> qN;
  qN[0] = SELF[3]*q[0] + SELF[0]*q[3] + SELF[1]*q[2] - SELF[2]*q[1];
  qN[1] = SELF[3]*q[1] + SELF[1]*q[3] + SELF[2]*q[0] - SELF[0]*q[2];
  qN[2] = SELF[3]*q[2] + SELF[2]*q[3] + SELF[0]*q[1] - SELF[1]*q[0];
  qN[3] = SELF[3]*q[3] - SELF[0]*q[0] - SELF[1]*q[1] - SELF[2]*q[2];
  return(qN);
}

template<typename T>
inline void Quaternion<T>::fromAxisAngle(const T x, const T y, const T z, const T theta)
{
	const float fCos = cos(theta / 2);
	const float fSin = sin(theta / 2);
  Vector<T,3> A (x, y, z);
  A.normalize();
	SELF(A[0]*fSin, A[1]*fSin, A[2]*fSin, fCos);
}

template<typename T>
inline void Quaternion<T>::toAxisAngle(T& x, T& y, T& z, T& theta)
{
	const float fAxisLenght = sqrt(SELF[0]*SELF[0] + SELF[1]*SELF[1] + SELF[2]*SELF[2]);
  if (fAxisLenght > 0)
  {
	  x = SELF[0] / fAxisLenght;
	  y = SELF[1] / fAxisLenght;
	  z = SELF[2] / fAxisLenght;
    theta = 2*acos(SELF[3]);
  }
  else
  {
	  x = 1;
	  y = 0;
	  z = 0;
    theta = 0;
  }
}

template<typename T>
inline void Quaternion<T>::fromEulerAngles(const T Rx, const T Ry, const T Rz)
{
}

template<typename T>
inline void Quaternion<T>::toEulerAngles(T& Rx, T& Ry, T& Rz)
{
}

template<typename T>
inline void Quaternion<T>::fromPitchYawRoll(const T pitch, const T yaw, const T roll)
{
  const T c1 = cos(yaw/2);
  const T c2 = cos(roll/2);
  const T c3 = cos(pitch/2);
  const T s1 = sin(yaw/2);
  const T s2 = sin(roll/2);
  const T s3 = sin(pitch/2);

  SELF[0] = s1*s2*c3 + c1*c2*s3;
  SELF[1] = s1*c2*c3 + c1*s2*s3;
  SELF[2] = c1*s2*c3 - s1*c2*s3;
  SELF[3] = c1*c2*c3 - s1*s2*s3;
}

template<typename T>
inline void Quaternion<T>::toPitchYawRoll(T& Rx, T& Ry, T& Rz)
{
}

template<typename T>
inline void Quaternion<T>::fromMatrix(const T Ux, const T Uy, const T Uz, const T Vx, const T Vy, const T Vz, const T Nx, const T Ny, const T Nz)
{
  // calculate the trace of the matrix
  const T trace (1 + Ux + Vy + Nz);

  // test if the trace is greater than zero. this will happens in most of cases.
  // (but use a value slightly greater than 0 to avoid large distortions...)
  if (trace > 0.0000001)
  {
	  const T S (sqrt(trace)*2);
    SELF[0] = (Vz - Ny) / S;
    SELF[1] = (Nx - Uz) / S;
    SELF[2] = (Uy - Vx) / S;
    SELF[3] = S/4;
    return;
  }

  // if the trace is zero, identify which major diagonal element has the greatest value.
  // column 0: 
    if ((Ux > Vy) && (Ux > Nz))
    {
      const T S (sqrt(1 + Ux - Vy - Nz)*2);
      SELF[0] = S/4;
      SELF[1] = (Uy + Vx) / S;
      SELF[2] = (Nx + Uz) / S;
      SELF[3] = (Vz - Ny) / S;
      return;
    }
  // column 1: 
    if (Vy > Nz)
    {
      const T S (sqrt(1 + Vy - Ux - Nz)*2);
      SELF[0] = (Uy + Vx) / S;
      SELF[1] = S/4;
      SELF[2] = (Vz + Ny) / S;
      SELF[3] = (Nx - Uz) / S;
      return;
    }
  // column 2:
    const T S (sqrt(1 + Nz - Ux - Vy)*2);
    SELF[0] = (Nx + Uz) / S;
    SELF[1] = (Vz + Ny) / S;
    SELF[2] = S/4;
    SELF[3] = (Uy - Vx) / S;
    return;
}

template<typename T>
inline void Quaternion<T>::fromMatrix(const Vector<T,3>& U, const Vector<T,3>& V, const Vector<T,3>& N)
{
  fromMatrix(U[0], U[1], U[2], V[0], V[1], V[2], N[0], N[1], N[2]);
}

template<typename T>
inline void Quaternion<T>::toMatrix(T& Ux, T& Uy, T& Uz, T& Vx, T& Vy, T& Vz, T& Nx, T& Ny, T& Nz)
{
	const float _x2 = SELF[0] * SELF[0];
	const float _y2 = SELF[1] * SELF[1];
	const float _z2 = SELF[2] * SELF[2];
	const float _w2 = SELF[3] * SELF[3];

	const float _2xy = 2 * SELF[0] * SELF[1];
	const float _2xz = 2 * SELF[0] * SELF[2];
	const float _2xw = 2 * SELF[0] * SELF[3];

	const float _2yz = 2 * SELF[1] * SELF[2];
	const float _2yw = 2 * SELF[1] * SELF[3];

	const float _2zw = 2 * SELF[2] * SELF[3];

  Ux = _w2 + _x2 - _y2 - _z2;
	Uy = _2xy + _2zw;
	Uz = _2xz - _2yw;

	Vx = _2xy - _2zw;
  Vy = _w2 - _x2 + _y2 - _z2;
	Vz = _2yz + _2xw;

	Nx = _2xz + _2yw;
	Ny = _2yz - _2xw;
	Nz = _w2 - _x2 - _y2 + _z2;
}

template<typename T>
inline void Quaternion<T>::toMatrix(Vector<T,3>& U, Vector<T,3>& V, Vector<T,3>& N)
{
  toMatrix(U[0], U[1], U[2], V[0], V[1], V[2], N[0], N[1], N[2]);
}

template<typename T>
inline void Quaternion<T>::toVectorU(T& Ux, T& Uy, T& Uz)
{
	const float _x2 = SELF[0] * SELF[0];
	const float _y2 = SELF[1] * SELF[1];
	const float _z2 = SELF[2] * SELF[2];
	const float _w2 = SELF[3] * SELF[3];
	const float _2xy = 2 * SELF[0] * SELF[1];
	const float _2xz = 2 * SELF[0] * SELF[2];
	const float _2yw = 2 * SELF[1] * SELF[3];
	const float _2zw = 2 * SELF[2] * SELF[3];
  Ux = _w2 + _x2 - _y2 - _z2;
	Uy = _2xy + _2zw;
	Uz = _2xz - _2yw;
}

template<typename T>
inline void Quaternion<T>::toVectorV(T& Vx, T& Vy, T& Vz)
{
	const float _x2 = SELF[0] * SELF[0];
	const float _y2 = SELF[1] * SELF[1];
	const float _z2 = SELF[2] * SELF[2];
	const float _w2 = SELF[3] * SELF[3];
	const float _2xy = 2 * SELF[0] * SELF[1];
	const float _2xw = 2 * SELF[0] * SELF[3];
	const float _2yz = 2 * SELF[1] * SELF[2];
	const float _2zw = 2 * SELF[2] * SELF[3];
  Vx = _2xy - _2zw;
  Vy = _w2 - _x2 + _y2 - _z2;
	Vz = _2yz + _2xw;
}

template<typename T>
inline void Quaternion<T>::toVectorN(T& Nx, T& Ny, T& Nz)
{
	const float _x2 = SELF[0] * SELF[0];
	const float _y2 = SELF[1] * SELF[1];
	const float _z2 = SELF[2] * SELF[2];
	const float _w2 = SELF[3] * SELF[3];
	const float _2xz = 2 * SELF[0] * SELF[2];
	const float _2xw = 2 * SELF[0] * SELF[3];
	const float _2yz = 2 * SELF[1] * SELF[2];
	const float _2yw = 2 * SELF[1] * SELF[3];
	Nx = _2xz + _2yw;
	Ny = _2yz - _2xw;
	Nz = _w2 - _x2 - _y2 + _z2;
}

template<typename T>
inline void Quaternion<T>::toVectorU(Vector<T,3>& U)
{
  ToVectorN(U[0], U[1], U[2]);
}
//------------------------------------------------------------------------------
template<typename T>
inline void Quaternion<T>::toVectorV(Vector<T,3>& V)
{
  ToVectorV(V[0], V[1], V[2]);
}

template<typename T>
inline void Quaternion<T>::toVectorN(Vector<T,3>& N)
{
  ToVectorN(N[0], N[1], N[2]);
}

typedef Quaternion<float>  Quaternionf;         // single precision quaternion
//------------------------------------------------------------------------------
typedef Quaternion<double> Quaterniond;         // double precision quaternion
//------------------------------------------------------------------------------

#undef VDCTOR
#undef SELF
//------------------------------------------------------------------------------

#endif //_MATH_QUATERNION_H_
