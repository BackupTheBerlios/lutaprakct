#ifndef _OBJLOAD_H_
#define _OBJLOAD_H_

/*gun?ao simples que retorna toda a informa??o sobre um .obj */

bool LoadObjModel( const char *fileName,
                   unsigned int &nverts, unsigned int &nindices, unsigned int *&indices,
                   float *&vertexdata, float *&normaldata, float *&tangendata, float *&binormdata,
				   float *&texcoords );

#endif //_OBJLOAD_H_
