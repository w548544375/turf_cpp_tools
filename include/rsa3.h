#ifndef __RSA3_H__
#define __RSA3_H__
#include <cstddef>

void RSAInit(const char * pub,const char * pri);

unsigned char * RSAEncrypt(const unsigned char *plain, int len, size_t &outLen);

unsigned char * RSADecrypt(const unsigned char *cipher, int len, size_t &outLen);

void RSAFree();
#endif