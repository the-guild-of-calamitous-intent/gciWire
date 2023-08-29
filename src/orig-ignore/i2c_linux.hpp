#pragma once
#if defined(__linux__)

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port

class TwoWire {
public:

  TwoWire() {}

  bool begin(const std::string& path="/dev/i2c-1") {
    if ((file_i2c = open(path.c_str(), O_RDWR)) < 0) {
      //ERROR HANDLING: you can check errno to see what went wrong
      printf("Failed to open the i2c bus");
      return false;
    }
    return true;
  }

  void setClock(uint32_t speed) {}

  inline ssize_t write(uint8_t data) { return ::write(fd, data, 1); }
  inline ssize_t write(uint8_t *data, size_t len) { return ::write(fd, data, len); }
  inline uint8_t read() {
    ssize_t num = ::read(fd, buffer, 1); // handle error??
    return buffer[0];
  }

  size_t available() { return 0; }

  void beginTransmission(uint8_t addr) {
    this->addr = addr;
    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
      printf("Failed to acquire bus access and/or talk to slave.\n");
      //ERROR HANDLING; you can check errno to see what went wrong
      return;
    }
  }

  void endTransmission(bool end=true) {}

  void requestFrom(uint8_t addr, size_t count) {}

  protected:
  int fd;
  const uint8_t addr;
  uint8_t buffer[32];
};

#endif