#include "package-point.hpp"

PackageMountPoint::PackageMountPoint(const std::string& physicalPath) :
    MountPoint(physicalPath, -1)
{

};

bool PackageMountPoint::OnMount() {

    packageFile = std::make_unique<File::Pak>();

    return packageFile->Open(this->physicalPath);

};

bool PackageMountPoint::HasFile(const std::string& filepath) {

    if (!packageFile->IsOpen())
        return false;

    return packageFile->Exist(filepath);

};

std::unique_ptr<File::Physical> PackageMountPoint::GetFile(const std::string& filepath) {

    if (!packageFile->IsOpen())
        return nullptr;

    std::unique_ptr<File::Physical> pFile(packageFile->Read(filepath));
    return pFile;

};
