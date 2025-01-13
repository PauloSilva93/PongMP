#pragma once
#include <string>
#include "Engine/Core/Filesystem/Files/physical.hpp"

class MountPoint {

    public:
        MountPoint(const std::string& pathPhysical, const int order = INT_MAX);
        virtual ~MountPoint() {};

        virtual bool OnMount() = 0;
        virtual std::unique_ptr<File::Physical> GetFile(const std::string& filepath) = 0;
        virtual bool HasFile(const std::string& filepath) = 0;

        const std::string& GetPhysicalPath() const { return this->physicalPath; };
        int GetOrder() const { return this->order; };

    protected:
        std::string physicalPath;
        int order;

};