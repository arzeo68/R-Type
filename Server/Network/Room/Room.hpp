/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_RTYPE_ROOM_HPP_
#define SRC_RTYPE_ROOM_HPP_

#include <list>
#include <array>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <mutex>
#include "Server/Network/Client/AClient.hpp"

namespace RType::Network::Room {
    const static constexpr uint16_t MAX_PARTICIPANT = 4;
    template<typename UDPSocket, typename TCPSocket>
    class Room : public std::enable_shared_from_this<Room<UDPSocket, TCPSocket>> {
        public:
        using room_user = AClient<UDPSocket, TCPSocket>;
        using room_user_sptr = std::shared_ptr<room_user>;
        using room_user_ptr = room_user*;
        Room() = default;
        Room(const std::vector<room_user_sptr>& participants) {
            this->_users = participants;
        }
        ~Room() = default;
        Room(const Room&) = default;

        void tcp_broadcast(const Common::Network::TCPPacket& m){
            std::lock_guard<std::mutex> l(this->_mutex);
            std::for_each(this->_users.begin(), this->_users.end(), [m](room_user_sptr& p) {
                p->get_tcpsocket->write(m);
            });
        }
        void udp_broadcast(const Common::Network::TCPPacket& m) {
            std::lock_guard<std::mutex> l(this->_mutex);
            std::for_each(this->_users.begin(), this->_users.end(), [m](room_user_sptr& p) {
                p->get_udpsocket->write(m);
            });
        }
        inline bool is_full() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_users.size() >= MAX_PARTICIPANT);
        }
        inline bool is_empty() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_users.empty());
        }
        void add_user(const room_user_sptr& p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            this->_users.emplace_back(p);
        }
        bool remove_user_from_ptr(room_user_ptr p) {
            std::lock_guard<std::mutex> l (this->_mutex);
            auto k = std::find_if(this->_users.begin(), this->_users.end(), [p](room_user_sptr& p_ptr) {
                return (p_ptr.get() == p);
            });
            if (k == std::end(this->_users))
                std::cerr << "Cannot remove user " << std::hex << p << std::endl;
            else
                this->_users.erase(k);
            return (k != std::end(this->_users));
        }
        bool has_participant(const room_user& p) {
            std::lock_guard<std::mutex> l (this->_mutex);
            return (std::find(this->_users.begin(), this->_users.end(), p) != std::end(this->_users));
        }
        bool has_participant(const room_user_ptr p) {
            std::lock_guard<std::mutex> l (this->_mutex);
            auto found = std::find_if(this->_users.begin(), this->_users.end(), [p](room_user_sptr& p_ptr) {
                return (p_ptr.get() == p);
            });
            return (found != std::end(this->_users));
        }

        private:
        std::mutex _mutex;
        std::vector<room_user_sptr> _users;
    };




}

#endif // SRC_RTYPE_ROOM_HPP_
