#include "profiling.hpp"

namespace Profiler {

    Tracer::Tracer() {

        outputStream = std::ofstream(outputfile);
        WriteHeader();

    };

    Tracer::~Tracer() {

        WriteFooter();

    };

    void Tracer::WriteProfile(const Result& result) {

        std::lock_guard<std::mutex> lock(this->lock);

        if (profileCount++ > 0)
            outputStream << ",";

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'' );

        this->outputStream << "\n{";
        this->outputStream << "\"cat\": \"function\",";
        this->outputStream << "\"dur\":" << result.end - result.start << ",";
        this->outputStream << "\"name\": \"" << result.name << "\",";
        this->outputStream << "\"ph\": \"X\",";
        this->outputStream << "\"pid\": 0,";
        this->outputStream << "\"tid\":" << result.threadID <<",";
        this->outputStream << "\"ts\":" << result.start;
        this->outputStream << "}";

    };

    void Tracer::WriteHeader() { 
    
        outputStream << "{\"otherData\": {},\"traceEvents\": ["; 
    
    };
    
    void Tracer::WriteFooter() { 
    
        outputStream << "]}"; 
    
    };

    void Tracer::SetOutputLocation(const std::string& filepath) {

        this->outputfile = filepath;

    };

    Timer::Timer(const std::string& name) : result({ name, 0, 0, 0 }) {

        this->Start();

    };

    Timer::~Timer() {

        this->Stop();

    };

    void Timer::Start() {

        static long long lastStartTimer = 0;

        startTimePoint = std::chrono::high_resolution_clock::now();
        result.start = std::chrono::time_point_cast<std::chrono::microseconds>(startTimePoint).time_since_epoch().count();

        result.start += (result.start == lastStartTimer) ? 1 : 0;

        lastStartTimer = result.start;

        stopped = false;

    };

    void Timer::Stop() {

        if (stopped) 
            return;

        auto endTimePoint = std::chrono::high_resolution_clock::now();
        result.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        result.threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

        Tracer::Instance().WriteProfile(result);

        stopped = true;

    };

};