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


int bytesToString(lua_State *L)
{
  size_t len;
  const char * str = luaL_checklstring(L,1,&len);
  char result[len * 8];
  memset(result,'\0',len * 8);
  char tmp[8];
  for (int i = 0; i < len; i++)
  {
     memset(tmp,'\0',8);
     sprintf(tmp,"%02X ",(unsigned char)(str[i] & 0xFF));
     strcat(result,tmp);
  }
  lua_pushstring(L,result);
  return 1;
}
