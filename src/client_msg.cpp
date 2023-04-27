#include "client_msg.h"
#include "Config.h"
#include "app_data.h"

ClientMsg::ClientMsg(ClientMsgType mt) : msgType(mt) {}

ClientTold::ClientTold(AppData *data)
    : ClientMsg(ClientMsgType::ClientTold), appData(data) {}

ClientTold::~ClientTold() { delete appData; }

AppData *ClientTold::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_TOLD);
  int size = this->appData->Size();
  result->PutShort(0);
  result->PutInt(size);
  result->seek(16);
  short valid = size & CLIENT_TOLD;
  result->PutShort(valid);
  result->Put(appData);
  return result;
}

ClientBoundTheAvatar::ClientBoundTheAvatar(unsigned long id, AppData *data)
    : ClientMsg(ClientMsgType::ClientBoundTheAvatar), id(id), appData(data) {}

ClientBoundTheAvatar::~ClientBoundTheAvatar() { delete appData; }

AppData *ClientBoundTheAvatar::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_BOUND_THE_AVATAR);
  result->PutShort(4);
  int size = this->appData->Size();
  short valid = size ^ 4 ^ CLIENT_BOUND_THE_AVATAR;
  result->PutInt(size);
  result->seek(16);
  result->PutInt(id);
  result->Put(appData);
  return result;
}

ClientUnboundTheAvatar::ClientUnboundTheAvatar(unsigned long id)
    : ClientMsg(ClientMsgType::ClientUnboundTheAvatar), id(id) {}

AppData *ClientUnboundTheAvatar::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_UNBOUND_THE_AVATAR);
  result->PutShort(4);
  result->PutInt(0);
  result->seek(16);
  short valid = CLIENT_UNBOUND_THE_AVATAR ^ 4;
  result->PutShort(valid);
  result->PutInt(id);
  return result;
}

ClientNearOccupantMovedIn::ClientNearOccupantMovedIn(unsigned long id,
                                                     unsigned short mapId,
                                                     Pos const &pos,
                                                     float direction,
                                                     AppData *data)
    : ClientMsg(ClientMsgType::ClientNearOccupantMovedIn), id(id), map(mapId),
      position(pos), direction(direction), appData(data) {}

ClientNearOccupantMovedIn::~ClientNearOccupantMovedIn() { delete appData; }

AppData *ClientNearOccupantMovedIn::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_NEAR_OCCUPANT_MOVED_IN);
  result->PutShort(16);
  int size = this->appData->Size();
  result->PutInt(size);
  result->seek(16);
  short valid = size ^ 16 ^ CLIENT_NEAR_OCCUPANT_MOVED_IN;
  result->PutShort(valid);
  result->PutInt(id);
  result->PutInt(position.x);
  result->PutInt(position.y);
  result->PutFloat(direction);
  result->Put(this->appData);
  return result;
}

ClientNearOccupantMovedOut::ClientNearOccupantMovedOut(unsigned long id)
    : ClientMsg(ClientMsgType::ClientNearOccupantMovedOut), id(id) {}

AppData *ClientNearOccupantMovedOut::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_NEAR_OCCUPANT_MOVED_OUT);
  result->PutShort(4);
  result->PutInt(0);
  result->seek(16);
  int valid = CLIENT_NEAR_OCCUPANT_MOVED_OUT ^ 4;
  result->PutShort(valid);
  result->PutInt(valid);
  return result;
}

ClientDisconnected::ClientDisconnected(int state)
    : ClientMsg(ClientMsgType::ClientDisconnected), state(state){};

AppData *ClientDisconnected::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_DISCONNECTED);
  result->PutShort(4);
  result->PutInt(0);
  result->seek(16);
  int valid = CLIENT_DISCONNECTED ^ 4;
  result->PutShort(valid);
  result->PutInt(valid);
  return result;
}

TheAvatarActivated::TheAvatarActivated(unsigned long id, unsigned short mapId,
                                       Pos const &pos, float direction)
    : ClientMsg(ClientMsgType::TheAvatarActivated), id(id), map(mapId),
      position(pos), direction(direction) {}

AppData *TheAvatarActivated::Serialize() {
  AppData *result = new AppData();
  result->PutShort(THE_AVATAR_AVTIVATED);
  result->PutShort(18);
  result->PutInt(0);
  short valid = THE_AVATAR_AVTIVATED ^ 18;
  result->seek(16);
  result->PutShort(valid);
  result->PutInt(id);
  result->PutShort(map);
  result->PutShort(position.x);
  result->PutShort(position.y);
  result->PutFloat(direction);
  return result;
}

TheAvatarDeactivated::TheAvatarDeactivated(unsigned long id)
    : ClientMsg(ClientMsgType::TheAvatarDeactivated), id(id) {}

TheAvatarMoved::TheAvatarMoved(unsigned long id, bool isConfirm, Pos const &pos,
                               float direction, long serverTime, AppData *data)
    : ClientMsg(ClientMsgType::TheAvatarMoved), id(id), isConfirm(isConfirm),
      position(pos), direction(direction), serverTime(serverTime),
      appData(data) {}

TheAvatarMoved::~TheAvatarMoved() { delete appData; }

TheAvatarMovedToOtherMap::TheAvatarMovedToOtherMap(unsigned long id,
                                                   unsigned short mapId,
                                                   Pos const &pos,
                                                   float direction,
                                                   AppData *data)
    : ClientMsg(ClientMsgType::TheAvatarMovedToOtherMap), id(id), map(mapId),
      position(pos), direction(direction), appData(data) {}

TheAvatarMovedToOtherMap::~TheAvatarMovedToOtherMap() { delete appData; }

NearOccupantTold::NearOccupantTold(unsigned long id, AppData *data)
    : ClientMsg(ClientMsgType::NearOccupantTold), id(id), appData(data) {}

NearOccupantTold::~NearOccupantTold() { delete appData; }

NearOccupantMoved::NearOccupantMoved(unsigned long id, Pos pos, float direction,
                                     AppData *data)
    : ClientMsg(ClientMsgType::NearOccupantMoved), id(id), pos(pos),
      direction(direction), appData(data) {}

NearOccupantMoved::~NearOccupantMoved() { delete appData; }

ClientToldAt::ClientToldAt(Pos const &pos, AppData *data)
    : ClientMsg(ClientMsgType::ClientToldAt), position(pos), appData(data) {}

ClientToldAt::~ClientToldAt() { delete appData; }
