#ifndef MATRIX_H_
#define MATRIX_H_

class Matrix4f{
	
	public:
	
		Matrix4f(){};
		Matrix4f(float* a){
			for (int i = 0; i < 16; i++)
				m[i] = a[i];
		}
	
	float m[16];
	
	const float& operator()(const int& i, const int& j) const
    {
        return m[ j * 4 + i ];
    }

    float& operator()(const int& i, const int& j)
    {
        return  m[ j * 4 + i ];
    }
	
};

void identity(Matrix4f& m);
void multiply(Matrix4f& product, Matrix4f& a, Matrix4f& b);
void transpose(Matrix4f& final, Matrix4f& m);

void translate(Matrix4f& m, float x, float y, float z);
void scale(Matrix4f& m, float x, float y, float z);

#endif /*MATRIX_H_*/
