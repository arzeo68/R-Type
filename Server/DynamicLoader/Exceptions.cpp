/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Main file for lib leading exceptions
*/

#include "SoLoader.hpp"
#include "Exceptions.hpp"


SoLoader::Exceptions::InvalidSO::InvalidSO(const std::string &DLLPath) noexcept {
    this->_dllName = DLLPath;
}

const char *SoLoader::Exceptions::InvalidSO::what() const noexcept {
    static std::string message =
        "SO file \"" + this->_dllName + "\" is invalid. Either the file cannot be open, "
        "either it's not a shared library or this library is not compatible with the program."
        + "\nAdditional information: ";
    auto err = dlerror();
    if (err != nullptr)
        message.append(err);
    else
        message.append("None");
    return (message.c_str());
}

SoLoader::Exceptions::InvalidEntryPoint::InvalidEntryPoint(const std::string &DLLPath) noexcept {
    this->_dllName = DLLPath;
}

const char *SoLoader::Exceptions::InvalidEntryPoint::what() const noexcept {

    static std::string message =
        "SO file '" + this->_dllName + "' doesn't have the entry point named: "
        + std::string(SoLoader<void>::ENTRY_POINT_NAME) + "\nAdditional information: ";
    auto err = dlerror();
    if (err != nullptr)
        message.append(err);
    else
        message.append("None");
    return (message.c_str());
}
