#include "buffer.h"
#include "lua.hpp"
#include <cstdio>
#include <cstring>
#include <ios>
#include <string>
typedef unsigned char byte;

int main(int argc, char *argv[]) {
  Buffer buf;
  buf.PutByte(0x5);
  buf.PutShort(0x1409);
  buf.PutInt(0x64);
  buf.PutFloat(1.0f);
  buf.PutDouble(1.0);
  buf.PutLong(0x64);
  char str[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '\0'};
  std::cout << "length of [ABCDEFG] = " << strlen(str) << std::endl;
  buf.PutString(str, strlen(str));

  const char *result = buf.String();
  std::cout << result << std::endl;
  delete[] result;

  buf.seek(0);
  std::cout << "byte ?" << (buf.GetByte() == 0x5) << std::endl;
  std::cout << "short ?" << (buf.GetShort() == 0x1409) << std::endl;
  std::cout << "int ?" << (buf.GetInt() == 0x64) << std::endl;
  std::cout << "float ?" << (buf.GetFloat() == 1.0f) << std::endl;
  std::cout << "double ?" << (buf.GetDouble() == 1.0f) << std::endl;
  std::cout << "long ?" << (buf.GetLong() == 0x64) << std::endl;

  std::string str2;
  buf.GetString(str2);
  std::cout << "string " << strcmp(str2.c_str(), str) << std::endl;
  auto L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "../test.lua");
  lua_close(L);
  return 0;
}
