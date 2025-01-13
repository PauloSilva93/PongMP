#pragma once
#include <vector>
#include "Engine/Core/Filesystem/paths.hpp"
#include "Engine/Core/Filesystem/MountPoints/mount-point.hpp"

class PhysicalMountPoint : public MountPoint {

    public:
        PhysicalMountPoint(const std::string& physicalPath);
        virtual ~PhysicalMountPoint();

        virtual bool OnMount() override;
        virtual bool HasFile(const std::string& filepath) override;
        virtual std::unique_ptr<File::Physical> GetFile(const std::string& filepath) override;

    private:
        bool RegisterDirectory(const std::string& path);
        Paths::List fileEntries;

};