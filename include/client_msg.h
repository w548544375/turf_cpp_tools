#ifndef __CLIENT_MSG_H__
#define __CLIENT_MSG_H__
#include "pos.h"
class AppData;

enum ClientMsgType {
  ClientTold,
  ClientBoundTheAvatar,
  ClientUnboundTheAvatar,
  ClientNearOccupantMovedIn,
  ClientNearOccupantMovedOut,
  ClientDisconnected,
  TheAvatarActivated,
  TheAvatarDeactivated,
  TheAvatarMoved,
  TheAvatarMovedToOtherMap,
  NearOccupantTold = 0xA,
  NearOccupantMoved = 0xB,
  ClientToldAt = 0xD
};

class ClientMsg {
public:
  ClientMsg(enum ClientMsgType msgType);
  virtual ~ClientMsg();

  virtual AppData *Serialize();

protected:
  enum ClientMsgType msgType;

public:
  enum ClientMsgType GetType() { return msgType; };
};

class ClientTold : public ClientMsg {
private:
  AppData *appData;

public:
  ClientTold(AppData *);
  AppData *GetAppData() { return appData; };

  ~ClientTold();

  AppData *Serialize();
};

class ClientBoundTheAvatar : public ClientMsg {
private:
  unsigned long id;
  AppData *appData;

public:
  ClientBoundTheAvatar(unsigned long, AppData *);
  ~ClientBoundTheAvatar();
  unsigned long GetID() { return id; };
  AppData *GetAppData() { return appData; };

  AppData *Serialize();
};

class ClientUnboundTheAvatar : public ClientMsg {
private:
  unsigned long id;

public:
  ClientUnboundTheAvatar(unsigned long);
  unsigned long GetID() { return id; };

  AppData *Serialize();
};

class ClientNearOccupantMovedIn : ClientMsg {
private:
  unsigned long id;
  unsigned short map;
  Pos position;
  float direction;
  AppData *appData;

public:
  ClientNearOccupantMovedIn(unsigned long, unsigned short, Pos const &, float,
                            AppData *);
  ~ClientNearOccupantMovedIn();
  float GetDirection() { return direction; }
  AppData *GetAppData() { return appData; }
  unsigned long GetID() { return id; }
  unsigned short GetMap() { return map; }
  Pos GetPosition() { return position; }

  AppData *Serialize();
};

class ClientNearOccupantMovedOut : ClientMsg {
private:
  unsigned long id;

public:
  ClientNearOccupantMovedOut(unsigned long);
  unsigned long GetID() { return id; }

  AppData *Serialize();
};

class ClientDisconnected : ClientMsg {
private:
  int state;

public:
  ClientDisconnected(int);
  int GetState() { return state; }

  AppData *Serialize();
};

class TheAvatarActivated : ClientMsg {
private:
  unsigned long id;
  unsigned short map;
  Pos position;
  float direction;

public:
  TheAvatarActivated(unsigned long, unsigned short, Pos const &, float);
  float GetDirection() { return direction; }
  unsigned long GetID() { return id; }
  unsigned short GetMap() { return map; }
  Pos GetPosition() { return position; }

  AppData *Serialize();
};

class TheAvatarDeactivated : ClientMsg {
private:
  unsigned long id;

public:
  TheAvatarDeactivated(unsigned long);
  unsigned long GetID() { return id; }

  AppData *Serialize();
};

class TheAvatarMoved : ClientMsg {
private:
  unsigned long id;
  bool isConfirm;
  Pos position;
  float direction;
  long serverTime;
  AppData *appData;

public:
  TheAvatarMoved(unsigned long, bool, Pos const &, float, long, AppData *);
  ~TheAvatarMoved();
  AppData *GetAppData() { return appData; };
  float GetDirection() { return direction; };
  unsigned long GetID() { return id; };
  Pos GetPosition() { return position; };
  long GetServerTime() { return serverTime; };
  bool IsConfirm() { return isConfirm; };

  AppData *Serialize();
};

class TheAvatarMovedToOtherMap : ClientMsg {
private:
  unsigned long id;
  unsigned short map;
  Pos position;
  float direction;
  AppData *appData;

public:
  TheAvatarMovedToOtherMap(unsigned long, unsigned short, Pos const &, float,
                           AppData *);
  ~TheAvatarMovedToOtherMap();
  float GetDirection() { return direction; }
  unsigned long GetID() { return id; }
  unsigned short GetMap() { return map; }
  Pos GetPosition() { return position; }
  AppData *GetAppData() { return appData; }

  AppData *Serialize();
};

class NearOccupantTold : ClientMsg {
private:
  unsigned long id;
  AppData *appData;

public:
  NearOccupantTold(unsigned long, AppData *);
  ~NearOccupantTold();
  AppData *GetAppData();
  unsigned long GetID();

  AppData *Serialize();
};

class NearOccupantMoved : ClientMsg {
private:
  unsigned long id;
  Pos pos;
  float direction;
  AppData *appData;

public:
  NearOccupantMoved(unsigned long, Pos, float, AppData *);
  ~NearOccupantMoved();
  AppData *GetAppData() { return appData; }
  float GetDirection() { return direction; }
  unsigned long GetID() { return id; }
  Pos GetPosition() { return pos; }

  AppData *Serialize();
};

class ClientToldAt : ClientMsg {
private:
  Pos position;
  AppData *appData;

public:
  ClientToldAt(Pos const &, AppData *);
  ~ClientToldAt();
  AppData *GetAppData() { return appData; }
  Pos GetPosition() { return position; }

  AppData *Serialize();
};

#endif // !__CLIENT_MSG_H__
