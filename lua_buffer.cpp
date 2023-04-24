#include "buffer.h"
#include "lua.hpp"

int NewBuffer(lua_State *L) {
  int numberOfArgs = lua_gettop(L);

  Buffer **ppBuf = (Buffer **)lua_newuserdata(L, sizeof(Buffer));
  if (numberOfArgs > 0) {
    int size = (int)luaL_checkinteger(L, 1);
    (*ppBuf) = new Buffer(size);
  } else {
    (*ppBuf) = new Buffer();
  }
  luaL_getmetatable(L, "Buffer");
  lua_setmetatable(L, -2);
  return 1;
}

Buffer *GetBuffer(lua_State *L, int arg) {
  luaL_checktype(L, arg, LUA_TUSERDATA);
  void *userData = luaL_checkudata(L, arg, "Buffer");
  luaL_argcheck(L, userData != nullptr, 1, "user data error");
  return *(Buffer **)userData;
}

int deleteBuffer(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  if (buf) {
    delete buf;
  }
  return 1;
}

int l_putByte(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  char b = luaL_checkinteger(L, -1);
  buf->PutByte(b);
  return 0;
}

int l_putShort(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  short d = luaL_checkinteger(L, -1);
  buf->PutShort(d);
  return 0;
}

int l_putInt(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  int d = luaL_checkinteger(L, -1);
  buf->PutInt(d);
  return 0;
}

int l_putFloat(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  float d = luaL_checknumber(L, -1);
  buf->PutFloat(d);
  return 0;
}
int l_putLong(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  long d = luaL_checkinteger(L, -1);
  buf->PutLong(d);
  return 0;
}
int l_putDouble(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  double d = luaL_checknumber(L, -1);
  buf->PutDouble(d);
  return 0;
}
int l_putString(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  luaL_checktype(L, -1, LUA_TSTRING);
  std::string d = luaL_checkstring(L, -1);
  buf->PutString(d);
  return 0;
}

int l_ToString(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  const char *s = buf->String();
  lua_pushstring(L, s);
  delete[] s;
  return 1;
}

int l_getByte(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  lua_pushinteger(L, buf->GetByte());
  return 1;
}

int l_getShort(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  lua_pushinteger(L, buf->GetShort());
  return 1;
}

int l_getInt(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  lua_pushinteger(L, buf->GetInt());
  return 1;
}

int l_getFloat(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  lua_pushnumber(L, buf->GetFloat());
  return 1;
}

int l_getLong(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  lua_pushinteger(L, buf->GetLong());
  return 1;
}

int l_getDouble(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  lua_pushinteger(L, buf->GetDouble());
  return 1;
}

int l_getString(lua_State *L) {
  Buffer *buf = GetBuffer(L, 1);
  std::string str;
  buf->GetString(str);
  lua_pushstring(L, str.c_str());
  return 1;
}

static const luaL_Reg bufferFunc[] = {{"new", NewBuffer},
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
                                      {NULL, NULL}};

extern "C" int luaopen_buffer(lua_State *L) {
  luaL_newmetatable(L, "Buffer");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
  luaL_setfuncs(L, bufferFunc, 0);
  /* luaL_newlib(L, bufferLib); */
  return 1;
}
