#include "lua_common.h"
#include "lua.hpp"
#include <cstring>
#include <iostream>

AppData *GetAppData(lua_State *L, int arg) {
  luaL_checktype(L, arg, LUA_TUSERDATA);
  void *userData = luaL_checkudata(L, arg, "AppData");
  luaL_argcheck(L, userData != nullptr, 1, "user data error");
  return *(AppData **)userData;
}

void registerUserMetaTable(lua_State *L, const char *name,
                           const luaL_Reg *funcs) {
  luaL_newmetatable(L, name);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, funcs, 0);
}


int lua_toHexString(lua_State * L) {
  size_t len;
  const char * buf = luaL_checklstring(L,1,&len);
  std::string str;
  char temp[4];
  std::cout << "lua_toHexString 长度:" << len << std::endl;
  for(int i =0;i < len;i++) {
    memset(temp,0,4);
    sprintf(temp,"%02X ",buf[i] & 0xFF);
    str.append(temp);
  }
  lua_pushstring(L,str.c_str());
  return 1;
}