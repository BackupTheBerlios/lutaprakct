#ifndef CFGFILE_H_
#define CFGFILE_H_

#include "../errors/exceptions.h"
#include <string>
#include <fstream>

namespace files{

	class CfgFile{
		
		public:
			void open(const std::string& Path) throw(errors::FileException);
			unsigned int getConfigInt(const std::string& entry, bool hex = false);
			std::string getConfigString(const std::string& entry);
			~CfgFile();
		
		private:
			std::ifstream cfg;
			std::string path;
			const std::string seekEntry(const std::string& entry);
   };	
	
}

#endif /*CFGFILE_H_*/
