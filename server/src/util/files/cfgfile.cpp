
#include "cfgfile.h"

files::CfgFile::~CfgFile(){
	
	if(cfg.is_open())
		cfg.close();

	return;
}

void files::CfgFile::open(const std::string& Path) throw(errors::FileException){
	cfg.open(path.c_str());
	if(!cfg)
		throw errors::FileException("Couldn't open CFG file", Path);
}

const std::string files::CfgFile::seekEntry(const std::string& entry){
	
	std::string line;

	while(getline(cfg, line)) {
		if(line.find(entry) != line.npos) {
			return line.substr(line.find_first_of('=') + 1);
		}
	}
	throw errors::FileException("Elem not found", entry);
	return "NULL";
}

std::string files::CfgFile::getConfigString(const std::string& entry){
	
	std::string res = seekEntry(entry);
	size_t start = res.find_first_of('"') + 1;

	return res.substr(start, res.find_last_of('"') - start);
}

unsigned int files::CfgFile::getConfigInt(const std::string& entry, bool hex){
	
	std::string res = seekEntry(entry);

	return strtoul(res.c_str(), 0, hex ? 16 : 10);
}
