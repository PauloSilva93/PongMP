#include "paths.hpp"
#include <filesystem>

namespace Paths {

    /**
     * @brief Get the size of a file in bytes.
     * @param path The relative path to the file. 
     * @return Returns an int64_t value.
     */
    int64_t Size(const std::string path){

        std::string _path_final = CurrentPath() + "/" + path;

        if (!Exists(path)) return -1;

        return std::filesystem::file_size(_path_final);

    };

    /**
     * @brief Checks if a file or directory exists.
     * @param path The relative path to the file/directory. 
     * @return Returns a boolean value.
     */
    bool Exists(const std::string path){
    
        std::string _path_final = CurrentPath() + "/" + path;

        return std::filesystem::exists(_path_final);
    };

    /**
     * @brief Check the extension type of a given file.
     * @param path The relative path to the file. 
     * @return Returns a std::string value.
     */
    std::string Extension(const std::string path){

        if (!Exists(path)) return "";

        // Get dot in final of string
        std::size_t dotPos = path.rfind('.');

        // if can't find any dot return nothing
        if (dotPos == std::string::npos)
            return "";

        if (path[dotPos+1] == '/')
            return "";

        // return extension
        return path.substr(dotPos+1);


    };
    /**
     * @brief Check the name of the folder where the file is located.
     * @param path The relative path to the file. 
     * @return Returns a std::string value.
     */
    std::string Directory(const std::string path){

        if (!Exists(path)) return "invalid directory path";

        std::string _final_path = Fullpath(path);

        std::size_t filePos = _final_path.find_last_of("/\\");

        if (filePos == std::string::npos)
            return "invalid directory";

        return _final_path.substr(0, filePos + 1);

    };
    /**
     * @brief Check the full path to the file.
     * @param path The relative path to the file. 
     * @return Returns a std::string value.
     */
    std::string Fullpath(const std::string path){
        return CurrentPath() + "/" + path;
    };
    /**
     * @brief Check what is the current execution path of the program.
     * @return Returns a std::string value.
     */
    std::string CurrentPath(){
        return std::filesystem::current_path().string();
    };

    /**
     * @brief Checks when the file was created based on local time (Works on Windows only).
     * @param path The relative path to the file.
     * @return Returns a LPFILETIME value.
     */
    LPFILETIME CreationTime(const std::string path){

        std::string _path_final = CurrentPath() + "/" + path;

        if (!Exists(path)) return NULL;

        std::wstring _wstr_path(_path_final.begin(), _path_final.end());

        WIN32_FIND_DATA ffd;
        HANDLE _handle = FindFirstFile(_wstr_path.c_str(), &ffd);

        // Creation Time
        LPFILETIME creationTime = new FILETIME;
        creationTime->dwHighDateTime = ffd.ftCreationTime.dwHighDateTime;
        creationTime->dwLowDateTime = ffd.ftCreationTime.dwLowDateTime;
        
        // Convert to Local Time
        FileTimeToLocalFileTime(creationTime, creationTime);

        return creationTime;

    };
    /**
     * @brief Checks when the file was last accessed based on local time (Works on Windows only).
     * @param path The relative path to the file.
     * @return Returns a LPFILETIME value.
     */
    LPFILETIME LastAccessTime(const std::string path){

        std::string _path_final = CurrentPath() + "/" + path;

        if (!Exists(path)) return NULL;

        std::wstring _wstr_path(_path_final.begin(), _path_final.end());

        WIN32_FIND_DATA ffd;
        HANDLE _handle = FindFirstFile(_wstr_path.c_str(), &ffd);

        // Last Access Time
        LPFILETIME lastAcessTime = new FILETIME;
        lastAcessTime->dwHighDateTime = ffd.ftLastAccessTime.dwHighDateTime;
        lastAcessTime->dwLowDateTime = ffd.ftLastAccessTime.dwLowDateTime;

        // Convert to Local Time
        FileTimeToLocalFileTime(lastAcessTime, lastAcessTime);

        return lastAcessTime;

    };
    /**
     * @brief Checks when was the last time the file was written based on local time (Works on Windows only).
     * @param path The relative path to the file.
     * @return Returns a LPFILETIME value.
     */
    LPFILETIME LastWriteTime(const std::string path){

        std::string _path_final = CurrentPath() + "/" + path;

        if (!Exists(path)) return NULL;

        std::wstring _wstr_path(_path_final.begin(), _path_final.end());

        WIN32_FIND_DATA ffd;
        HANDLE _handle = FindFirstFile(_wstr_path.c_str(), &ffd);

        // Last Write Time
        LPFILETIME lastWriteTime = new FILETIME;
        lastWriteTime->dwHighDateTime = ffd.ftCreationTime.dwHighDateTime;
        lastWriteTime->dwLowDateTime = ffd.ftCreationTime.dwLowDateTime;
        
        // Convert to Local Time
        FileTimeToLocalFileTime(lastWriteTime, lastWriteTime);

        return lastWriteTime;

    };

    /**
     * @brief Iterate over all folders and subfolders in the given path.
     * @param path The relative path to the directory.
     * @return Returns a std::vector< std::string > value.
     */
    Paths::List IterateDirectory(std::string path){

        Paths::List files;

        // Fix Slash in final string
        std::string _path_final = CurrentPath() + "/" + path;

        if (!Exists(path)) return files;

        // Loop through files and directories
        for (const auto& entry : std::filesystem::directory_iterator(_path_final)){

            const auto filenameStr = entry.path().filename().string();

            if (entry.is_directory()){
            
                // Recursively entry inside folders
                Paths::List subfolderFiles = IterateDirectory(path + "/" + filenameStr);
                files.insert(files.end(), subfolderFiles.begin(), subfolderFiles.end());
            
            } else if (entry.is_regular_file()){
            
                files.push_back(path + "/" + filenameStr);
            
            }

        }

        return files;

    };

    Paths::List IterateFilesWithExtension(std::string path, std::string extension) {

        Paths::List files;

        // Fix Slash in final string
        std::string _path_final = CurrentPath() + "/" + path;

        if (!Exists(path)) return files;

        // Loop through files and directories
        for (const auto& entry : std::filesystem::directory_iterator(_path_final)){

            const auto filenameStr = entry.path().filename().string();

            if (entry.is_directory()){
            
                // Recursively entry inside folders
                Paths::List subfolderFiles = IterateFilesWithExtension(path + "/" + filenameStr, extension);
                files.insert(files.end(), subfolderFiles.begin(), subfolderFiles.end());
            
            } else if (entry.is_regular_file()){
            
                if (Extension(path + "/" + filenameStr) == extension)
                    files.push_back(path + "/" + filenameStr);
            
            }

        }

        return files;

    };

    bool CreateDirectory(const std::string& path) {

        if (!std::filesystem::create_directories(path)) {

            if (std::filesystem::exists(path))
                return true;

            return false;

        };

        return false;

    };

    std::string Normalize(const std::string& path){

        std::string output = std::string(path.begin(), path.end());
        
        for (char& c : output) {

            if (c == '\\')
                c = '/';

            c = (char)std::tolower(c);

        };

        if (output.find("./") == 0)
            output = std::string(output.begin() + 2, output.end());

        return output;
        
    };

};