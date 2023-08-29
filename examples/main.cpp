
#include "i2c.hpp"

TwoWire tw;

int main() {
  bool ok = tw.setClock(100000);
  SensorI2C sen(&tw, 0x33);
  return 0;
}
