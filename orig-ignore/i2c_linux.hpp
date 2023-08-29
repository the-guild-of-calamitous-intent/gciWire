#pragma once
#if defined(__linux__)

#include <stdint.h>
#include <array>
#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <string>
#include <array>

#include "return_type.hpp"

using retu8_t = ret_t<uint8_t>;
// using reta_t = ret_t<array<uint8_t>, 32>;


class TwoWire {
public:

  TwoWire() {}

  bool begin(const std::string& path="/dev/i2c-1") {
    if ((fd = open(path.c_str(), O_RDWR)) < 0) {
      //ERROR HANDLING: you can check errno to see what went wrong
      printf("Failed to open the i2c bus");
      return false;
    }
    return true;
  }

  bool setClock(uint32_t speed) {
    if (speed != 100000 || speed != 400000) return false;
    // not sure this works
    // ioctl(fd, I2C_SET_SPEED, speed);
    return true;
  }

  inline ssize_t write(uint8_t data) { return ::write(fd, &data, 1); }
  inline ssize_t write(uint8_t *data, size_t len) { return ::write(fd, data, len); }

  inline retu8_t read() {
    retu8_t ret;
    int num = ::read(fd, &ret.value, 1); // handle error??
    if (num > 0) return ret;
    // ret.value = buffer[0];
    return ret;
  }

  size_t available() { return 0; }

  bool beginTransmission(uint8_t addr) {
    this->addr = addr;
    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
      printf("Failed to acquire bus access and/or talk to slave.\n");
      //ERROR HANDLING; you can check errno to see what went wrong
      return false;
    }
    return true;
  }

  void endTransmission(bool end=true) {}

  void requestFrom(uint8_t addr, size_t count) {}

  protected:
  int fd;
  uint8_t addr;
  // uint8_t buffer[32];
};

#endif
