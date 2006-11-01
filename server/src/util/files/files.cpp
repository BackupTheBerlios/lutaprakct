
#include <iostream>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "files.h"

bool files::MakeDir(const std::string& path){
	
   if(mkdir(path.c_str(), 0700) != 0) {
      if(errno == EEXIST) {
         return true;
      } else {
         return false;
      }
   }
   return true;
   
}
