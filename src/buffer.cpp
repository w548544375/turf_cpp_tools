#include "buffer.h"
#include <cstdio>
#include <cstring>
#include <memory>
#include <pthread.h>
#include <string>
#define DEFAULT_SIZE 256

#define DEFAULT_GROW 2

#define INC_SIZE(x) \
  if (x >= size)    \
  {                 \
    size = x;       \
  }

Buffer::Buffer() : pos(0), size(0), capicity(DEFAULT_SIZE)
{
  buff = new unsigned char[DEFAULT_SIZE];
  memset(buff, 0, capicity);
}

Buffer::Buffer(uint l) : pos(0), size(0), capicity(l)
{
  std::cout << " buffer length " << l << std::endl;
  buff = new unsigned char[l];
}

Buffer::Buffer(const char *buf, int len) : pos(0), size(len), capicity(len)
{
  buff = new unsigned char[len];
  memset(buff, 0, capicity);
  memcpy(buff, buf, len);
}

Buffer::~Buffer() { delete[] buff; }

void Buffer::grow(int required)
{
  int newCap = capicity * 2;
  if (newCap < capicity + required)
  {
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

void Buffer::tryGrow(int required)
{
  if (this->needGrow(required))
  {
    this->grow(required);
  }
}

void Buffer::seek(int po)
{
  if (po >= capicity)
  {
    this->pos = capicity;
  }
  else
  {
    this->pos = po;
  }
  INC_SIZE(pos);
}

void Buffer::PutByte(char b)
{
  this->tryGrow(1);
  this->buff[pos] = b & 0xFF;
  this->pos += 1;
  INC_SIZE(pos);
}

void Buffer::PutBytes(const char *head, int len)
{
  this->tryGrow(len);
  memcpy((this->buff + pos), head, len);
  this->pos += len;
  INC_SIZE(pos);
}

void Buffer::PutShort(short v)
{
  this->tryGrow(2);
  this->buff[pos] = (unsigned char)(v >> 0 & 0xffff);
  this->buff[pos + 1] = (unsigned char)(v >> 8 & 0xffff);
  this->pos += 2;
  INC_SIZE(pos);
}

void Buffer::PutInt(int v)
{
  this->tryGrow(4);
  this->buff[pos] = v >> 0 & 0xFFFFFFFF;
  this->buff[pos + 1] = v >> 8 & 0xFFFFFFFF;
  this->buff[pos + 2] = v >> 16 & 0xFFFFFFFF;
  this->buff[pos + 3] = v >> 24 & 0xFFFFFFFF;
  this->pos += 4;
  INC_SIZE(pos);
}

void Buffer::PutLong(long v)
{
  this->tryGrow(8);
  this->buff[pos] = v >> 0 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 1] = v >> 8 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 2] = v >> 16 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 3] = v >> 24 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 4] = v >> 32 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 5] = v >> 40 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 6] = v >> 48 & 0xFFFFFFFFFFFFFFFF;
  this->buff[pos + 7] = v >> 56 & 0xFFFFFFFFFFFFFFFF;
  this->pos += 8;
  INC_SIZE(pos);
}

void Buffer::PutFloat(float v)
{
  this->tryGrow(4);
  unsigned char *pdata = (unsigned char *)&v;
  for (int i = 0; i < 4; i++)
  {
    this->buff[pos + i] = *(pdata + i);
  }
  this->pos += 4;
  INC_SIZE(pos);
}

void Buffer::PutDouble(double v)
{
  this->tryGrow(8);
  const unsigned char *pdata = reinterpret_cast<const unsigned char *>(&v);
  for (int i = 0; i < 8; i++)
  {
    this->buff[pos + i] = *pdata++;
  }
  this->pos += 8;
  INC_SIZE(pos);
}

void Buffer::PutString(const char *v, int len)
{
  int length = len + 1;
  this->tryGrow(length + 4);
  this->PutInt(length);
  memcpy(this->buff + this->pos, v, length);
  this->pos += length;
  INC_SIZE(pos);
}

void Buffer::PutString(std::string &v)
{
  int len = v.length();
  this->PutString(v.c_str(), len);
}

void Buffer::PutString(const char *v)
{
  int len = strlen(v);
  this->PutString(v, len);
}

void Buffer::Put(Buffer *buf)
{
  this->tryGrow(buf->size);
  buf->seek(0);
  memcpy(this->buff + this->pos, buf->buff, buf->size);
  this->pos += buf->size;
  INC_SIZE(pos);
}

char Buffer::GetByte()
{
  char b = this->buff[this->pos];
  this->pos += 1;
  return b;
}

void Buffer::GetBytes(char *head, int len)
{
  memcpy(head, this->buff + this->pos, len);
  this->pos += len;
}

short Buffer::GetShort()
{
  short ret = this->buff[this->pos] & 0xFF;
  ret |= (this->buff[this->pos + 1] << 8) & 0xFF00;
  this->pos += 2;
  return ret;
}

int Buffer::GetInt()
{
  int ret = this->buff[this->pos] & 0xFF;
  ret |= (this->buff[this->pos + 1] << 8) & 0xFF00;
  ret |= (this->buff[this->pos + 2] << 16) & 0xFFFF00;
  ret |= (this->buff[this->pos + 3] << 24) & 0xFFFFFF00;
  this->pos += 4;
  return ret;
}

long Buffer::GetLong()
{
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

float Buffer::GetFloat()
{
  float f = *(float *)(this->buff + this->pos);
  this->pos += 4;
  return f;
}

double Buffer::GetDouble()
{
  double d = *(double *)(this->buff + this->pos);
  this->pos += 8;
  return d;
}

const char * Buffer::GetString(int * rlen)
{
  int len = this->GetInt();
  char *buf = new char[len - 1];
  memcpy(buf, this->buff + this->pos, len - 1);
  *rlen = len - 1;
  this->pos += len;
  return buf;
}

void Buffer::String(std::string &str)
{
  char *da = new char[size * 4];
  char temp[4];
  for (int i = 0; i < size; i++)
  {
    memset(temp, 0, 4);
    sprintf(temp, "%02X ", this->buff[i]);
    str.append(temp);
  }
}

unsigned char * Buffer::Buf()
{
  unsigned char * buf = new unsigned char[size];
  memcpy(buf,buff,size);
  return buf;
}

void Buffer::reset()
{
  this->pos = 0;
  this->size = 0;
}
