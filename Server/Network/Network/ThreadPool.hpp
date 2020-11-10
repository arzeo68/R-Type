/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Simple thread pool implementation
*/

#ifndef RTYPE_THREADPOOL_HPP
#define RTYPE_THREADPOOL_HPP

#include <thread>
#include <list>
#include <functional>

namespace RType::Network {
    /**
     * A pool of threads with the same core function.
     */
    class ThreadPool {
        public:
        /**
         * Create a pool of thread without starting them.
         * @param number of threads
         */
        explicit ThreadPool(uint32_t number) : _number(number) {}
        ThreadPool() = delete;
        ~ThreadPool() {
            std::for_each(this->_thread_pool.begin(), this->_thread_pool.end(), [] (std::thread& t) {
                if (t.joinable())
                    t.join();
                else // TODO: Add logger
                    printf("[Thread pool] %p is not joinable\n", &t);
            });
        }
        ThreadPool(ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;

        /**
         * Set the function to all thread and start them
         * @param fn Function's body
         * @param args Function's arguments
         */
        template<class func, typename... variadic>
        void run(func&& fn, variadic&&... args) {
            for (uint32_t i = 0; i < this->_number; ++i)
                this->_thread_pool.emplace_back(fn,
                                                std::forward<variadic>(args)...);
        }

        private:
        std::list<std::thread> _thread_pool;
        uint32_t _number;
    };
}


#endif //RTYPE_THREADPOOL_HPP
