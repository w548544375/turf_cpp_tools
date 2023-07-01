#include "rsa3.h"

#include <iostream>

void RSAInit(RSAInfo & ri,const char *pub, const char *pri)
{
    BIO *in = NULL;
    in = BIO_new(BIO_s_file());
    BIO_read_filename(in, pub);
    if (in == nullptr)
    {
        std::cout << "public key path invalid!" << std::endl;
        return;
    }
    ri.pub = PEM_read_bio_PUBKEY(in, NULL, NULL, NULL);
    BIO_free(in);
    if (ri.pub == NULL)
    {
        std::cout << "error : read public keys" << std::endl;
        return;
    }
    ri.pubCtx = EVP_PKEY_CTX_new(ri.pub, NULL);
    EVP_PKEY_encrypt_init(ri.pubCtx);
    if (EVP_PKEY_CTX_set_rsa_padding(ri.pubCtx, RSA_PKCS1_PADDING) <= 0)
    {
        std::cout << "error :public set_rsa_padding" << std::endl;
        return;
    }
    BIO *priIn = NULL;
    priIn = BIO_new(BIO_s_file());
    BIO_read_filename(priIn, pri);
    if (priIn == nullptr)
    {
        std::cout << "private key path invalid! " << std::endl;
        return;
    }
    ri.pri = PEM_read_bio_PrivateKey(priIn, NULL, NULL, NULL);
    BIO_free(priIn);
    if (ri.pri == NULL)
    {
        std::cout << "error : read private keys =" << pri << std::endl;
        return;
    }
    ri.priCtx = EVP_PKEY_CTX_new(ri.pri, NULL);
    EVP_PKEY_decrypt_init(ri.priCtx);
    if (EVP_PKEY_CTX_set_rsa_padding(ri.priCtx, RSA_PKCS1_PADDING) <= 0)
    {
        std::cout << "error :private set_rsa_padding" << std::endl;
        return;
    }
}

void RSAFree(RSAInfo & ri)
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

unsigned char * RSAEncrypt(RSAInfo & ri,const unsigned char *plain, int len, size_t &outLen)
{
    if (EVP_PKEY_encrypt(ri.pubCtx, NULL, &outLen, plain, len) <= 0)
    {
        std::cout << "error detemine buffer length " << std::endl;
        return 0;
    }
    std::cout << "before" << std::endl;
    unsigned char * out = (unsigned char *)OPENSSL_malloc(outLen);
    int res = EVP_PKEY_encrypt(ri.pubCtx, out, &outLen, plain, len);
    std::cout << "after" << std::endl;
    return out;
}

unsigned char * RSADecrypt(RSAInfo & ri,const unsigned char *cipher, int len, size_t &outLen)
{
    if (EVP_PKEY_decrypt(ri.priCtx, NULL, &outLen, cipher, len) <= 0)
    {
        std::cout << "[Decrypt]error detemine buffer length " << std::endl;
        return 0;
    }
    unsigned char * out = (unsigned char *)OPENSSL_malloc(outLen);
    int res = EVP_PKEY_decrypt(ri.priCtx, out, &outLen, cipher, len);
    return out;
}
