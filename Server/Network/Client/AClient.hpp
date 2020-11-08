/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ACLIENT_HPP_
#define SRC_RTYPE_ACLIENT_HPP_

#include <memory>

namespace RType::Network {
    template<typename UDPSocket, typename TCPSocket>
    class AClient {
        public:
        virtual ~AClient() = default;

        /**
         *
         * @return
         */
        std::shared_ptr<UDPSocket> get_udpsocket() {
            return (this->_udpsocket);
        }

        /**
         *
         * @return
         */
        std::shared_ptr<TCPSocket> get_tcpsocket() {
            return (this->_tcpsocket);
        }

        virtual void read() = 0;

        void check_for_closed_socket() {
            std::unique_lock<std::mutex> lock(this->_mutex);
            while (!this->_tcpsocket)
                this->_socket_closed.wait(lock);

        }

        protected:
        std::condition_variable _socket_closed;
        std::thread _thread;
        std::mutex _mutex;
        std::shared_ptr<UDPSocket> _udpsocket;
        std::shared_ptr<TCPSocket> _tcpsocket;
    };

    template<typename Client, typename E>
    class RemoveClient : public std::exception {
        public:
        RemoveClient(Client* client, const E& err) : _error(err), _client(client) {}
        RemoveClient() = delete;

        const char *what() const noexcept override {
            return ("An error occurred in a socket - You might use a build-in function "
                    "to retrieve the error message instead of using what() from this class.");
        }
        [[maybe_unused]] Client* get_client() const {
            return (this->_client);
        }
        [[maybe_unused]] Client* get_client() {
            return (this->_client);
        }
        // [[maybe_unused]] E get() requires std::is_default_constructible_v<E> {
        [[maybe_unused]] E get()  {
            return (this->_error);
        }
        // [[maybe_unused]] E get() const requires std::is_default_constructible_v<E> {
        [[maybe_unused]] E get() const {
            return (this->_error);
        }

        private:
        E _error;
        Client* _client;
    };
}
#endif
