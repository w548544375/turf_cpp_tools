#ifndef __LUA_RSA_H__
#define __LUA_RSA_H__
class lua_State;

int lua_init(lua_State *L);
int lua_RSADecrypt(lua_State *L);
int lua_RSAEncrypt(lua_State *L);
int lua_RSAFree(lua_State * L);

int lua_RSA3Init(lua_State *L);
int lua_RSA3Decrypt(lua_State *L);
int lua_RSA3Encrypt(lua_State *L);
int lua_RSA3Free(lua_State * L);
#endif
