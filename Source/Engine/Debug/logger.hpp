#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdint>

#define LOG_ON_IOSTREAM 0

namespace Debug {

    enum class ELogLevel{

        DEBUG,          // White
        VERBOSE,        // Blue
        SUCCESS,        // Green
        WARNING,        // Yellow
        ERROR,          // Red
        ASSERT          // Purple

    };

    struct LogMessage{

        const char*     file;
        int32_t         lineNumber;
        std::time_t     timestamp;
        ELogLevel       level;
        const char*     levelText;
        const char*     tag;
        char            message[256];

    };

    class Logger {

        public:

            static void Log(const char* file, int line, ELogLevel level, const char* tag, const char* format, ...);

            static void ToFile(const char* path);
            static void TagToFile(const char* tag);

            // static void Timestamp();
            
            static std::vector<LogMessage> messages;

        private:
            static void LogIOStream(LogMessage& msg);

    };

};


#ifdef ENGINE_DEBUG
    #define DEBUG_LOG(tag, format, ...)     Debug::Logger::Log(__FILE__, __LINE__, Debug::ELogLevel::DEBUG,    (tag), (format), __VA_ARGS__)
    #define DEBUG_VERBOSE(tag, format, ...) Debug::Logger::Log(__FILE__, __LINE__, Debug::ELogLevel::VERBOSE,  (tag), (format), __VA_ARGS__)
    #define DEBUG_SUCCESS(tag, format, ...) Debug::Logger::Log(__FILE__, __LINE__, Debug::ELogLevel::SUCCESS,  (tag), (format), __VA_ARGS__)
    #define DEBUG_WARNING(tag, format, ...) Debug::Logger::Log(__FILE__, __LINE__, Debug::ELogLevel::WARNING,  (tag), (format), __VA_ARGS__)
    #define DEBUG_ERROR(tag, format, ...)   Debug::Logger::Log(__FILE__, __LINE__, Debug::ELogLevel::ERROR,    (tag), (format), __VA_ARGS__)

    #define DEBUG_CHECK(condition, tag, success, error, ...) (condition) ? DEBUG_SUCCESS(tag, success, __VA_ARGS__) : DEBUG_ERROR(tag, error, __VA_ARGS__)

    #define DEBUG_ASSERT(condition, tag, format, ...)                                           \
    {                                                                                           \
        if (!(condition)){                                                                      \
                                                                                                \
            std::cerr << "Assertion failed at " << __FILE__ << ":" << __LINE__;                 \
            std::cerr << " inside " << __FUNCTION__ << std::endl;                               \
            std::cerr << "Condition: " << #condition;                                           \
                                                                                                \
            Debug::Logger::Log(__FILE__, __LINE__, ELogLevel::ASSERT, (tag), (format), __VA_ARGS__);    \
                                                                                                \
            std::terminate();                                                                   \
                                                                                                \
        }                                                                                       \
    }                                                                                           \

#else
    #define DEBUG_LOG(tag, format, ...)
    #define DEBUG_VERBOSE(tag, format, ...)
    #define DEBUG_SUCCESS(tag, format, ...)
    #define DEBUG_WARNING(tag, format, ...)
    #define DEBUG_ERROR(tag, format, ...)
    #define DEBUG_CHECK(condition, tag, success, error, ...)
    #define DEBUG_ASSERT(condition, tag, format, ...) (condition)
#endif