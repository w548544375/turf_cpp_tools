#include "lua.hpp"
#include "lua_appdata.h"

static const luaL_Reg AppDataFunc[] = {

    {"new", NewAppData},        {"PutByte", l_putByte},
    {"PutShort", l_putShort},   {"PutInt", l_putInt},
    {"PutFloat", l_putFloat},   {"PutLong", l_putLong},
    {"PutDouble", l_putDouble}, {"PutString", l_putString},
    {"GetByte", l_getByte},     {"GetShort", l_getShort},
    {"GetInt", l_getInt},       {"GetFloat", l_getFloat},
    {"GetLong", l_getLong},     {"GetDouble", l_getDouble},
    {"GetString", l_getString}, {"ToString", l_ToString},
    {"Seek", l_seek},           {NULL, NULL}};

extern "C" int luaopen_sephiroth(lua_State *L) {
  luaL_newmetatable(L, "AppData");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, AppDataFunc, 0);
  /* luaL_newlib(L, bufferLib); */
  return 1;
}
