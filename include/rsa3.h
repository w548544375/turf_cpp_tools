#ifndef __RSA3_H__
#define __RSA3_H__


void RSAInit(const char * pub,const char * pri);

int RSAEncrypt(const unsigned char * plain,int len,unsigned char * out,int outLen);

int RSADecrypt(const unsigned char * cipher,int len,unsigned char * out,int outLen);

void RSAFree();
#endif