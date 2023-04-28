#include "lua_clientmsg.h"
#include "app_data.h"
#include "client_msg.h"
#include "lua.hpp"
#include "lua_common.h"
/* ClientTold, */
/*   ClientBoundTheAvatar, */
/*   ClientUnboundTheAvatar, */
/*   ClientNearOccupantMovedIn, */
/*   ClientNearOccupantMovedOut, */
/*   ClientDisconnected, */
/*   TheAvatarActivated, */
/*   TheAvatarDeactivated, */
/*   TheAvatarMoved, */
/*   TheAvatarMovedToOtherMap, */
/*   NearOccupantTold = 0xA, */
/*   NearOccupantMoved = 0xB, */
/*   ClientToldAt = 0xD */
/**/
int NewClientMsg(lua_State *L) {
  int argsNum = lua_gettop(L);
  if (argsNum < 2) {
    luaL_argerror(L, 0, "numbers of arg error!");
    return 1;
  }
  ClientMsg **clientMsg;
  int type = luaL_checkinteger(L, 1);
  switch (type) {
  case ClientMsgType::ETold: {
    AppData *data = GetAppData(L, 2);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(ClientTold));
    *clientMsg = new ClientTold(data);
    luaL_getmetatable(L, "ClientTold");
    lua_setmetatable(L, -2);
  }
  case ClientMsgType::EBoundTheAvatar: {
    int id = luaL_checkinteger(L, 2);
    AppData *data = GetAppData(L, 3);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(ClientBoundTheAvatar));
    *clientMsg = new ClientBoundTheAvatar(id, data);
    luaL_getmetatable(L, "ClientBoundTheAvatar");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::EUnboundTheAvatar: {
    int id = luaL_checkinteger(L, 2);
    clientMsg =
        (ClientMsg **)lua_newuserdata(L, sizeof(ClientUnboundTheAvatar));
    *clientMsg = new ClientUnboundTheAvatar(id);
    luaL_getmetatable(L, "ClientUnboundTheAvatar");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::ENearOccupantMovedIn: {
    int id = luaL_checkinteger(L, 2);
    float x = luaL_checknumber(L, 3);
    float y = luaL_checknumber(L, 4);
    float direction = luaL_checknumber(L, 5);
    AppData *data = GetAppData(L, 6);
    clientMsg =
        (ClientMsg **)lua_newuserdata(L, sizeof(ClientNearOccupantMovedIn));
    Pos pos(x, y);
    *clientMsg = new ClientNearOccupantMovedIn(id, pos, direction, data);
    luaL_getmetatable(L, "ClientNearOccupantMovedIn");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::ENearOccupantMovedOut: {
    int id = luaL_checkinteger(L, 2);
    clientMsg =
        (ClientMsg **)lua_newuserdata(L, sizeof(ClientNearOccupantMovedOut));
    *clientMsg = new ClientNearOccupantMovedOut(id);
    luaL_getmetatable(L, "ClientNearOccupantMovedOut");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::EAvatarActivated: {
    int id = luaL_checkinteger(L, 2);
    short mapId = luaL_checknumber(L, 3);
    float x = luaL_checknumber(L, 4);
    float y = luaL_checknumber(L, 5);
    float direction = luaL_checknumber(L, 6);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(TheAvatarActivated));
    Pos pos(x, y);
    *clientMsg = new TheAvatarActivated(id, mapId, pos, direction);
    luaL_getmetatable(L, "TheAvatarActivated");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::EAvatarDeactivated: {
    int id = luaL_checkinteger(L, 2);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(TheAvatarDeactivated));
    *clientMsg = new TheAvatarDeactivated(id);
    luaL_getmetatable(L, "TheAvatarDeactivated");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::EAvatarMoved: {
    int seq = luaL_checkinteger(L, 2);
    float x = luaL_checknumber(L, 3);
    float y = luaL_checknumber(L, 4);
    float direction = luaL_checknumber(L, 5);
    long time = luaL_checknumber(L, 6);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(TheAvatarMoved));
    Pos pos(x, y);
    *clientMsg = new TheAvatarMoved(seq, pos, direction, time);
    luaL_getmetatable(L, "TheAvatarMoved");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::ENearOccupantTold: {
    int id = luaL_checkinteger(L, 2);
    AppData *data = GetAppData(L, 3);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(NearOccupantTold));
    *clientMsg = new NearOccupantTold(id, data);
    luaL_getmetatable(L, "NearOccupantTold");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::ENearOccupantMoved: {
    int id = luaL_checkinteger(L, 2);
    float x = luaL_checknumber(L, 3);
    float y = luaL_checknumber(L, 4);
    float direction = luaL_checknumber(L, 5);
    AppData *data = GetAppData(L, 6);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(NearOccupantMoved));
    Pos pos(x, y);
    *clientMsg = new NearOccupantMoved(id, pos, direction, data);
    luaL_getmetatable(L, "NearOccupantMoved");
    lua_setmetatable(L, -2);
    break;
  }
  case ClientMsgType::EToldAt: {
    float x = luaL_checknumber(L, 2);
    float y = luaL_checknumber(L, 3);
    AppData *data = GetAppData(L, 4);
    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(ClientToldAt));
    Pos pos(x, y);
    *clientMsg = new ClientToldAt(pos, data);
    luaL_getmetatable(L, "ClientToldAt");
    lua_setmetatable(L, -2);
    break;
  }
  default:

    int reason = luaL_checkinteger(L, 2);

    clientMsg = (ClientMsg **)lua_newuserdata(L, sizeof(ClientDisconnected));
    *clientMsg = new ClientDisconnected(reason);
    luaL_getmetatable(L, "ClientDisconnected");
    lua_setmetatable(L, -2);
  }
  return 1;
}

void registerClientTold(lua_State *L) {}
