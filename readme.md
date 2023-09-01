# gciWire

**move sensor.hpp to gcisensors**

```cpp
#include <stdint.h>
#include <iostream>

using namespace std;

template<typename T>
struct ret_t {
  T value;
  int error=0;
  inline explicit operator bool() const noexcept { return error==0 ? true: false; }
};

using retf_t = ret_t<float>;

enum Err: uint8_t {
  OK = 0,
  BAD = 1,
  REALBAD = 2
};

retf_t test(int val=0) {
  retf_t ret;
  if (val == 0) ret.value = 1.2345f;
  else if (val == 1) ret.error = Err::BAD;
  else ret.error = Err::REALBAD;
  return ret;
}

int main() {
  retf_t ret = test(2);

  if (ret) cout << ret.value << " " << ret.error << endl;
  else cout << "wtf: " << ret.error << endl;

  return 0;
}
```

## Why?

Trying to make a cross platform I2C library for Linux and Arduino, but
also be able to do simple tests on macOS. This is based off of Arduino
Wire library.

# Setup

To get i2c headers, Debian/Ubuntu: `sudo apt-get install libi2c-dev`

# MIT License

**Copyright (c) 2022 The Guild of Calamitous Intent**

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
