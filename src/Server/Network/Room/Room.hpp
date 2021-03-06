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
#include "Server/EntityLib/ConfigFile.hpp"

#include "Common/unique_id.hpp"

#include "Common/Component/Transform.hpp"
#include "Common/Component/Movement.hpp"
#include "Common/Component/Hitbox.hpp"
#include "Common/Component/InputQueue.hpp"
#include "Common/Component/OutputQueue.hpp"
#include "Common/Component/PlayerID.hpp"
#include "Common/Component/UniqueID.hpp"
#include "Common/Component/Tag.hpp"

#include "Common/Systems/TransformSystem.hpp"
#include "Common/Systems/PhysicSystem.hpp"
#include "Common/Systems/NetworkSystem.hpp"
#include "Common/Systems/MovementUpdateSystem.hpp"

namespace RType::Network::Room {

    static ECS::NetworkPacket getPlayerCreationPacket(size_t i)
    {
        switch (i) {
            case 0:
                return {static_cast<int>(i), 0, 0.f, 0.f, {8, 175, 27, 12}};
            case 1:
                return {static_cast<int>(i), 0, 0.f, 0.f, {8, 148, 27, 12}};
            case 2:
                return {static_cast<int>(i), 0, 0.f, 0.f, {8, 101, 27, 12}};
            case 3:
                return {static_cast<int>(i), 0, 0.f, 0.f, {8, 126, 27, 12}};
        }
        return {0, 0, 0, 0, {0, 0, 0, 0}};
    }


    /**
     * The number of participant per room
     */
    const static constexpr uint16_t MAX_PARTICIPANT = 1;

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
         * The function count the number of user in the room and return it
         * @return The number of users in the room
         */
        inline std::size_t count_users() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_users.size());
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
        inline bool is_game_running() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_state == GameState_e::EXITING || this->_state == GameState_e::RUNNING);
        }

        /**
         * Get the currently game state set by GameState_e
         * @return The current game state
         */
        GameState_e get_game_state() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_state);
        }

        private:
        void init_ecs() {
            _packetQueue = std::make_shared<ThreadSafeQueue<ECS::NetworkPacket>>();
            _netId_Generator = std::make_shared<UniqueIDGenerator>();
            _libs = std::make_shared<std::vector<std::shared_ptr<DynamicLoader<IEntityFactory>>>>();
            _config = std::make_shared<ConfigFile>("../../ressources/config.conf", _libs);
            _time = std::make_shared<float>(0.f);

            this->_world->template registerComponent<RType::TransformComponent>();
            this->_world->template registerComponent<RType::HitboxComponent>();
            this->_world->template registerComponent<RType::MovementComponent>();
            this->_world->template registerComponent<RType::InputQueueComponent>();
            this->_world->template registerComponent<RType::OutputQueueComponent>();
            this->_world->template registerComponent<RType::PlayerID>();
            this->_world->template registerComponent<RType::UniqueID>();
            this->_world->template registerComponent<RType::TagComponent>();

            this->_world->template addSingletonComponents<RType::InputQueueComponent, RType::OutputQueueComponent>(
                RType::InputQueueComponent(),
                RType::OutputQueueComponent()
            );

            this->_world->template registerSystem<RType::MovementUpdateSystem>();
            this->_world->template setSystemSignature<RType::MovementUpdateSystem, RType::MovementComponent>();

            this->_world->template registerSystem<RType::TransformSystem>();
            this->_world->template setSystemSignature<RType::TransformSystem, RType::TransformComponent, RType::MovementComponent>();

            this->_world->template registerSystem<RType::PhysicSystem>();
            this->_world->template setSystemSignature<RType::PhysicSystem, RType::TransformComponent, RType::HitboxComponent>();

            this->_world->template registerSystem<RType::NetworkSystem>();
            this->_world->template setSystemSignature<RType::NetworkSystem, RType::UniqueID>();

            for (size_t i = 0; i < this->_users.size(); i += 1) {
                ECS::Entity e = this->_world->createEntity();

                this->_world->template addComponents<RType::TransformComponent, RType::MovementComponent, RType::HitboxComponent, RType::PlayerID, RType::UniqueID, RType::TagComponent>(
                    e,
                    RType::TransformComponent({-(1920 / 2) + 100, static_cast<float>(i) * 100.f}, 0, {3, 3}),
                    RType::MovementComponent({0, 0}, 0, std::bind(RType::PlayerUpdateMovement, _netId_Generator, _packetQueue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)),
                    RType::HitboxComponent({0, 0, 27, 12}, std::bind(RType::PlayerCollisionUpdateRoutine, _packetQueue, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)),
                    RType::PlayerID(i),
                    RType::UniqueID(_netId_Generator->getID()),
                    RType::TagComponent("Player")
                );
                this->_users[i]->get_tcpsocket()->write({RType::Common::Network::g_MagicNumber, static_cast<int>(i)});
            }
            for (size_t i = 0; i < this->_users.size(); i += 1) {
                ECS::NetworkPacket p = getPlayerCreationPacket(i);
                for (size_t j = 0; j < this->_users.size(); j += 1)
                    this->_users[j]->get_udpsocket_write()->write(p);
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
                this->_world->clearDeferList();
                auto queue = this->_world->template getSingletonComponent<RType::InputQueueComponent>();
                auto oqueue = this->_world->template getSingletonComponent<RType::OutputQueueComponent>();
                for (std::size_t i = 0; i < _users.size(); i += 1) {
                    auto q = _users[i]->get_udpsocket_read()->get_queue();
                    while (!q->empty()) {
                        auto packet = q->pop();
                        queue.get()->InputQueueMap[packet.networkID].push_back(packet.command);
                    }
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float, std::milli> duration = end - _start;
                float res = duration.count();
                (*this->_time) += res;
                this->_world->template getSystem<RType::MovementUpdateSystem>()->update(res, this->_world);
                this->_world->template getSystem<RType::TransformSystem>()->update(res, this->_world);
                this->_world->template getSystem<RType::PhysicSystem>()->update(res, this->_world);
                this->_world->template getSystem<RType::NetworkSystem>()->update(res, this->_world);
                for (size_t i = 0; i < _users.size(); ++i) {
                    for (auto& p : *oqueue.get()->OutputQueue) {
                        _users[i]->get_udpsocket_write()->write(p);
                    }
                }
                while (!_packetQueue->empty()) {
                    ECS::NetworkPacket tmp = _packetQueue->pop();
                    for (size_t i = 0; i < _users.size(); ++i)
                        _users[i]->get_udpsocket_write()->write(tmp);
                }
                oqueue.get()->OutputQueue->clear();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
                _start = end;
                if ((*this->_time) > 1000.f) {
                    ECS::NetworkPacket enp = (*this->_libs->at(rand() % (this->_libs->size())))->instanciate(this->_world, this->_netId_Generator, this->_packetQueue);
                    for (size_t i = 0; i < _users.size(); ++i) {
                        _users[i]->get_udpsocket_write()->write(enp);
                    }
                    (*this->_time) = 0.f;
                }
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
        std::shared_ptr<ThreadSafeQueue<ECS::NetworkPacket>> _packetQueue;
        std::shared_ptr<ConfigFile> _config;
        std::shared_ptr<std::vector<std::shared_ptr<DynamicLoader<IEntityFactory>>>> _libs;
        std::shared_ptr<float> _time;
    };
}

#endif // SRC_RTYPE_ROOM_HPP_
