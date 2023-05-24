
#include "cryptor.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstring>
Cryptor::Cryptor() : Cryptor(true)
{
}

Cryptor::Cryptor(bool usingCrypt) : isCrypt(usingCrypt)
{
    if (isCrypt)
    {
        for (int i = 0; i < 256; i++)
        {
            cryptoTable[i] = i;
        }
    }
}

Cryptor::~Cryptor()
{
    
}

void Cryptor::SetRoundBound(int round, unsigned char bound)
{
    if (round > 1)
    {
        return;
    }
    rounds[round].bound = bound;
}

void Cryptor::SetRoundBegin(int round, unsigned char begin)
{
    if (round > 1)
    {
        return;
    }
    rounds[round].encryptIdx = begin;
    rounds[round].decryptIdx = begin;
}

void Cryptor::Feed(unsigned char *seed, int len)
{
    // char tmp[16];
    // for(int i = 0;i < len ;i ++)
    // {
    //     memset(tmp,0,16);
    //     unsigned char v = seed[i] & 0xFF;
    //     sprintf(tmp,"%02X %c",v,(i + 1)%16 ==0? '\n' : ' ');
    //     std::cout << tmp;
    // }
    // std::cout << std::endl;
    if (!isCrypt)
    {
        return;
    }
    for (int i = 0; i < len; i++)
    {
        int k = 0;
        for (int j = 0; j < 256; j++)
        {
            int u = ((int)seed[i] + k) & 0x80000FF;
            int tmp = cryptoTable[j];
            cryptoTable[j] = cryptoTable[u];
            cryptoTable[u] = tmp;
            k += 2;
        }
    }
}

void Cryptor::Encrypt(unsigned char *cipher, int len)
{
    for (int j = 0; j < 2; j++)
    {
        unsigned char &begin = rounds[j].encryptIdx;
        for (int i = 0; i < len; i += 2)
        {
            cipher[i] += cryptoTable[begin];
            begin += 1;
            if (begin > rounds[j].bound)
            {
                begin = rounds[j].bound;
            }
        }
    }
}

void Cryptor::Decrypt(unsigned char *cipher, int len)
{
    for (int j = 1; j >= 0; j--)
    {
        unsigned char &begin = rounds[j].decryptIdx;
        for (int i = 0; i < len; i += 2)
        {
            cipher[i] -= cryptoTable[begin];
            begin += 1;
            if (begin > rounds[j].bound)
            {
                begin = rounds[j].bound;
            }
        }
    }
}

std::string Cryptor::String()
{
    std::stringstream strstream;
    char tmp[512];
    memset(tmp,'\0',512);
    sprintf(tmp,"Crypto { isCrypt: %d,rounds: [",isCrypt);
    strstream <<tmp;
    for(ROUND_INFO info : rounds) {
        memset(tmp,'\0',512);
        sprintf(tmp,"{ DecryptStart: %d,EncryptStart: %d,Max: %d}",info.decryptIdx,info.encryptIdx,info.bound);
        strstream << tmp;
    }
    strstream << "],\n";
    strstream << "Table: [";
    char buf[256 * 4];
    memset(buf,'\0',256 * 4);
    for(int i =0 ;i < 256;i++) {
         memset(tmp,'\0',512);
         sprintf(tmp,"%02X%c",cryptoTable[i], (i + 1) % 16 == 0 ? '\n': ' ' );
         strcat(buf,tmp);
    }
    strstream << buf;
    strstream << "]\n";
    return strstream.str();
}
