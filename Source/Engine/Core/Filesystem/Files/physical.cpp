#include "physical.hpp"
#include <fstream>
#include "Engine/Core/Filesystem/paths.hpp"
#include "Engine/Debug/logger.hpp"
#include "Engine/Helpers/string.hpp"

namespace File {

    Physical::Physical() {};

    bool Physical::FromMemory(Attributes attributes) {

        this->attributes.data                     = attributes.data;
        this->attributes.size                     = attributes.size;
        this->attributes.extension                = attributes.extension;
        this->attributes.fullpath                 = attributes.fullpath;
        this->attributes.fileTime.creationTime    = attributes.fileTime.creationTime;
        this->attributes.fileTime.lastAccessTime  = attributes.fileTime.lastAccessTime;
        this->attributes.fileTime.lastWriteTime   = attributes.fileTime.lastWriteTime;

        if (this->attributes.data != nullptr) {
            isOpen = true;
            return true;
        };

        return false;

    };

    bool Physical::Open(const std::string path) {

        std::basic_ifstream<Types::Byte> fs(path, std::ios::in | std::ios::binary);
        if (fs.fail()) {
            DEBUG_ERROR("PHYSICAL FILE", "File could no been opened");
            return false;
        };

        // Get File Attributes
        // -------------------
        attributes.size                     = Paths::Size(path);
        attributes.extension                = Helpers::String::StringToChar(Paths::Extension(path));
        attributes.fullpath                 = Helpers::String::StringToChar(Paths::Fullpath(path));
        attributes.fileTime.creationTime    = Paths::CreationTime(path);
        attributes.fileTime.lastAccessTime  = Paths::LastAccessTime(path);
        attributes.fileTime.lastWriteTime   = Paths::LastWriteTime(path);

        uint64_t size = attributes.size;
        Types::Byte* buffer = new Types::Byte[size];
        memset(buffer, 0, size);

        fs.read(buffer, size);

        attributes.data = buffer;
        isOpen = true;
        fs.close();

        return true;

    };

    bool Physical::Close() {

        if (isOpen){

            // Clear Attributes
            // ----------------
            if (attributes.data)        delete attributes.data;
            if (attributes.extension)   delete [] attributes.extension;
            if (attributes.fullpath)    delete [] attributes.fullpath;
            if (attributes.size > 0)    attributes.size = 0;
            isOpen = false;
        
            return true;
    
        };

        return false;

    };
    bool Physical::Create(const std::string path, Types::Byte* buffer) {

        std::basic_ofstream<Types::Byte> ofs(path, std::ofstream::out);

        attributes.data = buffer;
        ofs << attributes.data;
        ofs.close();

        if (Paths::Exists(path)) return true;

        return false;

    };


    char* Physical::ToString() {

        if (isOpen){
            
            // Get File Size
            // -------------
            size_t size = attributes.size + 1;

            // Convert to text buffer
            // ----------------------
            char* textBuffer = new char[size];
            memcpy(textBuffer, attributes.data, size);
            textBuffer[size] = '\0';

            // Return File data
            // ----------------
            return textBuffer;

        }

        return nullptr;

    };
    
    nlohmann::json Physical::ToJSON() { 
    
        if (isOpen) {

            std::string dataAsString = this->ToString();
            if (!dataAsString.empty())
                return nlohmann::json::parse(dataAsString);

            return nlohmann::json();

        };
    
        return nlohmann::json(); 
    };

    int64_t         Physical::Size()        { return this->attributes.size; };
    Types::Byte*    Physical::Data()        { return this->attributes.data; };
    char*           Physical::Extension()   { return this->attributes.extension; };
    char*           Physical::Fullpath()    { return this->attributes.fullpath; };
    
    LPFILETIME Physical::CreationTime()     { return this->attributes.fileTime.creationTime; };
    LPFILETIME Physical::LastAccessTime()   { return this->attributes.fileTime.lastAccessTime; };
    LPFILETIME Physical::LastWriteTime()    { return this->attributes.fileTime.lastWriteTime; };

};