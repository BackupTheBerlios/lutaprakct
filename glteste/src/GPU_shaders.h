#ifndef _GPU_SHADERS_H_
#define _GPU_SHADERS_H_

static const char* brightnessFS =                      
"uniform sampler2D texture;                                            \n"
"uniform float Alpha;                                                  \n"
"void main (void)                                                      \n"
"{                                                                     \n"
"   vec3 pixelcolor = vec3(texture2D(texture, gl_TexCoord[0].st));     \n"
"	gl_FragColor = vec4(pixelcolor*Alpha, 1.0);                        \n"
"}                                                                     \n\0";

static const char* saturationFS =                      
"uniform sampler2D texture;                                            \n"
"const vec3 lumCoeff = vec3 (0.2125, 0.7154, 0.0721);                  \n"
"uniform float Alpha;                                                  \n"
"void main (void)                                                      \n"
"{                                                                     \n"
"   vec3 pixelcolor = vec3(texture2D(texture, gl_TexCoord[0].st));     \n"
"   vec3 itensity = vec3 (dot (pixelcolor.rgb, lumCoeff));             \n"
"   vec3 color = mix(itensity, pixelcolor.rgb, Alpha);                 \n"
"	gl_FragColor = vec4 (color, 1.0);                                  \n"
"}                                                                     \n\0";

static const char* edgeFS = 
"uniform sampler2D texture;                                                  \n"
"uniform float texsize;														 \n"
"void main (void)                                                            \n"
"{                                                                           \n"
"   const float offset = 1.0 / texsize;                                      \n"
"   vec2 texCoord = gl_TexCoord[0].xy;                                       \n"
"   vec4 c  = texture2D(texture, texCoord);                                  \n"
"   vec4 bl = texture2D(texture, texCoord + vec2(-offset, -offset));         \n"
"   vec4 l  = texture2D(texture, texCoord + vec2(-offset,     0.0));         \n"
"   vec4 tl = texture2D(texture, texCoord + vec2(-offset,  offset));         \n"
"   vec4 t  = texture2D(texture, texCoord + vec2(    0.0,  offset));         \n"
"   vec4 b  = texture2D(texture, texCoord + vec2(    0.0, -offset));         \n"
"   vec4 ur = texture2D(texture, texCoord + vec2( offset,  -offset));        \n"
"   vec4 r  = texture2D(texture, texCoord + vec2( offset,     0.0));         \n"
"   vec4 br = texture2D(texture, texCoord + vec2( offset,  offset));         \n"


"   gl_FragColor = 8.0 ( c + -0.125 * (bl + l + tl + t + ur + r + br + b)); \n"
"}                                                                           \n\0";

static const char* laplacianFS =
"uniform sampler2D texture;													\n"
"uniform float texsize;														\n"
"uniform float scale;														\n"
"void main (void)															\n"
"{																			\n"
"	vec2 texCoord = gl_TexCoord[0].xy;										\n"
"	int i;																	\n"
"	vec4 sum = vec4 (0.0);													\n"
"	vec2 offSet[5];															\n"
"	offSet[0] = vec2( -1.0/texsize,  0.0);									\n"
"	offSet[1] = vec2(  0.0, -1.0/texsize);									\n"
"	offSet[2] = vec2(  1.0/texsize,  0.0);									\n"
"	offSet[3] = vec2(  0.0, 1.0/texsize);									\n"
"	offSet[4] = vec2(  0.0,  0.0);											\n"
"   vec4 KernelValue[5];													\n"
"	KernelValue[0] = vec4(1.0);												\n"
"	KernelValue[1] = vec4(1.0);												\n"
"	KernelValue[2] = vec4(1.0);												\n"
"	KernelValue[3] = vec4(1.0);												\n"
"	KernelValue[4] = vec4(-4.0);											\n"
"	for (i =0; i < 5; i++)													\n"
"   {																		\n"
"		vec4 tmp = (texture2D(texture, texCoord + offSet[i]));				\n"
"		sum += tmp * KernelValue[i];										\n"
"	}																		\n"
"	gl_FragColor = scale*sum ;											    \n"
"}																			\n\0";

//Use only with grayscale images
static const char* embossingFS =
"uniform sampler2D texture;													\n"
"uniform float texsize;														\n"
"uniform float scale;														\n"
"void main (void)															\n"
"{																			\n"
"	vec2 texCoord = gl_TexCoord[0].xy;										\n"
"	int i;																	\n"
"	vec4 sum = vec4 (0.0);													\n"
"	vec2 offSet[2];															\n"
"	offSet[0] = vec2( 0.0,  0.0);											\n"
"	offSet[1] = vec2( 1.0/texsize,  1.0/texsize);							\n"

"   vec4 KernelValue[2];													\n"

"	KernelValue[0] = vec4(1.0);												\n"
"	KernelValue[1] = vec4(-1.0);											\n"

"	for (i =0; i < 2; i++)													\n"
"   {																		\n"
"		vec4 tmp = (texture2D(texture, texCoord + offSet[i]));				\n"
"		sum += tmp * KernelValue[i];										\n"
"	}																		\n"
"   vec4 basecolor = texture2D(texture, vec2(texCoord));                    \n"
"	gl_FragColor =  scale*sum ;											    \n"
"}																			\n\0";

static const char* invertFS =
"uniform sampler2D texture;													\n"
"void main (void)															\n"
"{																			\n"
"	vec4 color;                                                             \n"
"   color.xyz = texture2D(texture, gl_TexCoord[0].xy).xyz;				    \n"
"	gl_FragColor = 1.0 - color;												\n"
"}																			\n\0";

static const char* colorGradientFS =
"vec3 c_bezier(in half3 c0, in half3 c1, in half3 c2, in half3 c3, in half t) \n"
"{																				\n"
"	float t2 = t*t;																\n"
"	float t3 = t2*t;																\n"
"	float nt = 1.0 - t;															\n"
"	float nt2 = nt*nt;															\n"
"	float nt3 = nt2 * nt;														\n"
"	vec3 b = nt3*c0 + (3.0*t*nt2)*c1 + (3.0*t2*nt)*c2 + t3*c3;					\n"
"	return b;																	\n"
"}																				\n"
"// function used to fill the volume noise texture                         \n"
"vec4 color_curve(in vec2 Pos) 										   \n"
"{																		   \n"
"    vec3 color0 = vec3(-0.1, 0.0, 0.3);								   \n"
"    vec3 color1 = vec3(1.1, 0.3, -0.1);								   \n"
"    vec3 color2 = vec3(0.1, 1.4, 0.0);                                    \n"
"    vec3 color3 = vec3(0.3, 0.3, 1.1);                                    \n"
"	 vec3 sp = c_bezier(color0, color1, color2, color3, Pos.x);                \n"
"    return vec4(sp, 1.0);          										   \n"
"}             															   \n"
"uniform sampler2D texture;													\n"
"const vec3 GrayConv = { 1.0, 0.25, 0.10 };                                \n"
"void main (void)															\n"
"{																			\n"
"	vec4 srcColor = texture2D(texture, gl_TexCoord[0].st);                \n"
"   float n = dot(srcColor.xyz, GrayConv);                                  \n"
"	gl_FragColor = vec4(color_curve(vec2(n,0)).xyz, srcColor.w);												\n"
"}																			\n\0";

static const char* gammaFS =
"uniform sampler2D texture;													\n"
"uniform float gamma;														\n"
"uniform float exposure;													\n"
"void main (void)															\n"
"{																			\n"
"	vec4 color;                                                             \n"
"   color.xyz = texture2D(texture, gl_TexCoord[0].xy).xyz;				    \n"
"   color = color *exposure;												\n"
"   color.xyz = pow(color.xyz, gamma);										\n"
"	gl_FragColor = color;													\n"
"}																			\n\0";

static const char* halftoneFS =
"uniform sampler2D texture;													\n"
"const float  NOISE_PATCHES = 4.0;											\n"
"const vec2 DOTS_PER_BIT = 8.0;												\n"
"const vec2 IMG_DIVS = 8.0;													\n"
"const vec3 lumconst = { 0.2, 0.7, 0.1 };									\n"
"vec4 make_tones_n(vec3 Pos)												\n"
"{																			\n"
"	float n = 0.5*(1.0+noise(Pos*20.0));									\n"
"	float s = Pos.z;														\n"
"	float n2 = (n<s) ? 1.0 : 0.0;											\n"
"	return vec4(n2,n2,n2,1.0);												\n"
"}																			\n"
"void main (void)															\n"
"{																			\n"
"	vec4  scnC = texture2D(texture, gl_TexCoord[0].xy);						\n"
"	float  lum   = dot(lumconst, scnC.xyz);									\n"
"	vec2 lx0   = vec2(NOISE_PATCHES*IMG_DIVS*gl_TexCoord[0].xy);			\n"
"	vec3 lx    = vec3(lx0.x, lx0.y, lum);									\n"
"	vec4 dotC  = make_tones_n(lx);											\n"
"	gl_FragColor = vec4(dotC.xyz,1.0);										\n"
"}																			\n\0";

static const char* sepiaFS =
"uniform sampler2D texture;														\n"
"const half3 LightColor = { 1.0, 0.9,  0.5  };									\n"
"const half3 DarkColor  = { 0.2, 0.05, 0.0  };									\n"
"const half3 grayXfer   = { 0.3, 0.59, 0.11 };									\n"
"uniform float desaturate;														\n"
"uniform float toning;															\n"
"void main (void)																\n"
"{																				\n"
"	vec3 srcColor = LightColor * (texture2D(texture, gl_TexCoord[0].xy).xyz);   \n"	
"	float  gray    = dot(grayXfer,   srcColor);									\n"
"   vec3 muted    = lerp(srcColor,  gray.xxx,   desaturate);					\n"
"   vec3 sepia    = lerp(DarkColor, LightColor, gray);							\n"
"   vec3 result   = lerp(muted,     sepia,      toning);						\n"
"   gl_FragColor =  vec4(result.xyz, 1.0);										\n"
"}																				\n\0";

static const char* tilesFS =
"uniform sampler2D texture;													\n"
"const vec3 EdgeColor = { 0.7, 0.7, 0.7 };									\n"
"const vec3 ClearColor = { 0.0, 0.0, 0.0 };									\n"
"uniform float texsize;														\n"
"uniform float edgewidth;													\n"
"uniform float numtiles;													\n"
"void main (void)															\n"
"{																			\n"
"	float  size = 1.0 / numtiles;											\n"
"	vec2 texcoord = gl_TexCoord[0].xy / texsize;							\n"
"   vec2 Pbase = texcoord.xy - mod(texcoord.xy,size.xx);					\n"
"   vec2 PCenter = Pbase + (size/2.0).xx;									\n"
"   vec2 st = (texcoord.xy - Pbase)/size;									\n"
"   vec4 c1 = (vec4)0;														\n"
"   vec4 c2 = (vec4)0;														\n"
"   vec4 invOff = vec4((1-EdgeColor),1);									\n"
"   if (st.x > st.y) { c1 = invOff; }										\n"
"    float  thresholdB =  1.0 - edgewidth;									\n"
"   if (st.x > thresholdB) { c2 = c1; }										\n"
"   if (st.y > thresholdB) { c2 = c1; }										\n"
"   vec4 cBottom = c2;														\n"
"   c1 = (vec4)0;															\n"
"   c2 = (vec4)0;															\n"
"   if (st.x > st.y) { c1 = invOff; }										\n"
"   if (st.x < edgewidth) { c2 = c1; }										\n"
"   if (st.y < edgewidth) { c2 = c1; }										\n"
"   vec4 cTop = c2;															\n"
"   vec4 tileColor, result;													\n"
"	tileColor = texture2D( texture, PCenter*512.0 );						\n"
"   result = tileColor + cTop - cBottom;									\n"
"   gl_FragColor = result;													\n"
"}																			\n\0";



#endif //_GPU_SHADERS_H_
