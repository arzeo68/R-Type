/*
** EPITECH PROJECT, 2020
** RType
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef RTYPE_THREADSAFEQUEUE_HPP
#define RTYPE_THREADSAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <functional>

namespace RType::Network {
    template<typename T>
    class ThreadSafeQueue
        :
            public std::enable_shared_from_this<ThreadSafeQueue<T>> {
        public:
        ThreadSafeQueue() = default;
        ~ThreadSafeQueue() = default;

        void add(T element) {
            std::lock_guard<std::mutex> l(this->_mutex);
            this->_queue.push(element);
        }
        bool pop_with_effect(const std::function<void(T)>& function) {
            std::lock_guard<std::mutex> l(this->_mutex);
            if (this->_queue.empty())
                return (false);
            function(this->_queue.front());
            this->_queue.pop();
            return (true);
        }
        bool empty() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (this->_queue.empty());
        }

        private:
        std::queue<T> _queue;
        std::mutex _mutex;
    };
}


#endif //RTYPE_THREADSAFEQUEUE_HPP
