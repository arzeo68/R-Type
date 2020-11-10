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
            printf("Worker %p created\n", this);
        };
        Worker(const std::function<bool()>& unlock,
               const std::function<bool()>& locker) :
            _unlock_condition(unlock),
            _cv(std::make_shared<std::condition_variable>()), _locker(locker) {
            printf("Worker %p created\n", this);
        };
        ~Worker() {
            if (!this->_thread.joinable())
                std::cerr << "[Worker - " << std::hex << this
                          << "] is not joinable" << std::endl;
            else {
                std::cout << "Waiting thread " << std::hex << this << " to join" << std::endl;
                this->_thread.join();
                std::cout << "Thread joined for worker " << std::hex << this << std::endl;
            }
        }

        void terminate() {
            this->_must_exit = true;
            this->_cv->notify_all();
        }

        void run(const std::function<void()>& work) {
            this->_thread = std::thread([&, work]() {
                do {
                    std::unique_lock<std::mutex> lock(this->_mutex);
                    this->_cv->wait(lock, [&] {
                        return (this->_unlock_condition() || this->_must_exit);
                    });
                    if (!this->_must_exit)
                        work();
                } while ((this->_locker && this->_locker.value()) && !this->_must_exit);
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
        bool _must_exit = false;
    };
}


#endif //RTYPE_WORKER_HPP
