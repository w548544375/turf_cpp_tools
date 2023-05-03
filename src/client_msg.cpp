#include "client_msg.h"
#include "Config.h"
#include "app_data.h"

ClientMsg::ClientMsg(ClientMsgType mt) : msgType(mt) {}

ClientTold::ClientTold(AppData *data)
    : ClientMsg(ClientMsgType::ETold), appData(data) {}

ClientTold::~ClientTold() { delete appData; }

AppData *ClientTold::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_TOLD);
  int size = this->appData->Size();
  result->PutShort(0);
  result->PutInt(size);
  result->seek(16);
  short valid = size ^ CLIENT_TOLD;
  result->PutShort(valid);
  result->Put(appData);
  return result;
}

ClientBoundTheAvatar::ClientBoundTheAvatar(unsigned long id, AppData *data)
    : ClientMsg(ClientMsgType::EBoundTheAvatar), id(id), appData(data) {}

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
    : ClientMsg(ClientMsgType::EUnboundTheAvatar), id(id) {}

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
                                                     Pos const &pos,
                                                     float direction,
                                                     AppData *data)
    : ClientMsg(ClientMsgType::ENearOccupantMovedIn), id(id), position(pos),
      direction(direction), appData(data) {}

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
    : ClientMsg(ClientMsgType::ENearOccupantMovedOut), id(id) {}

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
    : ClientMsg(ClientMsgType::EDisconnected), state(state){};

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
    : ClientMsg(ClientMsgType::EAvatarActivated), id(id), map(mapId),
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
    : ClientMsg(ClientMsgType::EAvatarDeactivated), id(id) {}

AppData *TheAvatarDeactivated::Serialize() {
  AppData *result = new AppData();
  result->PutShort(THE_AVATAR_DEACTIVATED);
  result->PutShort(4);
  result->PutInt(0);
  result->seek(16);
  short valid = THE_AVATAR_DEACTIVATED ^ 4;
  result->PutShort(valid);
  result->PutInt(id);
  return result;
}

TheAvatarMoved::TheAvatarMoved(short seq, Pos const &pos, float direction,
                               long serverTime)
    : ClientMsg(ClientMsgType::EAvatarMoved), sequence(seq), position(pos),
      direction(direction), serverTime(serverTime) {}

TheAvatarMoved::~TheAvatarMoved()
{
}

AppData *TheAvatarMoved::Serialize() {
  AppData *result = new AppData();
  result->PutShort(THE_AVATAR_MOVED);
  result->PutShort(18);
  result->PutInt(0);
  result->seek(16);
  short valid = THE_AVATAR_MOVED ^ 4;
  result->PutShort(valid);
  result->PutShort(sequence);
  result->PutFloat(position.x);
  result->PutFloat(position.y);
  result->PutFloat(direction);
  result->PutInt(serverTime);
  return result;
}

TheAvatarMovedToOtherMap::TheAvatarMovedToOtherMap(unsigned long id,
                                                   unsigned short mapId,
                                                   Pos const &pos,
                                                   float direction,
                                                   AppData *data)
    : ClientMsg(ClientMsgType::EAvatarMovedToOtherMap), id(id), map(mapId),
      position(pos), direction(direction), appData(data) {}

TheAvatarMovedToOtherMap::~TheAvatarMovedToOtherMap() { delete appData; }

AppData *TheAvatarMovedToOtherMap::Serialize() { return nullptr; }

NearOccupantTold::NearOccupantTold(unsigned long id, AppData *data)
    : ClientMsg(ClientMsgType::ENearOccupantTold), id(id), appData(data) {}

NearOccupantTold::~NearOccupantTold() { delete appData; }

AppData *NearOccupantTold::Serialize() {
  AppData *result = new AppData();
  result->PutShort(NEAR_OCCUPANT_TOLD);
  result->PutShort(0);
  int size = this->appData->Size();
  result->PutInt(size);
  result->seek(16);
  short valid = NEAR_OCCUPANT_TOLD ^ size;
  result->PutShort(valid);
  result->Put(this->appData);
  return result;
}

NearOccupantMoved::NearOccupantMoved(unsigned long id, Pos pos, float direction,
                                     AppData *data)
    : ClientMsg(ClientMsgType::ENearOccupantMoved), id(id), pos(pos),
      direction(direction), appData(data) {}

NearOccupantMoved::~NearOccupantMoved() { delete appData; }

AppData *NearOccupantMoved::Serialize() {
  AppData *result = new AppData();
  result->PutShort(NEAR_OCCUPANT_MOVED);
  result->PutShort(16);
  int size = appData->Size();
  result->PutInt(size);
  result->seek(16);
  short valid = size ^ 16 ^ NEAR_OCCUPANT_MOVED;
  result->PutShort(valid);
  result->PutInt(id);
  result->PutFloat(pos.x);
  result->PutFloat(pos.y);
  result->PutFloat(direction);
  result->Put(appData);
  return result;
}

ClientToldAt::ClientToldAt(Pos const &pos, AppData *data)
    : ClientMsg(ClientMsgType::EToldAt), position(pos), appData(data) {}

ClientToldAt::~ClientToldAt() { delete appData; }

AppData *ClientToldAt::Serialize() {
  AppData *result = new AppData();
  result->PutShort(CLIENT_TOLD_AT);
  result->PutShort(8);
  int size = this->appData->Size();
  result->PutInt(size);
  result->seek(16);
  short valid = size ^ 8 ^ CLIENT_TOLD_AT;
  result->PutShort(valid);
  result->PutFloat(position.x);
  result->PutFloat(position.y);
  result->Put(appData);
  return result;
}
