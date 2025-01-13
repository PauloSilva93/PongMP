#pragma once
#include "Engine/Core/Filesystem/Files/physical.hpp"
#include "Engine/Core/Filesystem/MountPoints/mount-point.hpp"
#include "Engine/Core/Filesystem/Packages/pak.hpp"

class PackageMountPoint : public MountPoint {

    public:
        PackageMountPoint(const std::string& physicalPath);
        virtual ~PackageMountPoint() {};
    
        virtual bool OnMount() override;
        virtual bool HasFile(const std::string& filepath) override;
        virtual std::unique_ptr<File::Physical> GetFile(const std::string& filepath) override;

        File::Pak* GetPakFile() const { return packageFile.get(); }
    
    private:
        std::unique_ptr<File::Pak> packageFile;

};