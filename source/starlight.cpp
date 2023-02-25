#include "starlight.hpp"

void Starlight::Initialize(Starlight::UI::Overlay *overlay)
{
    Starlight::UI::Initialize(overlay);
}

std::string Starlight::Utils::ConvertToHex(void *data, size_t size, size_t outLength)
{
    char *out = new char[outLength];
    for (size_t i = 0; i < size; i++)
    {
        sprintf(out + (i * 2), "%02X", ((unsigned char *)data)[i]);
    }
    return std::string(out, outLength);
}