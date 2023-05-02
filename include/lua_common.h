#ifndef __LUA_COMMON_H__
#define  __LUA_COMMON_H__
class AppData;
class lua_State;

AppData *GetAppData(lua_State *L, int arg);


int bytesToString(lua_State * L);

#endif