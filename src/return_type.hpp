
#pragma once


/*
using reti_t = ret_t<int>;

enum Err: uint8_t {
  OK = 0;
  BAD = 127;
};

reti_t func(int val) {
  reti_t ret;
  if (val == 0) ret.value = 23; // all good, get the int
  else ret.error = Err::BAD;    // bad stuff, return error number
  return ret;
}
*/
template<typename T>
struct ret_t {
  T value;
  int error=0;
  inline explicit operator bool() const noexcept { return error==0 ? true: false; }
};
