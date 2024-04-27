

#pragma once

#include "hardware/i2c.h"
#include <stdint.h> // uint8_t
#include <stddef.h> // size_t

// constexpr uint8_t I2C_MAX_BUFFER_SIZE = 32;

class TwoWire {
  uint8_t addr;

public:
  // TwoWire() {}
  // ~TwoWire() {}

  // void begin(int sda = 0, int scl = 0) {}
  // void begin(int sda, int scl, uint8_t address) {}
  // void set(uint8_t address) {}
  // void setClock(uint32_t) {}
  // void setClockStretchLimit(uint32_t) {}
  // void beginTransmission(uint8_t) {}
  // void beginTransmission(int) {}
  inline
  uint8_t endTransmission(void) { return 0; }
  inline
  uint8_t endTransmission(uint8_t) { return 0; }
  // size_t requestFrom(uint8_t address, size_t size, bool sendStop) { return 0; }
  // // uint8_t status();

  // uint8_t requestFrom(uint8_t, uint8_t) { return 0; }
  // uint8_t requestFrom(uint8_t, uint8_t, uint8_t) { return 0; }
  // uint8_t requestFrom(int, int) { return 0; }
  // uint8_t requestFrom(int, int, int) { return 0; }

  // size_t write(uint8_t) { return 0; }
  // bool write(const uint8_t reg, const uint8_t data) { return true; }
  // uint8_t read(void) { return 0; }
  // bool read(const uint8_t reg, const uint8_t count, uint8_t *const data) { return true; }

  TwoWire(): addr(0) {}
  ~TwoWire() {}

  // Either i2c0 or i2c1
  void init(uint baud, uint8_t port, uint8_t pin_sda, uint8_t pin_scl) {
    if (port == 0) i2c = i2c0;
    else if (port == 1) i2c = i2c1;
    // This example will use I2C0 on the default SDA and SCL pins (GP4, GP5 on a Pico)
    i2c_init(i2c, baud);
    gpio_set_function(pin_sda, GPIO_FUNC_I2C);
    gpio_set_function(pin_scl, GPIO_FUNC_I2C);
    gpio_pull_up(pin_sda);
    gpio_pull_up(pin_scl);
  }

  inline
  void beginTransmission(uint8_t address) { addr = address; }

  inline
  void requestFrom(uint8_t address, uint8_t count) { addr = address; }

  // inline
  // void endTransmission() {}

  void write(const uint8_t reg, const uint8_t data) {
    uint8_t out[2]{reg, data};
    i2c_write_blocking(i2c, addr, out, 2, I2C_RELEASE_BUS);
  }

  bool read(const uint8_t reg, const uint8_t data_size, uint8_t *const data) {
    i2c_write_blocking(i2c, addr, &reg, 1, I2C_HOLD_BUS);
    int ret = i2c_read_blocking(i2c, addr, data, data_size, I2C_RELEASE_BUS);
    if (ret < 0) return false;
    return true;
  }

  inline
  size_t available() {
    return i2c_get_read_available(i2c);
  }
};