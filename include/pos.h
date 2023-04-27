#ifndef __POS_H__
#define __POS_H__

class Pos {
public:
  long x;
  long y;

public:
  Pos(long, long);
  Pos();
  long Dist(Pos const &);
  long XDist(Pos const &);
  long YDist(Pos const &);
};

#endif // !__POS_H__
