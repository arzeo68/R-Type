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
#include "Client/AClient.hpp"

namespace RType::Network::Room {
    const static constexpr uint16_t MAX_PARTICIPANT = 4;
    template<typename UDPSocket, typename TCPSocket>
    class Room {
        public:
        using room_participant = AClient<UDPSocket, TCPSocket>;
        using room_participant_sptr = std::shared_ptr<room_participant>;
        using room_participant_ptr = room_participant*;
        Room() = default;
        Room(const std::vector<room_participant_sptr> &participants) {
            this->_participant = participants;
        }
        ~Room() = default;
        Room(const Room&) = default;

        void broadcast(const std::string& m) {
            for (auto &p: this->_participant)
                m.end();
                // Write
        }
        bool is_full() {
            std::unique_lock<std::mutex> l(this->_mutex);
            return (this->_participant.size() == MAX_PARTICIPANT);
        }
        void add_participant(const room_participant_sptr& p) {
            std::unique_lock<std::mutex> l(this->_mutex);
            if (this->is_full())
                std::cerr << "Trying to add a client to a room which is already full" << std::endl;
            else
                this->_participant.emplace_back(p);
        }
        bool remove_participant_from_ptr(const room_participant_ptr p) {
            auto k = std::find_if(this->_participant.begin(), this->_participant.end(), [p](room_participant_sptr& p_ptr) {
                return (*p_ptr == p);
            });
            if (k == std::end(this->_participant))
                std::cerr << "Cannot remove participant " << std::hex << p << std::endl;
            else
                this->_participant.erase(k);
            return (k != std::end(this->_participant));
        }
        bool has_participant(const room_participant& p) {
            std::unique_lock<std::mutex> l (this->_mutex);
            return (std::find(this->_participant.begin(), this->_participant.end(), p) != std::end(this->_participant));
        }

        private:
        std::mutex _mutex;
        std::vector<room_participant_sptr> _participant;
    };

    template<typename UDPSocket, typename TCPSocket>
    class RoomManager {
        public:
        RoomManager() = default;
        ~RoomManager() = default;
        RoomManager(const RoomManager&) = delete;
        using participant_sptr = typename Room<UDPSocket, TCPSocket>::room_participant_ptr;

        void add_participant(const participant_sptr& p) {
            std::unique_lock<std::mutex> l (this->_mutex);
            auto r = std::find_if(this->_rooms.begin(), this->_rooms.end(), [&] (Room<UDPSocket, TCPSocket>& room) {
                return (room.is_full());
            });
            if (r == std::end(this->_rooms))
                this->_rooms.emplace_back(std::vector<participant_sptr> {p});
            else
                r->add_participant(p);
        }
        bool remove_participant(const participant_sptr& p) {
            std::unique_lock<std::mutex> l (this->_mutex);
            auto it = std::find_if(this->_rooms.begin(), this->_rooms.end(), [p](Room<UDPSocket, TCPSocket>& room) {
                return (room.has_participant(*p));
            });
            if (it == std::end(this->_rooms))
                std::cerr << "Cannot remove participant, doesn't exists" << std::endl;
            return (it != std::end(this->_rooms));
        }
        bool remove_participant(const Room<UDPSocket, TCPSocket>* p) {
            std::unique_lock<std::mutex> l (this->_mutex);
            auto it = std::find_if(this->_rooms.begin(), this->_rooms.end(), [p](Room<UDPSocket, TCPSocket>& room) {
                return (room.has_participant(p));
            });
            if (it == std::end(this->_rooms))
                std::cerr << "Cannot remove participant, doesn't exists" << std::endl;
            else
                it->remove_participant_from_ptr(p);
            return (it != std::end(this->_rooms));
        }

        private:
        std::list<Room<UDPSocket, TCPSocket>> _rooms;
        std::mutex _mutex;
    };
}

#endif // SRC_RTYPE_ROOM_HPP_
