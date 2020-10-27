# Babel


## Installation
```bash
[requires]
zlib/1.2.11@conan/stable
bzip2/1.0.8
boost/1.71.0@conan/stable
sfml/2.5.1@bincrafters/stable

[options]
sfml:graphics=True
sfml:window=True
sfml:audio=True

[generators]
cmake
cmake_find_package

[imports]
bin, *.dll -> ./bin
bin, *.lib -> ./bin
lib, *.lib -> ./bin
lib, *.dylib* -> ./bin

conan remote add conan https://api.bintray.com/conan/conan/conan-center;
conan remote add epitech https://api.bintray.com/conan/epitech/public-conan;
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan;
mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake --build .
```

### Building

```
mkdir build
cd build
conan install .. --build=missing
cmake ..
make
```

Your binary will be create in `/build/bin/`.
