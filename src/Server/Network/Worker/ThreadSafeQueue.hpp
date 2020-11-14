/*
** EPITECH PROJECT, 2020
** RType
** File description:
** ThreadSafeQueue class implementation
*/

#ifndef RTYPE_THREADSAFEQUEUE_HPP
#define RTYPE_THREADSAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <functional>

namespace RType::Network {
    /**
     * Basic re-implementation of std::queue (FIFO queue)  in a thread safe manner.
     * @tparam T Type of data contained in the queue
     */
    template<typename T>
    class ThreadSafeQueue :
        public std::enable_shared_from_this<ThreadSafeQueue<T>> {
        public:
        ThreadSafeQueue() = default;
        ~ThreadSafeQueue() = default;

        /**
         * Add an element to the queue
         * @param element Element to add
         */
        void add(T element) {
            std::lock_guard<std::mutex> l(this->_mutex);
            this->_queue.push(element);
        }

        /**
         *
         * @return
         */
        auto end() {
            std::lock_guard<std::mutex> l(this->_mutex);
            return (std::end(this->_queue));
        }

        /**
         * Pop the last added element
         * @return An instance T of the popped element if the queue isn't empty
         * @return A "end" instance otherwise
         */
        T pop() {
            if (this->empty())
                return (this->end());
            std::lock_guard<std::mutex> l(this->_mutex);
            auto element = this->_queue.front();
            this->_queue.pop();
            return (element);
        }

        /**
         * Pop the last added element and pass it to a custom user defined function
         * @param function Function with the prototype: void (T)
         * @return true: if the element has been removed
         * @return false: if the element cannot be deleted
         */
        bool pop_with_effect(const std::function<void(T)>& function) {
            if (this->empty())
                return (false);
            std::lock_guard<std::mutex> l(this->_mutex);
            function(this->_queue.front());
            this->_queue.pop();
            return (true);
        }
        /**
         * Check if the queue is empty
         * @return true: if the queue is empty
         * @return false: if there is at least one element in the queue
         */
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
