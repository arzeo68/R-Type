/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef RTYPE_WORKERWORKER_HPP_
#define RTYPE_WORKERWORKER_HPP_

#include "Server/Network/Network/ANetwork.hpp"
#include "Server/Network/Network/Router.hpp"
#include "ThreadSafeQueue.hpp"

namespace RType::Network {
    template<typename Client>
    class Worker {
        public:
        Worker() = delete;
        void delete_pending_client() {
            if (this->_pending_client.empty())
                return;

        }

        private:
        ThreadSafeQueue<Client*> _pending_client;
        ThreadSafeQueue<Client*> _notifications;
    };
}

#endif
