#ifndef __CRYPTO_H__
#define __CRYPTO_H__

typedef struct RoundInfo
{
  /* data */
  unsigned char bound;
  unsigned char decryptIdx;
  unsigned char encryptIdx;
} ROUND_INFO,*PROUND_INFO;



class Crypto {
public:
  Crypto();
  Crypto(bool usingCrypt);
  ~Crypto();

  void SetRoundBound(int round,unsigned char bound);
  void SetRoundBegin(int round,unsigned char begin);

  void Feed(unsigned char *, int);

  void Encrypt(unsigned char *, int);
  void Decrypt(unsigned char *, int);

private:
  bool isCrypt;
  // 第一轮加解密最大值以及当前计数
  ROUND_INFO rounds[2];
  unsigned char cryptoTable[256];
};

#endif // !__CRYPTO_H__
