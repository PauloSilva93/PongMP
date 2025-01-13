#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "Engine/Core/Filesystem/Files/physical.hpp"
#include "Engine/Core/Filesystem/MountPoints/mount-point.hpp"
#include "Engine/Core/Filesystem/Packages/pak.hpp"

class Filesystem {

    private:
        typedef std::unique_ptr<MountPoint> MountPointPtr_t;

    public:
        static Filesystem* Get();

        bool Mount(const std::string& physicalPath);
        void AddPackagesLocation(const std::string& path);

        std::unique_ptr<File::Physical> GetFile(const std::string& filename);

    private:
        static Filesystem* instance;
        std::vector<MountPointPtr_t> mountpoints;
        std::vector<std::string> packageLocations;

        std::unique_ptr<MountPoint> CreateMountPoint(const std::string& physicalPath);

};