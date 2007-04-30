#include "xmlconstants.h"

int translateTextureFlag(const char* s){

	if ( strcmp(s, "clamp") == 0)
		return Texture::CLAMP;
	else if ( strcmp(s, "clamp_to_edge") == 0)
		return Texture::CLAMP_TO_EDGE;
	else if ( strcmp(s, "nearest") == 0 )
		return Texture::NEAREST;
	else if ( strcmp(s, "nearest_mipmap_nearest") == 0)
		return Texture::NEAREST_MIPMAP_NEAREST;
	else if ( strcmp(s, "linear") == 0)
		return Texture::LINEAR;
	else if ( strcmp(s, "linear_mipmap_nearest") == 0)
		return Texture::LINEAR_MIPMAP_NEAREST;
	else if (strcmp(s, "linear_mipmap_linear") == 0)
		return Texture::LINEAR_MIPMAP_LINEAR;
		
	else if ( strcmp(s, "mipmap_sgi") == 0)
		return Texture::MIPMAP_SGI;
	
	else if ( strcmp(s, "compression_arb") == 0)
		return Texture::COMPRESSION_ARB;
	else if ( strcmp(s, "compression_dxt1") == 0)
		return Texture::COMPRESSION_DXT1;
	else if ( strcmp(s, "compression_dxt3") == 0)
		return Texture::COMPRESSION_DXT3;
	else if ( strcmp(s, "compression_dxt5") == 0)
		return Texture::COMPRESSION_DXT5;
		
	else if ( strcmp(s, "anisotropic2") == 0)
		return Texture::ANISOTROPIC_2;
	else if ( strcmp(s, "anisotropic4") == 0)
		return Texture::ANISOTROPIC_4;
	else if ( strcmp(s, "anisotropic8") == 0)
		return Texture::ANISOTROPIC_8;
	else if ( strcmp(s, "anisotropic16") == 0)
		return Texture::ANISOTROPIC_16;
	
	else
		return 0;
	
}

int getXmlConstant(const char* s){
	
	if (strcmp(s, "texture2d") == 0)
		return Texture::TEXTURE_2D;
	else if (strcmp(s, "texture1d") == 0)
		return Texture::TEXTURE_1D;
	else if (strcmp(s,"texture2d") == 0)
		return Texture::TEXTURE_3D;
	else if ( strcmp(s, "texturecubemap") == 0)
		return Texture::TEXTURE_CUBEMAP;
	else if ( strcmp(s, "texturerectangle") == 0)
		return Texture::TEXTURE_RECTANGLE;
		
	else if ( strcmp(s, "rgb8") == 0)
		return Texture::RGB8;
	else if ( strcmp( s, "rgba8") == 0)
		return Texture::RGBA8;
	else if ( strcmp(s, "rgb16") == 0)
		return Texture::RGB16;
	else if ( strcmp(s, "rgba16") == 0)
		return Texture::RGBA16;
	
	else if ( strcmp(s,"rgb") == 0)
		return Texture::RGB;
	else if ( strcmp(s,"rgba") == 0)
		return Texture::RGBA;
	else if ( strcmp(s, "bgr") == 0)
		return Texture::BGR;
	else if ( strcmp(s, "BGRA") == 0)
		return Texture::BGRA;
	else if ( strcmp(s, "luminance") == 0)
		return Texture::LUMINANCE;
	else if ( strcmp(s, "luminancealpha") == 0)
		return Texture::LUMINANCE_ALPHA;
			
	else
		return 0;
}

int getXmlTextureFlags(const char* strflags){
	
	int flags;
	std::string s(strflags);
	
	StringTokenizer tokenizer(s, " ");
	std::string token;
	
	if (tokenizer.countTokens() == 0)
		return 0;
	else{
		tokenizer.nextToken(token);
		flags = translateTextureFlag(token.c_str());
	}
	
	
	while (tokenizer.hasMoreTokens()){
		tokenizer.nextToken(token);
		flags |= translateTextureFlag(token.c_str());
	}
			
	return flags;
}
