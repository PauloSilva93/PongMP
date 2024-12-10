#pragma once
#include <Windows.h>
#include <WinBase.h>
#undef CreateWindow

#define PRE_DEFINE_LIBRARY_PATH(path)  \
    struct DLLPath {                   \
        DLLPath(){                     \
            SetDllDirectoryW(path);    \
        };                             \
    } dllpath;