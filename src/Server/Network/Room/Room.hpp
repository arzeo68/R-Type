/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Room class implementation
*/

#ifndef SRC_RTYPE_ROOM_HPP_
#define SRC_RTYPE_ROOM_HPP_

#include <ratio>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>
#include <thread>
#include "Common/Log.hpp"
#include "Common/ECS/World.hpp"
#include "Server/Network/Client/AClient.hpp"

#include "Common/unique_id.hpp"

#include "Common/Component/Transform.hpp"
#include "Common/Component/Movement.hpp"
#include "Common/Component/Hitbox.hpp"
#include "Common/Component/InputQueue.hpp"
#include "Common/Component/OutputQueue.hpp"
#include "Common/Component/PlayerID.hpp"
#include "Common/Component/UniqueID.hpp"

#include "Common/Systems/TransformSystem.hpp"
#include "Common/Systems/PhysicSystem.hpp"
#include "Common/Systems/NetworkSystem.hpp"
#include "Common/Systems/MovementUpdateSystem.hpp"

namespace RType::Network::Room {
    /**
     * The number of participant per room
     */
    const static constexpr uint16_t MAX_PARTICIPANT = 2;

    typedef uint16_t GameState_t;
    enum class GameState_e : GameState_t {
        PENDING,
        RUNNING,
        EXITING
    };
    [[maybe_unused]] static std::ostream& operator<<(std::ostream& os, const GameState_e& gs) {
        os << std::to_string(static_cast<GameState_t>(gs));
        return (os);
    }

    /**
     * The class create a room of AClient.
     * @tparam UDPSocket for the AClient
     * @tparam TCPSocket for the AClient
     * - See AClient documentation for further details
     */
    template<typename UDPSocket, typename TCPSocket>
    class Room:
        public std::enable_shared_from_this<Room<UDPSocket, TCPSocket>> {
        public:
        using room_user = AClient<UDPSocket, TCPSocket>;
        using room_user_sptr = std::shared_ptr<room_user>;
        using room_user_cptr = room_user *const;

        Room() = delete;
        /**
         * Basic constructor with a logger. ECS is initialized here.
         * @param logger A simple logger. You must pass a shared instance of an another logger
         */
        Room(const Common::Log::Log::shared_log_t& logger):
            _world(std::make_shared<ECS::World>()),
            _logger(logger),
            _worker_game_loop([&] () {
                return (this->_state != GameState_e::RUNNING);
            }) {
            this->_world->initialize();
        };
        /**
         * Allow to create a room with a set of predefined clients in it. ECS is initialized here.
         * @param logger A simple logger. You must pass a shared instance of an another logger
         * @param clients Vector of clients
         */
        Room(const Common::Log::Log::shared_log_t& logger,
             const room_user_sptr& user):
            _world(std::make_shared<ECS::World>()),
            _logger(logger),
            _worker_game_loop([&] () {
                return (this->_state != GameState_e::RUNNING);
            }) {
            this->_world->initialize();
            this->add_user(user);
        }
        /**
         * The destructor set the game state on "exiting" and terminate the associate
         * worker.
         */
        ~Room() {
            std::lock_guard<std::mutex> l(this->_mutex);
            this->_state = GameState_e::EXITING;
            this->_worker_game_loop.terminate();
        }
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
                              p->get_udpsocket_read->write(m);
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
            this->_logger->Debug("Number of user: ", this->_users.size());
            if (this->_users.size() >= MAX_PARTICIPANT)
                this->launch_game();
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

        /**
         * Let know if the current game of the room is on running state or exiting,
         * which is, considered as running.
         * @return true if the game is running or exiting
         * @return false if the game is not running or exiting
         */
        bool is_game_running() const {
            return (this->_state == GameState_e::EXITING || this->_state == GameState_e::RUNNING);
        }

        private:
        void init_ecs() {
            _netId_Generator = std::make_shared<UniqueIDGenerator>();

            this->_world->template registerComponent<Rtype::TransformComponent>();
            this->_world->template registerComponent<Rtype::HitboxComponent>();
            this->_world->template registerComponent<Rtype::MovementComponent>();
            this->_world->template registerComponent<Rtype::InputQueueComponent>();
            this->_world->template registerComponent<Rtype::OutputQueueComponent>();
            this->_world->template registerComponent<Rtype::PlayerID>();
            this->_world->template registerComponent<Rtype::UniqueID>();

            this->_world->template addSingletonComponents<Rtype::InputQueueComponent, Rtype::OutputQueueComponent>(
                Rtype::InputQueueComponent(),
                Rtype::OutputQueueComponent()
            );

            this->_world->template registerSystem<Rtype::MovementUpdateSystem>();
            this->_world->template setSystemSignature<Rtype::MovementUpdateSystem, Rtype::MovementComponent>();

            this->_world->template registerSystem<Rtype::TransformSystem>();
            this->_world->template setSystemSignature<Rtype::TransformSystem, Rtype::TransformComponent, Rtype::MovementComponent>();

            this->_world->template registerSystem<Rtype::PhysicSystem>();
            this->_world->template setSystemSignature<Rtype::PhysicSystem, Rtype::TransformComponent, Rtype::HitboxComponent>();

            this->_world->template registerSystem<Rtype::NetworkSystem>();
            this->_world->template setSystemSignature<Rtype::NetworkSystem, Rtype::UniqueID>();

            for (size_t i = 0; i < this->_users.size(); i += 1) {
                ECS::Entity e = this->_world->createEntity();

                this->_world->template addComponents<Rtype::TransformComponent, Rtype::MovementComponent, Rtype::PlayerID, Rtype::UniqueID>(
                    e,
                    Rtype::TransformComponent({0, 0}, 0, {1, 1}),
                    Rtype::MovementComponent({0, 0}, 0, std::bind(Rtype::PlayerUpdateMovement, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
                    Rtype::PlayerID(i),
                    Rtype::UniqueID(_netId_Generator->getID())
                );
                this->_users[i]->get_tcpsocket()->write({RType::Common::Network::g_MagicNumber, static_cast<int>(i)});
            }
        }

        void launch_game() {
            this->_logger->Debug("[Room ", this, "] Room completed, launching the game");
            this->init_ecs();
            this->_state = GameState_e::RUNNING;
            std::for_each(this->_users.begin(), this->_users.end(), [](room_user_sptr &u) {
                u->get_udpsocket_read()->read();
            });
            _start = std::chrono::high_resolution_clock::now();
            this->_worker_game_loop.run_awake([&] () {
                auto queue = this->_world->template getSingletonComponent<Rtype::InputQueueComponent>();
                auto oqueue = this->_world->template getSingletonComponent<Rtype::OutputQueueComponent>();
                for (int i = 0; i < _users.size(); i += 1) {
                    auto q = _users[i]->get_udpsocket_read()->get_queue();
                    while (!q->empty()) {
                        auto packet = q->pop();
                        queue.get()->InputQueueMap[packet.networkID].push_back(packet.command);
                    }
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float, std::milli> duration = end - _start;
                float res = duration.count();
                this->_world->template getSystem<Rtype::MovementUpdateSystem>()->update(res, this->_world);
                this->_world->template getSystem<Rtype::TransformSystem>()->update(res, this->_world);
                this->_world->template getSystem<Rtype::PhysicSystem>()->update(res, this->_world);
                this->_world->template getSystem<Rtype::NetworkSystem>()->update(res, this->_world);
                this->_world->template getSystem<Rtype::NetworkSystem>()->update(res, this->_world);
                for (size_t i = 0; i < _users.size(); ++i) {
                    for (auto& p : oqueue.get()->OutputQueue) {
                        _users[i]->get_udpsocket_write()->write(p);
                    }
                }
                oqueue.get()->OutputQueue.clear();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
                _start = end;
            });
        }

        std::shared_ptr<UniqueIDGenerator> _netId_Generator;
        std::chrono::high_resolution_clock::time_point _start;
        std::shared_ptr<ECS::World> _world;
        Common::Log::Log::shared_log_t _logger;
        Worker _worker_game_loop;
        GameState_e _state;
        std::mutex _mutex;
        std::vector<room_user_sptr> _users;
    };
}

#endif // SRC_RTYPE_ROOM_HPP_
