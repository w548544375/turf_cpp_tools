#include "pos.h"
#include <cmath>
Pos::Pos() {}

Pos::Pos(long x, long y) : x(x), y(y) {}

long Pos::Dist(const Pos &another) {
  long xdis = std::pow(another.x - x, 2);
  long ydis = std::pow(another.y - y, 2);
  long dist = std::sqrt(xdis + ydis);
  return dist;
}

long Pos::XDist(const Pos &another) {
  long xpow = std::pow(another.x - x, 2);
  return std::sqrt(xpow);
}

long Pos::YDist(const Pos &another) {
  long ypow = std::pow(another.y - y, 2);
  return std::sqrt(ypow);
}
