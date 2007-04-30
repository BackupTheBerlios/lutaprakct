#ifndef XMLCONSTANTS_H_
#define XMLCONSTANTS_H_

#include <cstring>
#include "../glhelper/texture.h"
#include "../structures/StringTokenizer.h"

/* alguns valores nos xmls precisam ser traduzidos pra int ou flags. essa funcao
 * faz isso*/
int translateTextureFlag(const char* s);
int getXmlConstant(const char* s);
int getXmlTextureFlags(const char* strflags);


#endif /*XMLCONSTANTS_H_*/
