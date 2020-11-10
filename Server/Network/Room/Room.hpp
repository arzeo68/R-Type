/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Room class implementation
*/

#ifndef SRC_RTYPE_ROOM_HPP_
#define SRC_RTYPE_ROOM_HPP_

#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>
#include <src/ECS/World.hpp>
#include "Server/Network/Client/AClient.hpp"

namespace RType::Network::Room {
    /**
     * The number of participant per room
     */
    const static constexpr uint16_t MAX_PARTICIPANT = 4;

    /**
     * The class create a room of AClient.
     * @tparam UDPSocket for the AClient
     * @tparam TCPSocket for the AClient
     * - See AClient documentation for further details
     */
    template<typename UDPSocket, typename TCPSocket>
    class Room
        :
            public std::enable_shared_from_this<Room<UDPSocket, TCPSocket>> {
        public:
        using room_user = AClient<UDPSocket, TCPSocket>;
        using room_user_sptr = std::shared_ptr<room_user>;
        using room_user_cptr = room_user *const;
        Room() = default;
        /**
         * Allow to create a room with a set of predefined clients in it
         * @param clients Vector of clients
         */
        Room(const std::vector<room_user_sptr>& clients) {
            this->_users = clients;
            _world->initialize();
        }
        ~Room() = default;
        Room(const Room&) = default;

        /**
         * Broadcast a package by using the TCP socket of a client
         * @param m The package to broadcast
         * @warning For now, everybody in a room get the message
         */
        void tcp_broadcast(const Common::Network::TCPPacket& m) {
            std::lock_guard<std::mutex> l(this->_mutex);
            std::for_each(this->_users.begin(),
                          this->_users.end(),
                          [m](room_user_sptr& p) {
                              p->get_tcpsocket->write(m);
                          });
        }
        /**
         * Broadcast a package by using the UDP socket of a client
         * @param m The package to broadcast
         * @warning For now, everybody in a room get the message
         */
        void udp_broadcast(const Common::Network::TCPPacket& m) {
            std::lock_guard<std::mutex> l(this->_mutex);
            std::for_each(this->_users.begin(),
                          this->_users.end(),
                          [m](room_user_sptr& p) {
                              p->get_udpsocket->write(m);
                          });
        }

        /**
         * Check if a room is full. Full means that there at least @MAX_PARTICIPANT in it
         * @return true if the room is full
         * @return false if the room contains vacant place
         */
        inline bool is_full() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_users.size() >= MAX_PARTICIPANT);
        }

        /**
         * Check if a room is empty/contains no client
         * @return true if the room is empty
         * @return false if the room has clients in it
         */
        inline bool is_empty() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_users.empty());
        }

        /**
         * Add a client to the room
         * @param p A shared pointer to the client (aka AClient<...>)
         */
        void add_user(const room_user_sptr& p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            this->_users.emplace_back(p);
        }
        /**
         * Remove a user from the room by using his pointer.
         * @param p A raw constant pointer to a constant client (example: const int* const)
         * @return true if the client has been removed
         * @return false if the client cannot be removed. The client hasn't been found in the room
         */
        bool remove_user_from_ptr(const room_user_cptr p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            auto k = std::find_if(this->_users.begin(),
                                  this->_users.end(),
                                  [p](room_user_sptr& p_ptr) {
                                      return (p_ptr.get() == p);
                                  });
            if (k == std::end(this->_users))
                std::cerr << "Cannot remove user " << std::hex << p
                          << std::endl;
            else
                this->_users.erase(k);
            return (k != std::end(this->_users));
        }

        /**
         * From a AClient<..> instance, check if it is in the room
         * @param p Constant AClient<...> instance to check
         * @return true if the client is in the room
         * @return false if the client isn't in the room
         */
        bool has_participant(const room_user& p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (
                std::find(this->_users.begin(), this->_users.end(), p) !=
                    std::end(this->_users));
        }
        /**
         * See has_participant function
         * @param p A raw constant pointer to a constant client (example: const int* const)
         * @return true if the client is in the room
         * @return false if the client isn't in the room
         */
        bool has_participant(const room_user_cptr p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            auto found = std::find_if(this->_users.begin(),
                                      this->_users.end(),
                                      [p](room_user_sptr& p_ptr) {
                                          return (p_ptr.get() == p);
                                      });
            return (found != std::end(this->_users));
        }

        private:
        std::shared_ptr<ECS::World> _world;
        std::mutex _mutex;
        std::vector<room_user_sptr> _users;
    };


}

#endif // SRC_RTYPE_ROOM_HPP_
