#pragma once
#if defined(__APPLE__)

static void delay(uint64_t sleep) {}

class TwoWire {
public:

  TwoWire() {}
  bool begin(const std::string& path="/dev/i2c-1") { return false; }
  void setClock(uint32_t speed) {}
  inline ssize_t write(uint8_t data) { return 0; }
  inline ssize_t write(uint8_t *data, size_t len) { return 0; }
  inline uint8_t read() { return 0; }
  size_t available() { return 0; }
  void beginTransmission(uint8_t addr) {}
  void endTransmission(bool end=true) {}
  uint8_t requestFrom(uint8_t addr, size_t count) { return 0; }

protected:
  uint8_t addr;

};

#endif