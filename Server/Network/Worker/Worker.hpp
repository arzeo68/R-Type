/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef RTYPE_WORKER_HPP
#define RTYPE_WORKER_HPP

#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <optional>
#include <functional>

namespace RType::Network {
    class Worker {
        public:
        Worker(const std::function<bool()>& unlock) :
            _unlock_condition(unlock),
            _cv(std::make_shared<std::condition_variable>()) {
        };
        Worker(const std::function<bool()>& unlock,
               const std::function<bool()>& locker) :
            _unlock_condition(unlock),
            _cv(std::make_shared<std::condition_variable>()), _locker(locker) {
        };
        ~Worker() {
            if (!this->_thread.joinable())
                std::cerr << "[Worker - " << std::hex << this
                          << "] is not joinable" << std::endl;
            else
                this->_thread.join();
        }

        void run(const std::function<void()>& work) {
            this->_thread = std::thread([&, work]() {
                //printf("Runing worker: %p\n", this);
                do {
                    std::unique_lock<std::mutex> lock(this->_mutex);
                    this->_cv->wait(lock, [&] {
                        return (this->_unlock_condition());
                    });
                    //printf("[W: %p] Waking up...\n", this);
                    work();
                    //printf("[W: %p] Work done...\n", this);
                } while (this->_locker && this->_locker.value());
            });
        }

        std::shared_ptr<std::condition_variable> share_cv_from_this() {
            return (this->_cv);
        }

        private:
        std::function<bool()> _unlock_condition;
        std::shared_ptr<std::condition_variable> _cv;
        std::thread _thread;
        std::mutex _mutex;
        std::optional<std::function<bool()>> _locker;
    };
}


#endif //RTYPE_WORKER_HPP
