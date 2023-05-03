#ifndef __LUA_COMMON_H__
#define __LUA_COMMON_H__

class AppData;
class lua_State;
class luaL_Reg;

AppData *GetAppData(lua_State *L, int arg);

void registerUserMetaTable(lua_State *L, const char *name,
                           const luaL_Reg *funcs);
int lua_toHexString(lua_State * L);
#endif // !__LUA_COMMON_H__