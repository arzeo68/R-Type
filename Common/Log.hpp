/*
** EPITECH PROJECT, 2020
** RType
** File description:
** Simple logger.
*/

#ifndef RType_LOG_HPP
#define RType_LOG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <ctime>
#include <iomanip>
#include <mutex>

namespace RType::Common::Log {
    enum LogLevel_e : uint16_t {
        LOG_DEBUG_E = 0b0001u,
        LOG_INFO_E = 0b0010u,
        LOG_WARN_E = 0b01000u,
        LOG_ERROR_E = 0b10000u,
    };

    /**
     * Log is a logger with different level:
     *  - DEBUG
     *  - INFO
     *  - WARNING
     *  - ERROR
     * It write the logs inside a file and in the C++ standard output with a timestamp
     */
    class Log : public std::enable_shared_from_this<Log> {
        public:
        using shared_log_t = std::shared_ptr<Log>;
        /**
         * Open or create the log file
         * @param title The main title of the log
         * @param path Path to the log's file
         * @param logLevel The log level. You can use bitwise operator on it with the modes above, default: all logs level
         * @param openMode Open mode for the log's file, default: append s text to the end
         * @throws InvalidPath
         */
        explicit Log(const std::string& title, const std::string& path,
                     uint8_t logLevel = LOG_DEBUG_E | LOG_INFO_E | LOG_WARN_E |
                         LOG_ERROR_E,
                     std::ios_base::openmode openMode = std::ios::app);

        Log(const Log& log);
        ~Log() = default;

        static const constexpr uint8_t g_AllLogLevel =
            LOG_DEBUG_E | LOG_INFO_E | LOG_WARN_E | LOG_ERROR_E;

        template<typename ...variadic>
        void Debug(variadic&& ... args) {
            return (this->Write(LOG_DEBUG_E, args...));
        }

        template<typename ...variadic>
        void Debug(variadic&& ... args) const {
            return (this->Write(LOG_DEBUG_E, args...));
        }

        template<typename ...variadic>
        void Warning(variadic&& ... args) {
            return (this->Write(LOG_WARN_E, args...));
        }
        template<typename ...variadic>
        void Warning(variadic&& ... args) const {
            return (this->Write(LOG_WARN_E, args...));
        }

        template<typename ...variadic>
        void Error(variadic&& ... args) {
            return (this->Write(LOG_ERROR_E, args...));
        }
        template<typename ...variadic>
        void Error(variadic&& ... args) const {
            return (this->Write(LOG_ERROR_E, args...));
        }

        template<typename ...variadic>
        void Info(variadic&& ... args) {
            return (this->Write(LOG_INFO_E, args...));
        }
        template<typename ...variadic>
        void Info(variadic&& ... args) const {
            return (this->Write(LOG_INFO_E, args...));
        }


        private:
        static std::string GetCurrentTime() {
            auto timer = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());
            std::tm *bt = std::localtime(&timer);
            std::ostringstream oss;
            oss << std::put_time(bt, "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }

        template<typename ...variadic>
        void Write(LogLevel_e level, variadic&& ... args) {
            if ((level & this->_level) == 0)
                return;
            std::unique_lock<std::mutex> lock(this->_mutex);
            std::string prefix("[" + Common::Log::Log::GetCurrentTime() + "/" +
                                   this->_title + "/" +
                                   _map.find(level)->second + "] ");
            std::cout << prefix;
            (std::cout << ... << args) << std::endl;
            this->_file << prefix;
            (this->_file << ... << args) << std::endl;
        }

        std::string _title;
        std::string _path;
        std::ios_base::openmode _mode;
        std::ofstream _file;
        LogLevel_e _level;
        std::mutex _mutex;
        const std::map<uint8_t, std::string> _map = {
            {LOG_DEBUG_E, "debug"},
            {LOG_INFO_E,  "info"},
            {LOG_WARN_E,  "warning"},
            {LOG_ERROR_E, "error"},
        };
    };

    class InvalidPath : std::exception {
        public:
        explicit InvalidPath(const std::string& path);
        const char *what() const noexcept override;

        private:
        std::string _path;
    };
}


#endif //RType_LOG_HPP
