# Nixreg

A C++ library for driving nixie tubes via HV shift registers.

## Features (Planned)
 - Generic `ShadowRegister` abstraction for HV shift registers
 - `NixieFloat` type for storing and displaying multi-digit values
 - Optional Decimal point support (IN-12B and similar)
 - ESP32 target support

## Requirements
 - GCC 16.1.1+ or Clang 22.1.6+
 - CMake 4.3.4+
 - Boost.Test 1.91+

### ESP32
 - ESP-IDF v6.0.1+ (`esp-idf` AUR package)

See [`DEVELOPMENT.md`](DEVELOPMENT.md) for environment setup.
:wq
## License
TBD
