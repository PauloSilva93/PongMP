#pragma once
#include <Windows.h>
#include "Engine/Helpers/types.hpp"

namespace File {

    struct Time {

        LPFILETIME  creationTime;
        LPFILETIME  lastAccessTime;
        LPFILETIME  lastWriteTime;

    };

    struct Attributes {

        int64_t         size;
        Types::Byte*    data;
        char*           extension;
        char*           fullpath;
        Time            fileTime;

    };

};