#include "buffer.h"
#include <cstdio>
#include <cstring>
#include <memory>
#include <pthread.h>
#include <string>
#define DEFAULT_SIZE 256

#define DEFAULT_GROW 2

Buffer::Buffer() : pos(0), size(0), capicity(DEFAULT_SIZE) {
  buff = new unsigned char[DEFAULT_SIZE];
}

Buffer::Buffer(uint l) : pos(0), size(0), capicity(l) {
  buff = new unsigned char[l];
}

Buffer::~Buffer() { delete[] buff; }

void Buffer::grow(int required) {
  int newCap = capicity * 2;
  if (newCap < capicity + required) {
    newCap = capicity + required * 2;
  }
  unsigned char *newBuff = new unsigned char[newCap];
  memset(newBuff, 0, newCap);
  memcpy(newBuff, buff, size);
  delete[] buff;
  buff = newBuff;
  capicity = newCap;
}

bool Buffer::needGrow(int predicate) { return pos + predicate >= capicity; }

void Buffer::tryGrow(int required) {
  if (this->needGrow(required)) {
    this->grow(required);
  }
}

void Buffer::seek(int po) {
  if (po >= size) {
    pos = size;
  } else {
    pos = po;
  }
}

void Buffer::PutByte(char b) {
  this->tryGrow(1);
  this->buff[pos] = b & 0xFF;
  this->size += 1;
  this->pos += 1;
}

void Buffer::PutShort(short v) {
  this->tryGrow(2);
  this->buff[pos] = (unsigned char)(v >> 0 & 0xffff);
  this->buff[pos + 1] = (unsigned char)(v >> 8 & 0xffff);
  this->size += 2;
  this->pos += 2;
}

void Buffer::PutInt(int v) {
  this->tryGrow(4);
  this->buff[pos] = v >> 0 & 0xFFFFFFFF;
  this->buff[pos + 1] = v >> 8 & 0xFFFFFFFF;
  this->buff[pos + 2] = v >> 16 & 0xFFFFFFFF;
  this->buff[pos + 3] = v >> 24 & 0xFFFFFFFF;
  this->size += 4;
  this->pos += 4;
}

void Buffer::PutLong(long v) {
  this->tryGrow(8);
  this->buff[pos] = v >> 0 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 1] = v >> 8 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 2] = v >> 16 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 3] = v >> 24 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 4] = v >> 32 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 5] = v >> 40 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 6] = v >> 48 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 7] = v >> 56 & 0xFFFFFFFFFFFFFFFF;
  this->size += 8;
  this->pos += 8;
}

void Buffer::PutFloat(float v) {
  this->tryGrow(4);
  unsigned char *pdata = (unsigned char *)&v;
  for (int i = 0; i < 4; i++) {
    this->buff[pos + i] = *(pdata + i);
  }

  this->size += 4;
  this->pos += 4;
}

void Buffer::PutDouble(double v) {
  this->tryGrow(8);
  const unsigned char *pdata = reinterpret_cast<const unsigned char *>(&v);
  for (int i = 0; i < 8; i++) {
    this->buff[pos + i] = *pdata++;
  }
  this->size += 8;
  this->pos += 8;
}

void Buffer::PutString(const char *v, int len) {
  int length = len + 1;
  this->tryGrow(length + 4);
  this->PutInt(length);
  memcpy(this->buff + this->pos, v, length);
  this->size += length;
  this->pos += length;
}

void Buffer::PutString(std::string &v) {
  int len = v.length();
  this->PutString(v.c_str(), len);
}

void Buffer::PutString(const char *v) {
  int len = strlen(v);
  this->PutString(v, len);
}

char Buffer::GetByte() {
  char b = this->buff[this->pos];
  this->pos += 1;
  return b;
}

short Buffer::GetShort() {
  short ret = this->buff[this->pos] & 0xFF;
  ret |= (this->buff[this->pos + 1] << 8) & 0xFF00;
  this->pos += 2;
  return ret;
}

int Buffer::GetInt() {
  int ret = this->buff[this->pos] & 0xFF;
  ret |= (this->buff[this->pos + 1] << 8) & 0xFF00;
  ret |= (this->buff[this->pos + 2] << 16) & 0xFFFF00;
  ret |= (this->buff[this->pos + 3] << 24) & 0xFFFFFF00;
  this->pos += 4;
  return ret;
}

long Buffer::GetLong() {
  long ret = this->buff[this->pos] & 0xFF;
  ret |= (long)(this->buff[this->pos + 1] << 8) & 0xFF00;
  ret |= (this->buff[this->pos + 2] << 16) & 0xFF0000;
  ret |= (this->buff[this->pos + 3] << 24) & 0xFF000000;
  ret |= ((long)this->buff[this->pos + 4] << 32) & 0xFF00000000;
  ret |= ((long)this->buff[this->pos + 5] << 40) & 0xFF0000000000;
  ret |= ((long)this->buff[this->pos + 6] << 48) & 0xFF000000000000;
  ret |= ((long)this->buff[this->pos + 7] << 56) & 0xFF00000000000000;
  this->pos += 8;
  return ret;
}

float Buffer::GetFloat() {
  float f = *(float *)(this->buff + this->pos);
  this->pos += 4;
  return f;
}

double Buffer::GetDouble() {
  double d = *(double *)(this->buff + this->pos);
  this->pos += 8;
  return d;
}

void Buffer::GetString(std::string &str) {
  int len = this->GetInt();
  char *buf = new char[len - 1];
  memcpy(buf, this->buff + this->pos, len - 1);
  str.assign(buf);
  delete[] buf;
  this->pos += len;
}

const char *Buffer::String() {
  char *da = new char[size * 4];
  char temp[4];
  for (int i = 0; i < size; i++) {
    memset(temp, 0, 4);
    sprintf(temp, "%02X ", this->buff[i]);
    strcat(da, temp);
  }
  return da;
}
