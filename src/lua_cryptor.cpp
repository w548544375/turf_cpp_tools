#include <cstring>
#include "lua_cryptor.h"
#include "lua.hpp"
#include "cryptor.h"
#include <string>
#include <iostream>

Cryptor *getCrypto(lua_State *L, int arg)
{
    luaL_checktype(L, arg, LUA_TUSERDATA);
    void *crypto = luaL_checkudata(L, arg, META_CRYPTO);
    luaL_argcheck(L, crypto != nullptr, arg, "crypto is null");
    return *(Cryptor **)crypto;
}

int lua_NewCrypto(lua_State *L)
{
    int argcNum = lua_gettop(L);
    Cryptor **crypto = (Cryptor **)lua_newuserdata(L, sizeof(Cryptor));
    if (argcNum > 0)
    {
        bool isCrypt = lua_toboolean(L, 1);
        *crypto = new Cryptor(isCrypt);
    }
    else
    {
        *crypto = new Cryptor();
    }
    luaL_setmetatable(L, META_CRYPTO);
    return 1;
}

int lua_CryptorFeed(lua_State *L)
{
    Cryptor *crypto = getCrypto(L, 1);
    size_t len;
    const char *bytes = luaL_checklstring(L, 2, &len);
    crypto->Feed((unsigned char *)bytes, len);
    return 0;
}

int lua_SetRoundBounds(lua_State *L)
{
    Cryptor *crypto = getCrypto(L, 1);
    int round = luaL_checkinteger(L, 2);
    luaL_argcheck(L, round <= 1 || round > 0, 2, "round is 0 or 1");
    int bounds = luaL_checkinteger(L, 3);
    crypto->SetRoundBound(round, bounds);
    return 0;
}

int lua_SetRoundBegin(lua_State *L)
{
    Cryptor *crypto = getCrypto(L, 1);
    int round = luaL_checkinteger(L, 2);
    luaL_argcheck(L, round <= 1 || round > 0, 2, "round is 0 or 1");
    int begin = luaL_checkinteger(L, 3);
    crypto->SetRoundBegin(round, begin);
    return 0;
}

int lua_CryptorEncrypt(lua_State *L)
{
    Cryptor *crypto = getCrypto(L, 1);
    size_t len;
    const char *plain = luaL_checklstring(L, 2,&len);
    char buf[len];
    memset(buf,0,len);
    memcpy(buf, plain, len);
    crypto->Encrypt((unsigned char *)buf, len);
    lua_pushlstring(L, buf, len);
    return 1;
}

int lua_CryptorDecrypt(lua_State *L)
{
    Cryptor *crypto = getCrypto(L, 1);
    size_t len;
    const char *cipher = luaL_checklstring(L, 2,&len);
    char plain[len];
    memcpy(plain, cipher, len);
    crypto->Decrypt((unsigned char *)plain, len);
    lua_pushlstring(L, plain, len);
    return 1;
}

int lua_CryptToString(lua_State * L)
{
    Cryptor *crypto = getCrypto(L, 1);
    std::string str = crypto->String();
    lua_pushlstring(L,str.c_str(),str.size());
    return 1;
}

int lua_GC(lua_State *L)
{
    Cryptor *crypto = getCrypto(L, 1);
    delete crypto;
    return 0;
}

