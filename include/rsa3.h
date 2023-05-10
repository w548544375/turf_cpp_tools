#ifndef __RSA3_H__
#define __RSA3_H__
#include <cstddef>
#include "openssl/rsa.h"
#include "openssl/evp.h"
#include "openssl/pem.h"

typedef struct RSAInfo
{
    EVP_PKEY *pub;
    EVP_PKEY *pri;
    EVP_PKEY_CTX *pubCtx;
    EVP_PKEY_CTX *priCtx;
} RSA_INFO, *PRSA_INFO;


void RSAInit(RSAInfo & ri,const char * pub,const char * pri);

unsigned char * RSAEncrypt(RSAInfo & ri,const unsigned char *plain, int len, size_t &outLen);

unsigned char * RSADecrypt(RSAInfo & ri,const unsigned char *cipher, int len, size_t &outLen);

void RSAFree(RSAInfo & ri);
#endif