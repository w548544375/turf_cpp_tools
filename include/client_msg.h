#ifndef __CLIENT_MSG_H__
#define __CLIENT_MSG_H__
#include "pos.h"
class AppData;

enum ClientMsgType {
  ETold,
  EBoundTheAvatar,
  EUnboundTheAvatar,
  ENearOccupantMovedIn,
  ENearOccupantMovedOut,
  EDisconnected,
  EAvatarActivated,
  EAvatarDeactivated,
  EAvatarMoved,
  EAvatarMovedToOtherMap,
  ENearOccupantTold = 0xA,
  ENearOccupantMoved = 0xB,
  EToldAt = 0xD
};
// 描述服务器发送给客户端的消息
class ClientMsg {
public:
  ClientMsg(enum ClientMsgType msgType);
  virtual ~ClientMsg(){};

  virtual AppData *Serialize(){return nullptr;}

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

  virtual AppData *Serialize();
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

  virtual AppData *Serialize();
};

class ClientUnboundTheAvatar : public ClientMsg {
private:
  unsigned long id;

public:
  ClientUnboundTheAvatar(unsigned long);
  unsigned long GetID() { return id; };

  virtual AppData *Serialize();
};

class ClientNearOccupantMovedIn : public ClientMsg {
private:
  unsigned long id;
  unsigned short map;
  Pos position;
  float direction;
  AppData *appData;

public:
  ClientNearOccupantMovedIn(unsigned long, Pos const &, float, AppData *);
  ~ClientNearOccupantMovedIn();
  float GetDirection() { return direction; }
  AppData *GetAppData() { return appData; }
  unsigned long GetID() { return id; }
  Pos GetPosition() { return position; }

  virtual AppData *Serialize();
};

class ClientNearOccupantMovedOut : public ClientMsg {
private:
  unsigned long id;

public:
  ClientNearOccupantMovedOut(unsigned long);
  unsigned long GetID() { return id; }

  virtual AppData *Serialize();
};

class ClientDisconnected : public ClientMsg {
private:
  int state;

public:
  ClientDisconnected(int);
  int GetState() { return state; }

  virtual AppData *Serialize();
};

class TheAvatarActivated : public ClientMsg {
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

  virtual AppData *Serialize();
};

class TheAvatarDeactivated : public ClientMsg {
private:
  unsigned long id;

public:
  TheAvatarDeactivated(unsigned long);
  unsigned long GetID() { return id; }

  virtual AppData *Serialize();
};

class TheAvatarMoved : public ClientMsg {
private:
  Pos position;
  float direction;
  long serverTime;
  short sequence;

public:
  TheAvatarMoved(short seq, Pos const &, float, long);
  virtual ~TheAvatarMoved();
  float GetDirection() { return direction; };
  Pos GetPosition() { return position; };
  long GetServerTime() { return serverTime; };
  short GetSequence() { return this->sequence; };
  virtual AppData *Serialize();
};

class TheAvatarMovedToOtherMap : public ClientMsg {
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

  virtual AppData *Serialize();
};

class NearOccupantTold : public ClientMsg {
private:
  unsigned long id;
  AppData *appData;

public:
  NearOccupantTold(unsigned long, AppData *);
  ~NearOccupantTold();
  AppData *GetAppData();
  unsigned long GetID();

  virtual AppData *Serialize();
};

class NearOccupantMoved : public ClientMsg {
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

  virtual AppData *Serialize();
};

class ClientToldAt : public ClientMsg {
private:
  Pos position;
  AppData *appData;

public:
  ClientToldAt(Pos const &, AppData *);
  ~ClientToldAt();
  AppData *GetAppData() { return appData; }
  Pos GetPosition() { return position; }

  virtual AppData *Serialize();
};

#endif // !__CLIENT_MSG_H__
