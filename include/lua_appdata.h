#ifndef __LUA_APPDATA_H__
#define __LUA_APPDATA_H__

class lua_State;

int NewAppData(lua_State *L);

int deleteAppData(lua_State *L);

int l_Size(lua_State * L);

int l_Buf(lua_State *L);

int l_putByte(lua_State *L);

int l_putBytes(lua_State *L);

int l_putShort(lua_State *L);

int l_putInt(lua_State *L);

int l_putFloat(lua_State *L);

int l_putLong(lua_State *L);

int l_putDouble(lua_State *L);

int l_putString(lua_State *L);

int l_ToString(lua_State *L);

int l_getByte(lua_State *L);

int l_getBytes(lua_State *L);

int l_getShort(lua_State *L);

int l_getInt(lua_State *L);

int l_getFloat(lua_State *L);

int l_getLong(lua_State *L);

int l_getDouble(lua_State *L);

int l_getString(lua_State *L);

int l_seek(lua_State *L);

#endif // !DEBUG
