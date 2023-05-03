#include "lua.hpp"
#include "lua_appdata.h"
#include "lua_clientmsg.h"
#include "lua_common.h"
#include "lua_rsa.h"
#include "lua_cryptor.h"

static const luaL_Reg constructors[] = {
    {"AppData", NewAppData},
    {"ClientMsg", NewClientMsg},
    {"RSAInit",lua_init},
    {"RSADecrypt",lua_RSADecrypt},
    {"RSAEncrypt",lua_RSAEncrypt},
    {"Free",lua_RSAFree},
    {"toHexString",lua_toHexString},
    {nullptr, nullptr}};

static const luaL_Reg AppDataFunc[] = {
    {"PutByte", l_putByte},
    {"PutShort", l_putShort},
    {"PutInt", l_putInt},
    {"PutFloat", l_putFloat},
    {"PutLong", l_putLong},
    {"PutDouble", l_putDouble},
    {"PutString", l_putString},
    {"GetByte", l_getByte},
    {"GetShort", l_getShort},
    {"GetInt", l_getInt},
    {"GetFloat", l_getFloat},
    {"GetLong", l_getLong},
    {"GetDouble", l_getDouble},
    {"GetString", l_getString},
    {"ToString", l_ToString},
    {"__tostring", l_ToString},
    {"Seek", l_seek},
    {NULL, NULL}};

static const luaL_Reg clientToldFuns[] = {{"Serialize", ClientMsgSerialize},
                                          {"GetType", GetMsgType},
                                          {NULL, NULL}};

static const luaL_Reg cryptoFunctions[] = {
    {"Feed", lua_CryptorFeed},
    {"SetRoundBounds", lua_SetRoundBounds},
    {"SetRoundBegin", lua_SetRoundBegin},
    {"Decrypt", lua_CryptorDecrypt},
    {"Encrypt", lua_CryptorEncrypt},
    {"__tostring",lua_CryptToString},
    {"__gc",lua_GC},
    {nullptr, nullptr}};

extern "C" int luaopen_sephiroth(lua_State *L)
{
  registerUserMetaTable(L, "AppData", AppDataFunc);
  registerUserMetaTable(L, "ClientMsg", clientToldFuns);
  registerUserMetaTable(L, META_CRYPTO, cryptoFunctions);
  /* luaL_newlib(L, bufferLib); */
  luaL_newlib(L, constructors);
  return 1;
}
