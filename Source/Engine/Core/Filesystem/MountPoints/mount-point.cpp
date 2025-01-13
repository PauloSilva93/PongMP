#include "mount-point.hpp"

MountPoint::MountPoint(const std::string& pathPhysical, const int order) :
    physicalPath(pathPhysical), order(order)
{

};