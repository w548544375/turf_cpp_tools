#include "client_msg.h"
#include "app_data.h"

ClientMsg::ClientMsg(ClientMsgType mt) : msgType(mt) {}

ClientTold::ClientTold(AppData *data)
    : ClientMsg(ClientMsgType::ClientTold), appData(data) {}

ClientTold::~ClientTold() { delete appData; }

ClientBoundTheAvatar::ClientBoundTheAvatar(unsigned long id, AppData *data)
    : ClientMsg(ClientMsgType::ClientBoundTheAvatar), id(id), appData(data) {}

ClientBoundTheAvatar::~ClientBoundTheAvatar() { delete appData; }

ClientUnboundTheAvatar::ClientUnboundTheAvatar(unsigned long id)
    : ClientMsg(ClientMsgType::ClientUnboundTheAvatar), id(id) {}

ClientNearOccupantMovedIn::ClientNearOccupantMovedIn(unsigned long id,
                                                     unsigned short mapId,
                                                     Pos const &pos,
                                                     float direction,
                                                     AppData *data)
    : ClientMsg(ClientMsgType::ClientNearOccupantMovedIn), id(id), map(mapId),
      position(pos), direction(direction), appData(data) {}

ClientNearOccupantMovedIn::~ClientNearOccupantMovedIn() { delete appData; }

ClientNearOccupantMovedOut::ClientNearOccupantMovedOut(unsigned long id)
    : ClientMsg(ClientMsgType::ClientNearOccupantMovedOut), id(id) {}

ClientDisconnected::ClientDisconnected(int state)
    : ClientMsg(ClientMsgType::ClientDisconnected), state(state){};

TheAvatarActivated::TheAvatarActivated(unsigned long id, unsigned short mapId,
                                       Pos const &pos, float direction)
    : ClientMsg(ClientMsgType::TheAvatarActivated), id(id), map(mapId),
      position(pos), direction(direction) {}

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
