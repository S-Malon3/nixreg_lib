# Development Environment

## ESP-IDF Setup (Arch Linux)
Install the AUR package, then run one-time installer:
```bash
/opt/esp-idf/install.sh
```
or if using fish shell
```fish
/opt/esp-idf/install.fish
``` 
Source manually in any terminal session where ESP-IDF is required
```bash
source /opt/esp-idf/export.sh
```

Fish shell:
```fish
source /opt/esp-idf/export.fish
```

## Desktop builds
Requires GCC16.1.1+/Clang 22.1.6+, CMake 4.3.4+, and Boost.Test 1.9q+. On Arch:
```bash
sudo pacman -S cmake boost
```

## Running Tests
```bash
cmake -B build
cmake --build build
cmake --test-dir build --output-on-failure
```
