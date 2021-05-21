# R-Type


## Conan remote needed
```bash
conan remote add conan https://api.bintray.com/conan/conan/conan-center
conan remote add epitech https://api.bintray.com/conan/epitech/public-conan
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
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
 
