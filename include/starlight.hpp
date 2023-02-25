#pragma once

#include "starlight/hid.hpp"
#include "starlight/ui.hpp"
#include "starlight/fs.hpp"
#include "starlight/memory.hpp"

namespace Starlight
{
    void Initialize(Starlight::UI::Overlay *overlay);

    namespace Utils
    {
        std::string ConvertToHex(void *data, size_t size, size_t outLength);
    }
}