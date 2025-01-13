#pragma once
#include "Engine/Debug/ImGui/Base/widget.hpp"
#include "Engine/Debug/Logger.hpp"
#include "Engine/Core/Filesystem/Packages/pak.hpp"
#include "Engine/Core/Filesystem/Packages/pakdef.hpp"

namespace ImGuiWidget {

    class PackageViewer : public WidgetBase {

        public: 
            virtual void Render() override;

        private:
            Package::FileTableEntry* fteList;

    };

};