/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef RTYPE_THREADPOOL_HPP
#define RTYPE_THREADPOOL_HPP

#include <thread>
#include <vector>

namespace RType::Network {
    class ThreadPool {
        public:
        explicit ThreadPool(uint32_t number) : _number(number) {
        }
        ThreadPool() = delete;
        ~ThreadPool() {
            for (auto& i: this->_threadPool)
                if (i.joinable()) {
                    //printf("Waiting for %p to join\n", &i);
                    i.join();
                    //printf("Thread %p joined\n", &i);
                } else
                    printf("[Thread pool] %p is not joinable\n", &i);
        }
        ThreadPool(ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;

        template<class func, typename ...variadic>
        void run(func&& fn, variadic&& ... args) {
            for (uint32_t i = 0; i < this->_number; ++i)
                this->_threadPool.emplace_back(fn,
                                               std::forward<variadic>(args)...);
        }

        private:
        std::vector<std::thread> _threadPool;
        uint32_t _number;
    };
}


#endif //RTYPE_THREADPOOL_HPP
