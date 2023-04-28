#include "lua_common.h"
#include "lua.hpp"

AppData *GetAppData(lua_State *L, int arg) {
  luaL_checktype(L, arg, LUA_TUSERDATA);
  void *userData = luaL_checkudata(L, arg, "AppData");
  luaL_argcheck(L, userData != nullptr, 1, "user data error");
  return *(AppData **)userData;
}
