#ifndef _PIVOT_H_
#define _PIVOT_H_

/* thaks to Marcos Slomp for the Pivot class */

#include "Quaternion.h"
#include "Vector.h"

#define VDCTOR
#define SELF (*this)

template<typename T>
class Pivot
{
protected:
  Vector<T, 3> m_vPosition;
  Quaternion<T> m_qRotation;

public:
  inline Pivot();
  inline Pivot(const Pivot<T>& pivot);
  inline VDCTOR ~Pivot();

  inline Pivot<T>& operator = (const Pivot<T>& pivot);

  inline void getPosition(Vector<T,3>& P);
  inline void getPosition(T& x, T& y, T& z);

  inline void getRotation(Quaternion<T>& Q);
  inline void getRotation(T& x, T& y, T& z, T& w);

  inline void moveAbsolute(const Vector<T,3>& P);
  inline void moveRelative(const Vector<T,3>& dP);
  inline void moveAbsolute(const T x, const T y, const T z);
  inline void moveRelative(const T x, const T y, const T z);
  inline void moveRelativeAxisX(const T dx);
  inline void moveRelativeAxisY(const T dy);
  inline void moveRelativeAxisZ(const T dz);
  inline void moveRelativeAxisU(const T du);
  inline void moveRelativeAxisV(const T dv);
  inline void moveRelativeAxisN(const T dn);

  inline void rotateAbsolute(const Quaternion<T>& Q);
  inline void rotateRelative(const Quaternion<T>& dQ);
  inline void rotateAbsolute(const T x, const T y, const T z, const T w);
  inline void rotateRelative(const T x, const T y, const T z, const T w);
	inline void rotateRelativeAxis(const Vector<T, 3>& vAxis, const T theta);
  inline void rotateRelativeAxis(const T x, const T y, const T z, const T theta);
  inline void rotateRelativeAxisX(const T theta);
  inline void rotateRelativeAxisY(const T theta);
  inline void rotateRelativeAxisZ(const T theta);
  inline void rotateRelativeAxisU(const T theta);
  inline void rotateRelativeAxisV(const T theta);
  inline void rotateRelativeAxisN(const T theta);

  inline void lookAt(const Vector<T,3>& To);
  inline void lookAt(const T tox, const T toy, const T toz);
  inline void lookAtFixUp(const Vector<T,3>& To, const Vector<T,3>& Up);
  inline void lookAtFixUp(const T tox, const T toy, const T toz, const T upx, const T upy, const T upz);

};


template<typename T>
inline Pivot<T>::Pivot()
{
}

template<typename T>
inline Pivot<T>::Pivot(const Pivot<T>& pivot)
{
  (*this) = pivot;
}

template<typename T>
inline Pivot<T>::~Pivot()
{
}

template<typename T>
inline Pivot<T>& Pivot<T>::operator = (const Pivot<T>& pivot)
{
  moveAbsolute(pivot.m_vPosition);
  rotateAbsolute(pivot.m_qRotation);
  return(*this);
}

template<typename T>
inline void Pivot<T>::getPosition(Vector<T,3>& P)
{
  getPosition(P[0], P[1], P[2]);
}

template<typename T>
inline void Pivot<T>::getPosition(T& x, T& y, T& z)
{
  x = m_vPosition[0];
  y = m_vPosition[1];
  z = m_vPosition[2];
}

template<typename T>
inline void Pivot<T>::getRotation(Quaternion<T>& Q)
{
  getRotation(Q[0], Q[1], Q[2], Q[3]);
}

template<typename T>
inline void Pivot<T>::getRotation(T& x, T& y, T& z, T& w)
{
  x = m_qRotation[0];
  y = m_qRotation[1];
  z = m_qRotation[2];
  w = m_qRotation[3];
}

template<typename T>
inline void Pivot<T>::moveAbsolute(const Vector<T,3>& P)
{
  m_vPosition = P;
}

template<typename T>
inline void Pivot<T>::moveRelative(const Vector<T,3>& dP)
{
  m_vPosition += dP;
}

template<typename T>
inline void Pivot<T>::moveAbsolute(const T x, const T y, const T z)
{
  Vector<T, 3> vPosition(x, y, z);
  moveAbsolute(vPosition);
}

template<typename T>
inline void Pivot<T>::moveRelative(const T x, const T y, const T z)
{
  Vector<T, 3> vOffset(x, y, z);
  moveRelative(vOffset);
}

template<typename T>
inline void Pivot<T>::moveRelativeAxisX(const T dx)
{
  Vector<T, 3> vOffset(dx, 0, 0);
  moveRelative(vOffset);
}

template<typename T>
inline void Pivot<T>::moveRelativeAxisY(const T dy)
{
  Vector<T, 3> vOffset(0, dy, 0);
  moveRelative(vOffset);
}

template<typename T>
inline void Pivot<T>::moveRelativeAxisZ(const T dz)
{
  Vector<T, 3> vOffset(0, 0, dz);
  moveRelative(vOffset);
}

template<typename T>
inline void Pivot<T>::moveRelativeAxisU(const T du)
{
  Vector<T, 3> U;
  m_qRotation.toVectorU(U[0], U[1], U[2]);
  moveRelative(U*du);
}

template<typename T>
inline void Pivot<T>::moveRelativeAxisV(const T dv)
{
  Vector<T, 3> V;
  m_qRotation.toVectorV(V[0], V[1], V[2]);
  moveRelative(V*dv);
}

template<typename T>
inline void Pivot<T>::moveRelativeAxisN(const T dn)
{
  Vector<T, 3> N;
  m_qRotation.toVectorN(N[0], N[1], N[2]);
  moveRelative(N*dn);
}

template<typename T>
inline void Pivot<T>::rotateAbsolute(const Quaternion<T>& Q)
{
  m_qRotation = Q;
}

template<typename T>
inline void Pivot<T>::rotateRelative(const Quaternion<T>& dQ)
{
  // qN = q2*q1 (new rotation qN is a rotation q1 followed by a rotation q2)
  m_qRotation = (dQ * m_qRotation);
}

template<typename T>
inline void Pivot<T>::rotateAbsolute(const T x, const T y, const T z, const T w)
{
  Quaternion<T> qRotation(x, y, z, w);
  rotateAbsolute(qRotation);
}

template<typename T>
inline void Pivot<T>::rotateRelative(const T x, const T y, const T z, const T w)
{
  Quaternion<T> qRotation(x, y, z, w);
  rotateRelative(qRotation);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxis(const Vector<T, 3>& vAxis, const T theta)
{
  Quaternion<T> qRotation;
  qRotation.fromAxisAngle(vAxis[0], vAxis[1], vAxis[2], theta);
  rotateRelative(qRotation);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxis(const T x, const T y, const T z, const T theta)
{
	Vector<T, 3> vAxis (x, y, z);
	rotateRelativeAxis(vAxis, theta);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxisX(const T theta)
{
  rotateRelativeAxis(1, 0, 0, theta);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxisY(const T theta)
{
  rotateRelativeAxis(0, 1, 0, theta);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxisZ(const T theta)
{
  rotateRelativeAxis(0, 0, 1, theta);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxisU(const T theta)
{
  Vector<T, 3> U;
  m_qRotation.toVectorU(U[0], U[1], U[2]);
  rotateRelativeAxis(U[0], U[1], U[2], theta);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxisV(const T theta)
{
  Vector<T, 3> V;
  m_qRotation.toVectorV(V[0], V[1], V[2]);
  rotateRelativeAxis(V[0], V[1], V[2], theta);
}

template<typename T>
inline void Pivot<T>::rotateRelativeAxisN(const T theta)
{
  Vector<T, 3> N;
  m_qRotation.toVectorN(N[0], N[1], N[2]);
  rotateRelativeAxis(N[0], N[1], N[2], theta);
}

template<typename T>
inline void Pivot<T>::lookAt(const Vector<T,3>& To)
{
  lookAt(To[0], To[1], To[2]);
}

template<typename T>
inline void Pivot<T>::lookAt(const T tox, const T toy, const T toz)
{
  Vector<T, 3> N;
  m_qRotation.toVectorN(N[0], N[1], N[2]);

  const Vector<T, 3>& A (m_vPosition);
  const Vector<T, 3>  B (tox, toy, toz);
  Vector<T, 3> D (B - A);
  D.normalize();

  const float dot (N*D);
  if (abs(dot) < 0.9999990f)
  {
    const float theta (acos(dot));
    Vector<T, 3> R (N % D);
    R.normalize();
    rotateRelativeAxis(R, theta);
  }
}

template<typename T>
inline void Pivot<T>::lookAtFixUp(const Vector<T,3>& To, const Vector<T,3>& Up)
{
  lookAt(To[0], To[1], To[2], Up[0], Up[1], Up[2]);
}

template<typename T>
inline void Pivot<T>::lookAtFixUp(const T tox, const T toy, const T toz, const T upx, const T upy, const T upz)
{
  lookAt(tox, toy, toz);

  // Note about cross products and normalization:
  // v3 = v1 X v2
  // |v3|=1 <=> |v1|=1 ^ |v2|=1 ^ v1*v2=0
  // a resulting cross vector v3 is a unit vector only if its basis vectors v1 and v2
  // are unit vectors and orthogonals.

  Vector<T,3> To;
  m_qRotation.toVectorN(To);
  const Vector<T,3> Up (upx, upy, upz);

  // there is no guarantee that the given Up vector is either a unit vector or it is
  // orthogonal to the found vector To; normalization IS required.
  Vector<T,3> NewU (Up % To);
  NewU.normalize();

  // here, both vectors To and NewU are unit vectors and they are orthogonals;
  // their cross product will be a unit vector, so normalizaton IS NOT required.
  const Vector<T,3> NewV (To % NewU);
  const Vector<T,3> NewN (To);

  m_qRotation.fromMatrix(NewU, NewV, NewN);
}

//------------------------------------------------------------------------------
typedef Pivot<float>  Pivotf;                        // single precision pivot
//------------------------------------------------------------------------------
typedef Pivot<double> Pivotd;                        // double precision pivot
//------------------------------------------------------------------------------

#endif // _PIVOT_H_
