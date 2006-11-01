
#include "luaVM.h"
#include <stdarg.h>
#include <cstring>
#include <iostream>

using namespace lua;

LuaVM::LuaVM(){
	//initialize();
}

LuaVM::~LuaVM(){
	shutdown();
}

bool LuaVM::initialize(){


	L = lua_open();

	luaopen_table(L);
//	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);

	return true;

}

void LuaVM::shutdown(){

	lua_close(L);
	
}

bool LuaVM::loadScripts(char* path){
	luaL_dofile(L, "add.lua");
	return true;
}

//funcao do livro: programming in lua -> http://www.lua.org/pil/25.3.htmlS
void LuaVM::callFunction(const char* functionname, const char* signature, ...){

	va_list vl;
	int narg, nres;
    
	va_start(vl, signature);
	lua_getglobal(L, functionname); 
    
      /* push arguments */
	narg = 0;
	while (*signature) {  /* push arguments */
		switch (*signature++) {
    
		case 'd':  /* double argument */
			lua_pushnumber(L, va_arg(vl, double));
			break;
    
		case 'i':  /* int argument */
			lua_pushnumber(L, va_arg(vl, int));
			break;
    
		case 's':  /* string argument */
			lua_pushstring(L, va_arg(vl, char *));
			break;
    
		case '>':
			goto endwhile;
    
		default:
			return;
		}
		narg++;
		luaL_checkstack(L, 1, "too many arguments");
	} endwhile:
    
      /* do the call */
	nres = strlen(signature);  /* number of expected results */
	if (lua_pcall(L, narg, nres, 0) != 0)  /* do the call */
		return;
    
      /* retrieve results */
	nres = -nres;  /* stack index of first result */
	while (*signature) {  /* get results */
		switch (*signature++) {
    
			case 'd':  /* double result */
				if (!lua_isnumber(L, nres))
					return;
				*va_arg(vl, double *) = lua_tonumber(L, nres);
				break;
    
			case 'i':  /* int result */
				if (!lua_isnumber(L, nres))
					return;
				*va_arg(vl, int *) = (int)lua_tonumber(L, nres);
				break;
    
			case 's':  /* string result */
				if (!lua_isstring(L, nres))
					return;
				*va_arg(vl, const char **) = lua_tostring(L, nres);
				break;
    
			default:
				return;
			}
		nres++;
	}
	va_end(vl);
	
}
