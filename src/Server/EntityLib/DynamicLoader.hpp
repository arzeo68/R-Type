/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** DynamicLoader
*/

#ifndef SOLOADER_HPP_
#define SOLOADER_HPP_

#ifdef _WIN32
    #include <Server/EntityLib/dlfcn.h>
#elif
    #include "dlfcn.h"
#endif
#include <iostream>

template <typename T>
class DynamicLoader {
    public:
        DynamicLoader(const std::string &filename)
        {
            dlerror();
            this->_lib = dlopen(filename.c_str(), RTLD_LAZY);
            if (this->_lib == nullptr) {
                std::cerr << dlerror() << std::endl;
            }
            dlerror();
            T *(*func)() = reinterpret_cast<T *(*)()>(dlsym(this->_lib, "entry"));
            if (func == nullptr) {
                std::cerr << dlerror() << std::endl;
            }
            this->_instance = func();
        }
        ~DynamicLoader() {
            if (this->_instance != nullptr)
                delete this->_instance;
            if (this->_lib != nullptr)
                dlclose(this->_lib);
        }
        T *operator ->() {
            return (this->_instance);
        }
    private:
        void *_lib = nullptr;
        T *_instance = nullptr;
};

#endif /* !SOLOADER_HPP_ */