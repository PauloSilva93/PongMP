#include "string.hpp"
#include <sstream>

namespace Helpers {

    std::vector<std::string> String::Split(std::string& input, char delimiter) {
        
        std::vector<std::string> result;
        std::stringstream ss(input);

        std::string buff;
        while(getline(ss, buff, delimiter)) {
            result.push_back(buff);
        };

        return result;

    };

};