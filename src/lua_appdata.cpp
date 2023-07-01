#include "lua_appdata.h"
#include "app_data.h"
#include "lua.hpp"
#include "lua_common.h"
#include <cstring>

int NewAppData(lua_State *L)
{
  int numberOfArgs = lua_gettop(L);

  AppData **ppBuf = (AppData **)lua_newuserdata(L, sizeof(AppData));
  if (numberOfArgs > 0)
  {
    
    const char * typeName = luaL_typename(L,1);
    if (strcmp("string",typeName) == 0)
    {
      size_t len;
      const char *buf = luaL_checklstring(L, 1, &len);
      (*ppBuf) = new AppData(buf,len);
    }
    else
    {
      int size = (int)luaL_checkinteger(L, 1);
      (*ppBuf) = new AppData(size);
    }
  }
  else
  {
    (*ppBuf) = new AppData();
  }
  luaL_getmetatable(L, "AppData");
  lua_setmetatable(L, -2);
  return 1;
}

int deleteAppData(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  if (buf)
  {
    delete buf;
  }
  return 1;
}

int l_Size(lua_State * L)
{
  AppData *data = GetAppData(L, 1);
  int size = data->Size();
  lua_pushinteger(L,size);
  return 1;
}

int l_Buf(lua_State *L)
{
  AppData *data = GetAppData(L, 1);
  unsigned char * buf = data->Buf();
  lua_pushlstring(L,(const char *)buf,data->Size());
  delete [] buf;
  return 1;
}

int l_putByte(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  char b = luaL_checkinteger(L, -1);
  buf->PutByte(b);
  return 0;
}

int l_putBytes(lua_State * L)
{
  AppData *buf = GetAppData(L, 1);
  size_t len;
  const char * str = luaL_checklstring(L,-1,&len);
  buf->PutBytes(str,len);
  return 0;
}



int l_putShort(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  short d = luaL_checkinteger(L, -1);
  buf->PutShort(d);
  return 0;
}

int l_putInt(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  int d = luaL_checkinteger(L, -1);
  buf->PutInt(d);
  return 0;
}

int l_putFloat(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  float d = luaL_checknumber(L, -1);
  buf->PutFloat(d);
  return 0;
}
int l_putLong(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  long d = luaL_checkinteger(L, -1);
  buf->PutLong(d);
  return 0;
}
int l_putDouble(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  double d = luaL_checknumber(L, -1);
  buf->PutDouble(d);
  return 0;
}
int l_putString(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  luaL_checktype(L, -1, LUA_TSTRING);
  std::string d = luaL_checkstring(L, -1);
  buf->PutString(d);
  return 0;
}

int l_ToString(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  std::string str;
  buf->String(str);
  lua_pushstring(L, str.c_str());
  return 1;
}

int l_getByte(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);

  lua_pushinteger(L, buf->GetByte());
  return 1;
}

int l_getBytes(lua_State * L)
{
  AppData * appdata = GetAppData(L,1);
  int len = luaL_checkinteger(L,-1);
  char d[len];
  appdata->GetBytes(d,len);
  lua_pushlstring(L,d,len);
  return 1;
}

int l_getShort(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  lua_pushinteger(L, buf->GetShort());
  return 1;
}

int l_getInt(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  lua_pushinteger(L, buf->GetInt());
  return 1;
}

int l_getFloat(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  lua_pushnumber(L, buf->GetFloat());
  return 1;
}

int l_getLong(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  lua_pushinteger(L, buf->GetLong());
  return 1;
}

int l_getDouble(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  lua_pushnumber(L, buf->GetDouble());
  return 1;
}

int l_getString(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  int len;
  const char * str = buf->GetString(&len);
  lua_pushlstring(L, str,len);
  delete str;
  return 1;
}



int l_seek(lua_State *L)
{
  AppData *buf = GetAppData(L, 1);
  int numberOfArgs = lua_gettop(L);
  if (numberOfArgs > 1)
  {
    int n = luaL_checkinteger(L, 2);
    buf->seek(n);
  }
  else
  {
    buf->seek(0);
  }
  return 0;
}
