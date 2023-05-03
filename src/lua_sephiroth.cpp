#include "lua.hpp"
#include "lua_appdata.h"
#include "lua_clientmsg.h"
#include "lua_common.h"
#include "lua_rsa.h"

static const luaL_Reg constructors[] = {
    {"NewAppData", NewAppData},
    {"NewClientMsg", NewClientMsg},
    {"RSAInit",lua_init},
    {"RSADecrypt",lua_Decrypt},
    {"RSAEncrypt",lua_Encrypt},
    {"Free",lua_Free},
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

extern "C" int luaopen_sephiroth(lua_State *L)
{
  registerUserMetaTable(L, "AppData", AppDataFunc);
  registerUserMetaTable(L, "ClientMsg", clientToldFuns);
  /* luaL_newlib(L, bufferLib); */
  luaL_newlib(L, constructors);
  return 1;
}
