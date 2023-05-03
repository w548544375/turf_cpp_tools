#include "lua_appdata.h"
#include "app_data.h"
#include "lua.hpp"
#include "lua_common.h"

int NewAppData(lua_State *L) {
  int numberOfArgs = lua_gettop(L);

  AppData **ppBuf = (AppData **)lua_newuserdata(L, sizeof(AppData));
  if (numberOfArgs > 0) {
    int size = (int)luaL_checkinteger(L, 1);
    (*ppBuf) = new AppData(size);
  } else {
    (*ppBuf) = new AppData();
  }
  luaL_getmetatable(L, "AppData");
  lua_setmetatable(L, -2);
  return 1;
}

int deleteAppData(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  if (buf) {
    delete buf;
  }
  return 1;
}

int l_putByte(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  char b = luaL_checkinteger(L, -1);
  buf->PutByte(b);
  return 0;
}

int l_putShort(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  short d = luaL_checkinteger(L, -1);
  buf->PutShort(d);
  return 0;
}

int l_putInt(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  int d = luaL_checkinteger(L, -1);
  buf->PutInt(d);
  return 0;
}

int l_putFloat(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  float d = luaL_checknumber(L, -1);
  buf->PutFloat(d);
  return 0;
}
int l_putLong(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  long d = luaL_checkinteger(L, -1);
  buf->PutLong(d);
  return 0;
}
int l_putDouble(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  double d = luaL_checknumber(L, -1);
  buf->PutDouble(d);
  return 0;
}
int l_putString(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  luaL_checktype(L, -1, LUA_TSTRING);
  std::string d = luaL_checkstring(L, -1);
  buf->PutString(d);
  return 0;
}

int l_ToString(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  std::string str;
  buf->String(str);
  lua_pushstring(L, str.c_str());
  return 1;
}

int l_getByte(lua_State *L) {
  AppData *buf = GetAppData(L, 1);

  lua_pushinteger(L, buf->GetByte());
  return 1;
}

int l_getShort(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  lua_pushinteger(L, buf->GetShort());
  return 1;
}

int l_getInt(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  lua_pushinteger(L, buf->GetInt());
  return 1;
}

int l_getFloat(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  lua_pushnumber(L, buf->GetFloat());
  return 1;
}

int l_getLong(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  lua_pushinteger(L, buf->GetLong());
  return 1;
}

int l_getDouble(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  lua_pushnumber(L, buf->GetDouble());
  return 1;
}

int l_getString(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  std::string str;
  buf->GetString(str);
  lua_pushstring(L, str.c_str());
  return 1;
}

int l_seek(lua_State *L) {
  AppData *buf = GetAppData(L, 1);
  int numberOfArgs = lua_gettop(L);
  if (numberOfArgs > 1) {
    int n = luaL_checkinteger(L, 2);
    buf->seek(n);
  } else {
    buf->seek(0);
  }
  return 0;
}
