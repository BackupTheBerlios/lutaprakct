#ifndef _FILES_H_
#define _FILES_H_

#include <string>
#include <fstream>
#include "../errors/exceptions.h"

namespace files{
	
	bool MakeDir(const std::string& path);
	
	class CfgFile;
	
}


#endif //_FILES_H_
