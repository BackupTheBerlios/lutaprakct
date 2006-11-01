#ifndef LUAVM_H_
#define LUAVM_H_

extern "C" {
    #include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace lua{

class LuaVM{
	
	public:
		LuaVM();
		~LuaVM();
		
		bool initialize();
		void shutdown();
		
		bool loadScripts(char* path);
		
		void callFunction(const char *functioname, const char *signature, ...);
	
	private:
	
		lua_State* L;
	
};

}
#endif /*LUAVM_H_*/
