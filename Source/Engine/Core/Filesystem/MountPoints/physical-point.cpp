#include "physical-point.hpp"
#include <iostream>

PhysicalMountPoint::PhysicalMountPoint(const std::string& physicalPath) :
    MountPoint(physicalPath, 0)
{

};

PhysicalMountPoint::~PhysicalMountPoint() {

};

bool PhysicalMountPoint::OnMount() {

    if (!this->RegisterDirectory(this->physicalPath)) 
        return false;

    return true;

};

bool PhysicalMountPoint::HasFile(const std::string& filepath) {

    const std::string resolvedPath = Paths::Normalize(physicalPath + "/" + filepath);
    return std::find_if(fileEntries.begin(), fileEntries.end(),
        [&resolvedPath](const std::string& entry) {
            return entry == resolvedPath;
        }
    ) != fileEntries.end();

};

std::unique_ptr<File::Physical> PhysicalMountPoint::GetFile(const std::string& filepath) {

    const std::string resolvedPath = Paths::Normalize(this->physicalPath + "/" + filepath);
    auto pathIt = std::find_if(fileEntries.begin(), fileEntries.end(),
        [&resolvedPath](const std::string& entry) {
            std::cout << std::strcmp(entry.c_str(), resolvedPath.c_str()) << std::endl;
            return std::strcmp(entry.c_str(), resolvedPath.c_str()) == 0;
        }
    );

	if (pathIt == fileEntries.end()) 
        return nullptr;

	std::unique_ptr<File::Physical> pFile = std::make_unique<File::Physical>();
    
    if(!pFile->Open(resolvedPath))
        return nullptr;

    return pFile;

};

bool PhysicalMountPoint::RegisterDirectory(const std::string& path) {

    this->fileEntries = Paths::IterateDirectory(path);

    return this->fileEntries.size() > 0;

};
