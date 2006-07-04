#ifndef NOISE_H_
#define NOISE_H_

void SetNoiseFrequency(int frequency);
double noise1(double arg);
double noise2(double vec[2]);
double noise3(double vec[3]);
void normalize2(double v[2]);
void normalize3(double v[3]);
double PerlinNoise1D(double x,double alpha,double beta,int n);
double PerlinNoise2D(double x,double y,double alpha,double beta,int n);
double PerlinNoise3D(double x,double y,double z,double alpha,double beta,int n);


#endif /*NOISE_H_*/
