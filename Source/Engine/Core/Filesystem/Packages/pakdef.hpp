#pragma once
#include <array>
#include <cinttypes>
#include "Engine/Helpers/version.hpp"

#define PACKAGE_SIGNATURE "ENGINE"

namespace Package {

    struct Header {

        std::array<char, 8> signature;          // Used to quickly verify file format.
        Helpers::Version    version;            // The version of the format. This should match with the code that parses it.
        uint32_t            numEntries = 0;     // The number of directories/files. 

    };
    
    struct FileTableEntry {

        std::array<char, 255>   path;           // The path to the file (relative to the pak directory).
        uint32_t                size = 0;       // The size of the file in bytes.
        uint32_t                offset = 0;     // Offset pointing to start of binary data.

    };


};