#include "lua.hpp"
#include "lua_appdata.h"
#include "lua_crypto.h"
#include "lua_common.h"
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
    {"Seek", l_seek},
    {NULL, NULL}};

static const luaL_Reg cryptoFunctions[] = {
    {"Feed", lua_Feed},
    {"SetRoundBounds", lua_SetRoundBounds},
    {"SetRoundBegin", lua_SetRoundBegin},
    {"Decrypt", lua_Decrypt},
    {"Encrypt", lua_Encrypt},
    {"__tostring",lua_CryptToString},
    {"__gc",lua_GC},
    {nullptr, nullptr}};

static const luaL_Reg constructors[] = {
    {"Crypto", lua_NewCrypto},
    {"AppData", NewAppData},
    {"ToHexString",bytesToString},
    {nullptr, nullptr}};

void lua_registerUserData(lua_State *L, const char *name, const luaL_Reg *funcs)
{
  luaL_newmetatable(L, name);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, funcs, 0);
}

extern "C" int
luaopen_sephiroth(lua_State *L)
{
  lua_registerUserData(L, "AppData", AppDataFunc);
  lua_registerUserData(L, META_CRYPTO, cryptoFunctions);
  luaL_newlib(L, constructors);
  /* luaL_newlib(L, bufferLib); */
  return 1;
}
