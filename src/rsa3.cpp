#include "rsa3.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include <iostream>

typedef struct RSAInfo
{
    EVP_PKEY *pub;
    EVP_PKEY *pri;
    EVP_PKEY_CTX *pubCtx;
    EVP_PKEY_CTX *priCtx;
} RSA_INFO, *PRSA_INFO;

RSA_INFO ri;

void RSAInit(const char *pub, const char *pri)
{
    FILE *fp = fopen(pub, "r");
    if (fp == nullptr)
    {
        std::cout << "public key path invalid!" << std::endl;
        return;
    }
    ri.pub = PEM_read_PUBKEY(fp, NULL, NULL, NULL);
    fclose(fp);
    ri.pubCtx = EVP_PKEY_CTX_new(ri.pub, NULL);
    EVP_PKEY_encrypt_init(ri.pubCtx);

    FILE *fpriv = fopen(pri, "r");
    if (fpriv == nullptr)
    {
        std::cout << "private key path invalid!" << std::endl;
        return;
    }
    ri.pri = PEM_read_PrivateKey(fpriv, NULL, NULL, NULL);
    fclose(fpriv);
    ri.priCtx = EVP_PKEY_CTX_new(ri.pri, NULL);
    EVP_PKEY_decrypt_init(ri.priCtx);
}

void RSAFree()
{
    if (ri.pub != nullptr)
        EVP_PKEY_free(ri.pub);
    if (ri.pri != nullptr)
        EVP_PKEY_free(ri.pri);
    if (ri.pubCtx != nullptr)
        EVP_PKEY_CTX_free(ri.pubCtx);
    if (ri.priCtx != nullptr)
        EVP_PKEY_CTX_free(ri.priCtx);
}

int RSAEncrypt(const unsigned char * plain,int len,unsigned char * out,size_t outLen)
{
   return EVP_PKEY_encrypt(ri.pubCtx,out,&outLen,plain,len);
}

int RSADecrypt(const unsigned char *cipher, int len, unsigned char *out, size_t outLen)
{
    return EVP_PKEY_decrypt(ri.priCtx,out,&outLen,cipher,len);
}
