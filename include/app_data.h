#ifndef __APPDATA_H__
#define __APPDATA_H__

#include "buffer.h"
class AppData : public Buffer {

public:
  AppData() : Buffer() {}
  AppData(uint size) : Buffer(size) {}
};

#endif // !
