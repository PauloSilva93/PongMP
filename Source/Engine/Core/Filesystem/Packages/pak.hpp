#pragma once
#include <string>
#include <fstream>
#include "Windows.h"
#include "Engine/Helpers/types.hpp"
#include "Engine/Core/Filesystem/Packages/pakdef.hpp"
#include "Engine/Core/Filesystem/Files/physical.hpp"
#include "Engine/Core/Filesystem/Files/settings.hpp"

namespace File {

    class Pak : public Physical{

        private:
            typedef std::vector<Types::Byte> FileBufferList_t;
            typedef std::vector<Package::FileTableEntry> FileTableEntryList_t;

        public:
            
            void Generate(std::string folder, const std::string& output);
            void Extract(const std::string filename, const std::string& outputPath);

            bool Open(const std::string path) override;
            bool Close() override;
            
            File::Physical* Read(const std::string path);
            
            bool Exist(const std::string& path);
            bool CheckSignature();

        private:
            std::basic_ifstream<Types::Byte>*   fs;
            Package::Header                     header;
            Package::FileTableEntry*            fileTableEntry;

            Package::Header GenerateHeader(uint32_t numEntries);
            void GenerateFilesTable(const std::string& folder, FileBufferList_t& databuffer, FileTableEntryList_t& ftentries);
            void GenerateCompressedFile(const std::string& output, FileBufferList_t& databuffer, FileTableEntryList_t& ftentries);

    };

};