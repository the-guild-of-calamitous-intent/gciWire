
#pragma once

#include <type_traits> // std::is_enum

/*
enum Err: uint8_t {
  OK = 0; // always need this
  BAD = 127;
};

using reti_t = ret_t<int, Err>;

reti_t func(int val) {
  reti_t ret;
  if (val == 0) ret.value = 23; // all good, get the int
  else ret.error = Err::BAD;    // bad stuff, return error number
  return ret;
}
*/
template<typename T, typename E>
struct ret_t {
  static_assert(std::is_enum<E>::value,"E needs to be an enum");
  T value;
  E error=E::OK;
  inline explicit operator bool() const noexcept { return error==E::OK ? true: false; }
};
