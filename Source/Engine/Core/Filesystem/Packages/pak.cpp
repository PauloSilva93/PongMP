#include "pak.hpp"
#include "Engine/Core/Filesystem/paths.hpp"
#include "Engine/Debug/logger.hpp"
#include "Engine/Helpers/string.hpp"

namespace File {

    void Pak::Generate(std::string folder, const std::string& output) {

        FileBufferList_t databuffer;
        FileTableEntryList_t ftentries;

        this->GenerateFilesTable(folder, databuffer, ftentries);

        this->GenerateCompressedFile(output, databuffer, ftentries);        

    };

    Package::Header Pak::GenerateHeader(uint32_t numEntries){

        Package::Header header = {};
        header.signature = { PACKAGE_SIGNATURE };
        header.version = { 1, 2, 3 };
        header.numEntries = numEntries;

        return header;

    };

    void Pak::GenerateFilesTable(const std::string& folder, FileBufferList_t& databuffer, FileTableEntryList_t& ftentries) {

        Paths::List filepaths = Paths::IterateDirectory(folder);

        for (std::string path : filepaths) {

            std::basic_ifstream<Types::Byte> fstream(path, std::ios::ate | std::ios::binary);
            DEBUG_ASSERT(!fstream.fail(), "PACKAGE FILE", "File at '%s' not found", path.c_str());

            Package::FileTableEntry fte;
            memset(&fte, 0, sizeof(Package::FileTableEntry));   // Clear Garbage

            // Remove Relative Path from filename
            if ((path[0] == '.' && path[1] == '/') || path[0] == '/'){
                std::size_t npos = path.find_first_of("/\\")+1;
                path = path.substr(npos, path.size() - npos);
            };


            std::string filePath = path.substr(path.find_first_of("/\\")+1);
            memcpy(fte.path.data(), filePath.data(), filePath.size()+1);

            fte.size = (uint32_t)fstream.tellg();
            fte.offset = (uint32_t)databuffer.size();

            fstream.seekg(0);

            std::vector<Types::Byte> fileBufferData(fte.size);
            fstream.read(fileBufferData.data(), fte.size);

            databuffer.insert(databuffer.end(), fileBufferData.begin(), fileBufferData.end());
            ftentries.push_back(fte);

            fstream.close();

        };

    };

    void Pak::GenerateCompressedFile(const std::string& output, FileBufferList_t& databuffer, FileTableEntryList_t& ftentries) {

        Package::Header header = this->GenerateHeader((uint32_t)ftentries.size());

        std::basic_ofstream<Types::Byte> compressedFile(output, std::ios::ate | std::ios::binary);
        
        compressedFile.write(
            reinterpret_cast<Types::Byte*>(&header), 
            sizeof(Package::Header)
        );

        const uint32_t baseOffset = sizeof(Package::Header) + (uint32_t)ftentries.size() * sizeof(Package::FileTableEntry);
        for (Package::FileTableEntry fte : ftentries) {

            fte.offset += baseOffset;
            compressedFile.write(
                reinterpret_cast<Types::Byte*>(&fte),
                sizeof(Package::FileTableEntry)
            );

        };

        compressedFile.write(databuffer.data(), databuffer.size());
        compressedFile.close();

    };

    void Pak::Extract(const std::string filename, const std::string& outputPath) {

        this->Open(filename);

            for (uint32_t i = 0; i < this->header.numEntries; i++) {

                Package::FileTableEntry& entry = this->fileTableEntry[i];

                std::vector<Types::Byte> filebuffer(entry.size);

                fs->read(filebuffer.data(), filebuffer.size());

                std::string outpath = outputPath + std::string(entry.path.data());

                std::size_t npos = outpath.find_last_of("/\\");
                std::string folderPath = outpath.substr(0, npos + 1);

                if (Paths::CreateDirectory(folderPath)) {
                    std::basic_ofstream<Types::Byte> ofstream(outpath, std::ios::binary);
                    DEBUG_ASSERT(!ofstream.fail(), "PACKAGE", "Failed to create file %s", outpath);
                    ofstream.write(filebuffer.data(), filebuffer.size());
                };

            };

        this->Close();

    };

    bool Pak::Open(const std::string path) { 

        fs = new std::basic_ifstream<Types::Byte>(path, std::ios::in | std::ios::binary);
        DEBUG_ASSERT(!fs->fail(), "PACKAGE", "Failed to open asset file at: %s", path);

        this->isOpen = true;

        fs->read(
            reinterpret_cast<Types::Byte*>(&header),
            sizeof(Package::Header)
        );

        DEBUG_ASSERT(this->CheckSignature(), "PACKAGE", "Asset file at: %s has bad format", path);

        this->fileTableEntry = new Package::FileTableEntry[this->header.numEntries];
        fs->read(
            reinterpret_cast<Types::Byte*>(fileTableEntry),
            sizeof(Package::FileTableEntry) * this->header.numEntries
        );

        return this->header.numEntries > 0;
    };

    bool Pak::Close() { 

        memset(&header, 0, sizeof(Package::Header));
        delete this->fileTableEntry;

        if (fs->is_open()) fs->close();

        delete fs;

        return this->header.numEntries == 0;

    };

    File::Physical* Pak::Read(const std::string path) {

        for (uint32_t i = 0; i < header.numEntries; i++) {

            if (std::strcmp(path.c_str(), fileTableEntry[i].path.data()) == 0) {

                Package::FileTableEntry& entry = fileTableEntry[i];
                uint32_t size = entry.size;
                uint32_t offset = entry.offset;

                fs->seekg(entry.offset);

                if (size < 0) return nullptr;

                byte* buffer = new byte[size];
                memset(buffer, 0, size);
                fs -> read(buffer, size);

                File::Attributes attr;
                attr.data = buffer;
                attr.size = size;

                File::Physical* file = new File::Physical();
                file->FromMemory(attr);

                return file;

            };

        };

        return nullptr;

    };

    bool Pak::Exist(const std::string& path) {
        
        for (uint32_t i = 0; i < header.numEntries; i++){

            if (std::strcmp(path.c_str(), fileTableEntry[i].path.data()) == 0)
                return true;

        }

        return false;

    };

    bool Pak::CheckSignature() {

        if (isOpen) {
            std::string signature = std::string(this->header.signature.data());

            return (signature == PACKAGE_SIGNATURE);
        };

        return false;

    };

};

// ----------------------------
// -          header          -
// ----------------------------
// -     File Table Entry     -
// ----------------------------
// -                          -
// -    Content Compressed    -
// -                          -
// ----------------------------