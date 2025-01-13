#include "string.hpp"
#include <sstream>

namespace Helpers {

    namespace String {

        std::vector<std::string> Split(std::string& input, char delimiter) {
            
            std::vector<std::string> result;
            std::stringstream ss(input);

            std::string buff;
            while(getline(ss, buff, delimiter)) {
                result.push_back(buff);
            };

            return result;

        };

        char* StringToChar(const std::string str){

            size_t size = str.length() + 1;

            char* cstr = new char[size];
            
            strcpy_s(cstr, size, str.c_str());

            return cstr;
            
        };

    };

};