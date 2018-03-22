#ifndef __luafunc__
#define __luafunc__
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


int
LuaDrawRect(lua_State *L);

int
LuaFillRect(lua_State *L);

int
LuaSetColor(lua_State *L);

#endif
