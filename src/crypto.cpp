#include "crypto.h"

Crypto::Crypto() : isCrypt(true)
{
    Crypto(isCrypt);
}

Crypto::Crypto(bool usingCrypt) : isCrypt(usingCrypt)
{
    if (isCrypt)
    {
        for (int i = 0; i < 256; i++)
        {
            cryptoTable[i] = i;
        }
    }
}

Crypto::~Crypto()
{
    delete[] rounds;
    delete[] cryptoTable;
}

void Crypto::SetRoundBound(int round, unsigned char bound)
{
    if (round > 1)
    {
        return;
    }
    rounds[round].bound = bound;
}

void Crypto::SetRoundBegin(int round, unsigned char begin)
{
    if (round > 1)
    {
        return;
    }
    rounds[round].encryptIdx = begin;
    rounds[round].decryptIdx = begin;
}

void Crypto::Feed(unsigned char *seed, int len)
{
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
            cryptoTable[j] = seed[u];
            cryptoTable[u] = tmp;
            k += 2;
        }
    }
}

void Crypto::Encrypt(unsigned char *cipher, int len)
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

void Crypto::Decrypt(unsigned char *cipher, int len)
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
