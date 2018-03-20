#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "view.h"


#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"


int
LuaDrawRect(lua_State *L) {
    int x1 = lua_tonumber(L, 1);
    int y1 = lua_tonumber(L, 2);
    int w = lua_tonumber(L, 3);
    int h = lua_tonumber(L, 4);

    DrawRect(x1, y1, w, h);

    return 1;
}

int
LuaFillRect(lua_State *L) {
    int x1 = lua_tonumber(L, 1);
    int y1 = lua_tonumber(L, 2);
    int w = lua_tonumber(L, 3);
    int h = lua_tonumber(L, 4);

    FillRect(x1, y1, w, h);

    return 1;
}

int
LuaSetColor(lua_State *L) {
    int r = lua_tonumber(L, 1);
    int g = lua_tonumber(L, 2);
    int b = lua_tonumber(L, 3);
    int a = lua_tonumber(L, 4);

    setDrawcolor(r, g, b, a);

    return 1;
}
