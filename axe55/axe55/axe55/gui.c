#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>


#include "view.h"
#include "button.h"
#include "input.h"
#include "label.h"
#include "switch.h"
#include "slider.h"
#include "luafunc.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

char *name = "axe55";
int width = 600;
int height = 800;
ViewStruct *view;


int
AddButton(lua_State *L){
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    int w = lua_tonumber(L, 3);
    int h = lua_tonumber(L, 4);

    ButtonStruct *b = GuaButtonNew(x, y, w, h);
    GuaButtonSetAction(b, (void *)actionClick);
    GuaViewAdd(b, view);
    return 0;
}

int
AddText(lua_State *L){
    int x = lua_tonumber(L, 1);
    int y = lua_tonumber(L, 2);
    const char *text = lua_tostring(L, 3);

    drawText(view, x, y, text);
    return 0;
}


// int
// AddLabel(lua_State *L){
//     int x = lua_tonumber(L, 1);
//     int y = lua_tonumber(L, 2);
//     int w = lua_tonumber(L, 3);
//     int h = lua_tonumber(L, 4);
//     char *text = lua_tostring(L, 5);
//
//     McLabel *l = McLabelNew(view, text, x, y, w, h);
//     GuaViewAdd(l, view);
//     return 0;
// }

int
main(int argc, char *argv[]) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    view = ViewStructCreate(name, width, height);

    char inputtext[50] = "text";

    // lua_register(L, "drawLine", LuaDrawLine);
    // lua_register(L, "drawPoint", LuaDrawPoint);
    lua_register(L, "drawButton", AddButton);
    lua_register(L, "drawText", AddText);
    lua_register(L, "fillRect", LuaFillRect);
    lua_register(L, "setColor", LuaSetColor);

    // // input
    // McInput *i = McInputNew(view, inputtext);
    // GuaViewAdd(i, view);
    // // switch
    // McSwitch *s = McSwitchNew(view);
    // SwitchSetAction(s, (void *)actionSwitch);
    // GuaViewAdd(s, view);
    //
    // McSlider *sl = McSliderNew(view);
    // SliderSetAction(sl, (void *)actionSlider);
    // GuaViewAdd(sl, view);

    initsdl(view);
    while(true) {
        updateInput(view, inputtext);
        draw(view, L);
    }
    TTF_Quit();
    return 0;
}
