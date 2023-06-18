#ifndef __BUFFER_H__
#define __BUFFER_H__
#include <iostream>
#include <memory>
#include <string>

class Buffer {
public:
  Buffer();
  Buffer(uint);
  Buffer(const char * buf,int len);
  ~Buffer();

  void PutByte(char);
  void PutBytes(const char * head,int len);
  void PutShort(short);
  void PutInt(int);
  void PutFloat(float);
  void PutLong(long);
  void PutDouble(double);
  void PutString(const char *, int);
  void PutString(std::string &);
  void PutString(const char *);
  void Put(Buffer *buf);

  char GetByte();
  void GetBytes(char * head,int len);
  short GetShort();
  int GetInt();
  float GetFloat();
  long GetLong();
  double GetDouble();
  void GetString(std::string &str);

  void seek(int);

  int Size() { return size; }
  int Pos() { return pos; }
  int Cap() { return capicity; }
  unsigned char * Buf();

  void reset();
  void String(std::string &);

private:
  int pos;
  int size;
  int capicity;
  unsigned char *buff;

  void grow(int);
  bool needGrow(int);
  void tryGrow(int);
};

#endif // !__BUFFER_H__
