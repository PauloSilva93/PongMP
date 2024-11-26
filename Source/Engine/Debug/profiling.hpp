#pragma once
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <chrono>
#include <mutex>

namespace Profiler {

    struct Result {

        std::string name    = "Default";
        long long start     = 0;
        long long end       = 0;
        size_t threadID     = 0;

    };

    class Tracer {

        public:
            static Tracer& Instance() {

                static Tracer instance;
                return instance;

            };

            ~Tracer();

            void WriteProfile(const Result& result);

            void SetOutputLocation(const std::string& filepath);

        private:
            std::string outputfile = "../Compiler/LOGS/profiler.json";
            size_t profileCount = 0;
            std::ofstream outputStream;
            std::mutex lock;
            
            Tracer();

            void WriteHeader();
            void WriteFooter();

    };

    class Timer {

        public:
            Timer(const std::string& name);
            ~Timer();

            void Start();
            void Stop();

        private:
            typedef std::chrono::time_point<std::chrono::high_resolution_clock> ClockType;

            ClockType startTimePoint;
            Result result;
            bool stopped = false;

    };

};

#ifdef _DEBUG
    #define PROFILE_SCOPE(name) Profiler::Timer timer##__LINE__(name)
    #define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
    #define PROFILE_SCOPE(name)
#endif