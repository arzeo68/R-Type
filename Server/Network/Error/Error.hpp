/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_NETWORK_ERROR
#define SRC_NETWORK_ERROR

#include <exception>
#include <string>
#include <utility>

namespace RType::Network {
    template<typename T>
    class Error : std::exception {
        public:
        explicit Error(T err, std::string message) : _message(
            std::move(message)) {
        }
        const char *what() const noexcept override {
            return (_message.c_str());
        }

        private:
        T _error;
        std::string _message;
    };
}

#endif
