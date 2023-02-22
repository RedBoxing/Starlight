#pragma once

#include "nn/result.h"

namespace Starlight
{
    namespace FS
    {
        bool doesFileExist(const char *path);
        nn::Result writeFile(const char *path, const void *data, size_t size);
        void readFile(const char *path, void **data, size_t *size);
    }
}