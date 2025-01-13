#pragma once
#include <vector>
#include <string>
#include <Windows.h>

namespace Paths {

    typedef std::vector<std::string> List;

    int64_t Size(const std::string path);

    bool Exists(const std::string path);
    
    std::string CurrentPath();
    std::string Fullpath(const std::string path);
    std::string Extension(const std::string path);
    std::string Directory(const std::string path);
    
    LPFILETIME CreationTime(const std::string path);
    LPFILETIME LastAccessTime(const std::string path);
    LPFILETIME LastWriteTime(const std::string path);
    
    Paths::List IterateDirectory(std::string path);
    Paths::List IterateFilesWithExtension(std::string path, std::string extension);
    bool CreateDirectory(const std::string& path);
    std::string Normalize(const std::string& path);

};