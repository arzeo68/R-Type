/*
** EPITECH PROJECT, 2020
** OOP_boostrap_Arcade
** File description:
** Header class file for lib loading functions
*/

#ifndef OOP_ARCADE DynamicLoader_HPP_
#define OOP_ARCADE_DYNAMICLOADER_HPP_

#include <string>
#ifdef __linux__
#include <dlfcn.h>
#elif defined(_WIN32)
#include <Server/DynamicLoader/dlfcn.h>
#endif
#include <iostream>
#include "Exceptions.hpp"
#include "../Common/Log.hpp"

namespace DynamicLoader {
    /**
     * The class allows to load a library and associate a type determined by the template T.
     * @tparam T Type which will be associated to the library.
     */
    template <typename T>
    class LibraryLoader {
        public:
            static constexpr const char *ENTRY_POINT_NAME = "entry";

         LibraryLoader(uint16_t logLevel = Common::Log::g_AllLogLevel) : _logger(std::make_shared<RType::Common::Log::Log>("server", "server.log",
                                                              logLevel,
                                                              std::ios_base::trunc))) : _instance(nullptr), _dll(nullptr) {
            }

            /**
             * Change the current loaded library to the new one specified by the parameter.
             * If there was already a library loaded, it closes it before loading the new one.
             * @param DLLPath : The new library's path.
             * @throw LibraryLoader::Exceptions::InvalidSO
             * @throw LibraryLoader::Exceptions::InvalidEntryPoint
             */
            void changeLibrary(const std::string &DLLPath) {
                if (this->_dll != nullptr)
                    dlclose(this->_dll);
                this->loadSo(DLLPath);
            }

            /**
             * The destructor closes the current loaded library if there is one
             */
             LibraryLoader() {
                if (this->_dll != nullptr)
                    dlclose(this->_dll);
            }

            /**
             * Overloading the `->` operator to access to the members functions of the T type.
             * @warning It leads to a crash if there is no instance loaded
             * @return The current instance loaded.
             */
            T *operator->() {
                if (this->_instance == nullptr)
                    this->_logger->Error(" LibraryLoader] The instance is null, you might not want to use that");
                return (this->_instance);
            }

            /**
             * Get the current instance loaded
             * @return The current instance
             */
            T *getInstance() {
                return (this->_instance);
            }

            /**
             * Get the library's path loaded
             * @return A string to the library's path
             */
            std::string getLibPath() {
                return (this->_libPath);
            }

        private:
            typedef T *(*EntryPointPtrFunc)(void);
            T *_instance;
            void *_dll;
            std::string _libPath;
            RType::Common::Log::Log::shared_log_t _logger;


            void loadLibrary(const std::string &DLLPath) {
                EntryPointPtrFunc entryPointFunc;

                this->_dll = dlopen(DLLPath.c_str(), RTLD_LAZY);
                if (this->_dll == nullptr)
                    throw Exceptions::InvalidSO(DLLPath);
                entryPointFunc = (EntryPointPtrFunc) dlsym(this->_dll, ENTRY_POINT_NAME);
                if (entryPointFunc == nullptr)
                    throw Exceptions::InvalidEntryPoint(DLLPath);
                this->_instance = entryPointFunc();
                this->_libPath = DLLPath;
            }
    };
}

#endif //OOP_ARCADE DynamicLoader_HPP_