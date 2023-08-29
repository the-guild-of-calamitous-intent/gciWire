/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

#include <stdint.h> // int types

// not sure the value of this
// #if defined(GCI_SENSORS_DEBUG)
//   #if defined(ARDUINO)
// static void println(const String &s) { Serial.println(s); }
// static void print(const String &s) { Serial.print(s); }
//   #else // apple linux
//     #if defined(__APPLE__) || defined(__linux__)
// typedef std::string String;
//     #endif
// static void println(const String &s) {}
// static void print(const String &s) {}
//   #endif
// #else
//   #if defined(__APPLE__) || defined(__linux__)
// typedef std::string String;
//   #endif
// static void println(const String &s) {}
// static void print(const String &s) {}
// #endif

inline uint32_t to_24b(uint8_t *b) {
  return (uint32_t)b[0] | (uint32_t)b[1] << 8 | (uint32_t)b[2] << 16;
}
inline uint16_t to_16b(uint8_t msb, uint8_t lsb) {
  return ((uint16_t)msb << 8) | (uint16_t)lsb;
}

namespace BITS {
constexpr uint8_t b0 = 1;
constexpr uint8_t b1 = 2;
constexpr uint8_t b2 = 4;
constexpr uint8_t b3 = 8;
constexpr uint8_t b4 = 16;
constexpr uint8_t b5 = 32;
constexpr uint8_t b6 = 64;
constexpr uint8_t b7 = 128;
} // namespace BITS


class SensorI2C {
public:
  SensorI2C(TwoWire *tw, const uint8_t address) : addr(address), i2c(tw) {}

  bool writeRegister(const uint8_t reg, const uint8_t data); // FIXME

  bool readRegisters(const uint8_t reg, const uint8_t count,
                     uint8_t *const data);
  // bool readRegister(const uint8_t reg, uint8_t *const data) {
  //   return readRegisters(reg, 1, value);
  // }
  uint8_t readRegister(uint8_t reg) {
    uint8_t value;
    if (!readRegisters(reg, 1, &value)) return 0;
    return value;
  }

  // inline bool checkErr(int val) { return (val < 0) ? false : true; }

  TwoWire *i2c;
  uint8_t addr;
};

//[ LINUX ]////////////////////////////////////////////////////////////////////////////////
#if defined(__linux__)

bool SensorI2C::writeRegister(const uint8_t reg, const uint8_t data) {
  i2c->set(addr);
  return i2c->write(reg, data);
}

bool SensorI2C::readRegisters(const uint8_t reg, const uint8_t count,
                              uint8_t *const data) {
  i2c->set(addr);
  return i2c->read(reg, count, data);
}


//[ APPLE ]///////////////////////////////////////////////////////////////////////////////
#elif defined(__APPLE__)


bool SensorI2C::writeRegister(const uint8_t reg, const uint8_t data) {
  return true;
}

bool SensorI2C::readRegisters(const uint8_t reg, const uint8_t count,
                              uint8_t *const data) {
  return true;
}

//[ Arduino ]///////////////////////////////////////////////////////////////////////////////
#elif defined(ARDUINO)

bool SensorI2C::writeRegister(const uint8_t reg, const uint8_t data) {
  uint8_t ret_val;
  i2c->beginTransmission(addr);
  i2c->write(reg);
  i2c->write(data);
  i2c->endTransmission();

  delay(10);
  readRegisters(reg, 1, &ret_val);
  if (data == ret_val) return true;

  // println("data write failed verification: " + String(int(data)) +
  //         " != " + String(int(ret_val)));

  return false;
}

bool SensorI2C::readRegisters(const uint8_t reg, const uint8_t count,
                              uint8_t *const data) {
  i2c->beginTransmission(addr);
  i2c->write(reg);
  i2c->endTransmission(false);

  // delay(500);
  // delay(2);

  uint8_t bytes_rx = i2c->requestFrom(addr, count);
  if (bytes_rx == count) {
    for (uint8_t i = 0; i < count; i++) {
      data[i] = i2c->read();
    }
    return true;
  }

  // println("ReadRegisters::bad read: " + String(int(bytes_rx)) +
  //         " expected: " + String(int(count)));

  return false;
}

#endif
