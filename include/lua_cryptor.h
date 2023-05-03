#ifndef __LUA_CRYPTO_H__
#define __LUA_CRYPTO_H__

#define META_CRYPTO "Crypto"
class lua_State;

int lua_NewCryptor(lua_State *L);

int lua_CryptorFeed(lua_State *L);

int lua_SetRoundBounds(lua_State *L);

int lua_SetRoundBegin(lua_State *L);

int lua_CryptorEncrypt(lua_State *L);

int lua_CryptorDecrypt(lua_State *L);

int lua_CryptToString(lua_State *L);

int lua_GC(lua_State *L);
#endif