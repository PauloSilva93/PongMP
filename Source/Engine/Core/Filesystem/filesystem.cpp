#include "filesystem.hpp"
#include "Engine/Core/Filesystem/paths.hpp"
#include "Engine/Core/Filesystem/MountPoints/physical-point.hpp"
#include "Engine/Core/Filesystem/MountPoints/package-point.hpp"

Filesystem* Filesystem::instance = nullptr;
Filesystem* Filesystem::Get() {

    if (!instance)
        instance = new Filesystem();

    return instance;

};


bool Filesystem::Mount(const std::string& physicalPath) {

    std::unique_ptr<MountPoint> mountPtr = this->CreateMountPoint(physicalPath);
    
    if (!mountPtr) return false;
    if (!mountPtr->OnMount()) return false;

    this->mountpoints.push_back(std::move(mountPtr));

    std::sort(mountpoints.begin(), mountpoints.end(),
        [](const MountPointPtr_t& a, const MountPointPtr_t& b) {
            return a->GetOrder() > b->GetOrder();
        }
    );
    
    return true;

};

void Filesystem::AddPackagesLocation(const std::string& path) { 

    if (std::find(packageLocations.begin(), packageLocations.end(), path) != packageLocations.end())
		return;

    packageLocations.push_back(path);

    for (const std::string& location : packageLocations) {

		std::vector<std::string> pakFiles = Paths::IterateFilesWithExtension(location, "pak");
		for (const std::string& pakFile : pakFiles)
			Mount(pakFile);

	};

};

std::unique_ptr<File::Physical> Filesystem::GetFile(const std::string& filename) {

    const std::string path = Paths::Normalize(filename);

	//Search through all the mount points
	//The points that got mounted first get prioritized
	for (const auto& mountedPointPtr : this->mountpoints) {

		std::unique_ptr<File::Physical> filePtr = mountedPointPtr->GetFile(path);
		//If we didn't find the file, continue looking in the other mount points
		if (filePtr == nullptr)
            continue;

		return filePtr;
	
    };
	
    return nullptr;

};

std::unique_ptr<MountPoint> Filesystem::CreateMountPoint(const std::string& physicalPath) {

    std::string extension = Paths::Extension(physicalPath);
    if (extension.length() == 0)
        return std::make_unique<PhysicalMountPoint>(physicalPath);
    else if (extension == "pak")
        return std::make_unique<PackageMountPoint>(physicalPath);

    return nullptr;

};