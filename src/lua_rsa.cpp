#include "lua_rsa.h"
#include "openssl/pem.h"
#include "openssl/rsa.h"
#include <iostream>
#include "lua.hpp"

RSA *privKey = nullptr;

RSA *loadKey(std::string &path)
{
    BIO *in = BIO_new(BIO_s_file());
    if (in == nullptr)
    {
        std::cout << "BIO_new failed!" << std::endl;
        return nullptr;
    }
    BIO_read_filename(in, path.c_str());
    RSA *rsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);
    BIO_free(in);
    return rsa;
}

void Init(std::string &path)
{
    privKey = loadKey(path);
    if (nullptr == privKey)
    {
        std::cout << "error load keyfile" << std::endl;
        return;
    }
}

void Free()
{
    if (nullptr != privKey)
        RSA_free(privKey);
}

int Decrypt(RSA *privKey, const char *cipher, size_t len,char * dest,int * destLen)
{
    int ret = RSA_private_decrypt(len, (unsigned char *)cipher, (unsigned char *)dest, privKey, RSA_PKCS1_PADDING);
    if (ret == -1)
    {
        std::cout << "RSA_private_decrypt failed " << std::endl;
        return -1;
    }
    if(nullptr != destLen)
    {
        *destLen = ret;
    }
    return ret;
}

int Encrypt(RSA *privKey, const char *plain, size_t len, char *result, int *resultLen)
{
    int ret = RSA_public_encrypt(len, (unsigned char *)plain, (unsigned char *)result, privKey, RSA_PKCS1_PADDING);
    if (ret == -1)
    {
        std::cout << "RSA_private_encrypt failed" << std::endl;
        return -1;
    }
    if (nullptr != resultLen)
    {
        *resultLen = ret;
    }
    return ret;
}

int lua_init(lua_State *L)
{
    const char *str = luaL_checkstring(L, 1);
    std::string path(str);
    Init(path);
    return 0;
}

int lua_RSADecrypt(lua_State *L)
{
    size_t len;
    const char *msg = luaL_checklstring(L, 1, &len);
    int size = RSA_size(privKey);
    char buf[size];
    memset(buf,0,size);
    int decryptedSize;
    Decrypt(privKey, msg, len,buf,&decryptedSize);
    lua_pushlstring(L, buf,decryptedSize);
    return 1;
}

int lua_RSAEncrypt(lua_State *L)
{
    size_t len;
    const char *msg = luaL_checklstring(L, 1, &len);
    int size = RSA_size(privKey);
    char buf[size];
    memset(buf,0,size);
    int encryptedSize;
    Encrypt(privKey, msg, len,buf,&encryptedSize);
    lua_pushlstring(L, buf,encryptedSize);
    return 1;
}

int lua_RSAFree(lua_State *L)
{
    Free();
    return 0;
}