#ifndef __LUA_CLIENTMSG_H__
#define __LUA_CLIENTMSG_H__

class lua_State;

int NewClientMsg(lua_State *L);

int ClientMsgSerialize(lua_State *L);

int GetMsgType(lua_State * L);

#endif // !DEBUG
