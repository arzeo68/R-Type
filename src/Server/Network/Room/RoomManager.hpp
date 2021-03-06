/*
** EPITECH PROJECT, 2020
** RType
** File description:
** RoomManager class implementation
*/

#ifndef SRC_RTYPE_ROOMMANAGER_HPP_
#define SRC_RTYPE_ROOMMANAGER_HPP_

#include <list>
#include <algorithm>
#include <iostream>
#include <mutex>
#include "Common/Log.hpp"
#include "Room.hpp"

namespace RType::Network::Room {
    /**
     * A class to manage rooms. See Room for further information.
     */
    template<typename UDPSocket, typename TCPSocket>
    class RoomManager {
        public:
        RoomManager() = delete;
        RoomManager(const Common::Log::Log::shared_log_t& logger): _logger(logger) {}
        ~RoomManager() = default;
        RoomManager(const RoomManager&) = delete;
        using room_sptr = std::shared_ptr<Room<UDPSocket, TCPSocket>>;
        using participant_sptr = typename Room<UDPSocket, TCPSocket>::room_user_sptr;
        using participant_cptr = typename Room<UDPSocket, TCPSocket>::room_user_cptr;

        /**
         * Add an user to a room that isn't full or create a new room.
         * @param p A shared pointer to the client (aka AClient<...>)
         * See add_user from Room to further information.
         */
        void add_user(const participant_sptr& p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            auto r = std::find_if(this->_rooms.begin(), this->_rooms.end(),
                                  [&](room_sptr& room) {
                                      return (!room->is_full()  && !room->is_game_running());
                                  });
            if (r == std::end(this->_rooms)) {
                this->_rooms.emplace_back(
                    std::make_shared<Room<UDPSocket, TCPSocket>>
                        (this->_logger->shared_from_this(), p));
            } else
                (*r)->add_user(p);
        }
        /**
         * Remove an user from his room. If the user is the last one from the room,
         * the room is destroyed.
         * @param p A raw constant pointer to a constant client (example: const int* const)
         * @return true if the client has been removed
         * @return false if the client cannot be removed. The client hasn't been found in the room
         */
        bool remove_user(const participant_cptr p) {
            std::lock_guard<std::mutex> l(this->_mutex);
            auto it = std::find_if(this->_rooms.begin(), this->_rooms.end(),
                                   [p](room_sptr& room) {
                                       return (room->has_participant(p));
                                   });
            if (it == std::end(this->_rooms))
                this->_logger->Error("Cannot find user '", p, "' in any room");
            else {
                (*it)->remove_user_from_ptr(p);
                if ((*it)->is_empty())
                    this->_rooms.erase(it);
            }
            return (it != std::end(this->_rooms));
        }

        /**
         * Display all rooms with their number of users in it and the currently room state.
         */
        void display_rooms() {
            std::lock_guard<std::mutex> l(this->_mutex);
            if (this->_rooms.empty())
                this->_logger->Info("There is no room at the moment.");
            else {
                std::for_each(this->_rooms.begin(), this->_rooms.end(), [&](room_sptr &r) {
                    switch (r->get_game_state()) {
                        case GameState_e::PENDING:
                            this->_logger->Info("Room ", r, " with ", r->count_users(), " users connected on the room. The room is waiting for more users.");
                            break;
                        case GameState_e::RUNNING:
                            this->_logger->Info("Room ", r, " with ", r->count_users(), " users connected on the room. The game is currently running.");
                            break;
                        case GameState_e::EXITING:
                            this->_logger->Info("Room ", r, " with ", r->count_users(), " users connected on the room. The room is exiting.");
                            break;
                    }
                });
            }
        }

        private:
        Common::Log::Log::shared_log_t _logger;
        std::list<room_sptr> _rooms;
        std::mutex _mutex;
    };
}
#endif
