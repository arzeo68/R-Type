/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Worker class implementation
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
    /**
     * A worker is a thread that will do one job one or multiple time.
     */
    class Worker {
        public:
        Worker() = delete;
        /**
         * Create the thread without running it and setting internal variable
         * @param unlock A function which determine if a thread must be keep awake and executes his task
         * - The function MUST returns TRUE to unlock the thread
         * - If the function returns FALSE, the thread fall back to sleep
         * @warning The function must have the prototype bool (void).
         */
        Worker(const std::function<bool()>& unlock) :
            _unlock_condition(unlock),
            _cv(std::make_shared<std::condition_variable>()) {
        };
        /**
         * Create the thread without running it and setting internal variable
         * @param unlock See above
         * @param locker A function used to repeat the thread's task until the function returns false
         * - The function MUST returns TRUE to stop the repeating task
         * - The thread must be awake and the function @link{unlock} must have returned true
         * @warning The function must have the prototype bool (void).
         */
        Worker(const std::function<bool()>& unlock,
               const std::function<bool()>& locker) :
            _unlock_condition(unlock),
            _cv(std::make_shared<std::condition_variable>()), _locker(locker) {
        };
        /**
         * Wait for the thread to join and terminate
         */
        ~Worker() {
            if (!this->_thread.joinable())
                std::cerr << "[Worker - " << std::hex << this
                          << "] is not joinable" << std::endl;
            else {
                this->_thread.join();
            }
        }

        /**
         * Terminate the worker by notifying the thread to wake up and exit without
         * executing any task.
         */
        void terminate() {
            this->_must_exit = true;
            this->_cv->notify_all();
        }

        /**
         * Run the worker and attributing a task/work to do. The occurrence of the
         * task depends of if the a locker has been set in the constructor or not.
         * The worker goes sleep before doing the ask and basically wait for the
         * unlock condition.
         * @param work The work to do
         */
        void run(const std::function<void()>& work) {
            this->_thread = std::thread([&, work]() {
                do {
                    std::unique_lock<std::mutex> lock(this->_mutex);
                    this->_cv->wait(lock, [&] {
                        return (this->_must_exit || this->_unlock_condition());
                    });
                    if (!this->_must_exit)
                        work();
                } while (!this->_must_exit &&
                    (this->_locker && this->_locker.value()));
            });
        }

        /**
         * The main difference between @run and this function is that, this function
         * never sleep and will quit when the unlock condition function returns true.
         * @warning It's strongly advice to set a timer that make the function work sleep to avoid your CPU burn out
         * @param work The work to do
         */
        void run_awake(const std::function<void()>& work) {
            this->_thread = std::thread([&, work]() {
                do {
                    std::unique_lock<std::mutex> lock(this->_mutex);
                    if (!this->_must_exit)
                        work();
                } while (!this->_must_exit && !this->_unlock_condition());
            });
        }

        /**
         * Share the condition variable by using a shared pointer.
         * The condition variable may be used to notify the thread to wake up.
         * The logic behind is similar to std::enable_shared_from_this.
         * @return A shared pointer containing an instance of the condition variable.
         */
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
