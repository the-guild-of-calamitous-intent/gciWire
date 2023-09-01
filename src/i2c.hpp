/**************************************\
 * The MIT License (MIT)
 * Copyright (c) 2022 Kevin Walchko
 * see LICENSE for full details
\**************************************/
#pragma once

#include <stdint.h> // int types

#if defined(ARDUINO)
  #include <Arduino.h>
  #include <Wire.h>
#elif defined(__APPLE__)
  #include "wire_apple.hpp"
#elif defined(__linux__)
  #include "wire_linux.hpp"
#endif
