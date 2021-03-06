/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Simple logger.
*/

#include <vector>
#include "Log.hpp"

RType::Common::Log::Log::Log(const std::string& title, const std::string& path,
                             uint8_t logLevel, std::ios_base::openmode openMode)
    :
    _title(title),
    _path(path),
    _file(path, openMode),
    _level(static_cast<LogLevel_e>(logLevel)) {
    if (!this->_file.is_open())
        throw InvalidPath(path);
}

RType::Common::Log::Log::Log(const RType::Common::Log::Log& log) : Log(
    log._title, log._path, log._level, log._mode) {
}

RType::Common::Log::InvalidPath::InvalidPath(const std::string& path) : _path(
    path) {
}

const char *RType::Common::Log::InvalidPath::what() const noexcept {
    static std::string message = "Invalid path: " + this->_path;
    return (message.c_str());
}
