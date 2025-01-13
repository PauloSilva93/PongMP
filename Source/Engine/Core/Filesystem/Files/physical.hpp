#pragma once
#include <string>
#include <cinttypes>
#include <Windows.h>
#include "Vendors/nlohmann/json.hpp"
#include "Engine/Core/Filesystem/Files/settings.hpp"
#include "Engine/Helpers/types.hpp"

namespace File {

    class Physical {

        public:

            Physical();

            virtual bool Open(const std::string path);
            virtual bool Close();
            virtual bool FromMemory(Attributes attributes);
            virtual bool Create(const std::string path, Types::Byte* buffer);

            char* ToString();
            nlohmann::json ToJSON();

            int64_t Size();
            Types::Byte* Data();
            char* Extension();
            char* Fullpath();
            LPFILETIME CreationTime();
            LPFILETIME LastAccessTime();
            LPFILETIME LastWriteTime();

            bool IsOpen() { return this->isOpen; }; 

        protected:
            Attributes attributes;
            bool isOpen = false;

    };

};