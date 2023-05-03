#ifndef __LUA_RSA_H__
#define __LUA_RSA_H__
class lua_State;

int lua_init(lua_State *L);
int lua_Decrypt(lua_State *L);
int lua_Encrypt(lua_State *L);
int lua_Free(lua_State * L);
#endif
