#ifndef __LUA_CRYPTO_H__
#define __LUA_CRYPTO_H__

#define META_CRYPTO "Crypto"
class lua_State;

int lua_NewCrypto(lua_State *L);

int lua_Feed(lua_State *L);

int lua_SetRoundBounds(lua_State *L);

int lua_SetRoundBegin(lua_State *L);

int lua_Encrypt(lua_State *L);

int lua_Decrypt(lua_State *L);

int lua_CryptToString(lua_State *L);

int lua_GC(lua_State *L);
#endif