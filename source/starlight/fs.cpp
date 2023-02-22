#include "starlight/fs.hpp"
#include "lib/diag/assert.hpp"
#include "nn/fs.h"

bool Starlight::FS::doesFileExist(const char *path)
{
    nn::fs::DirectoryEntryType type;
    nn::Result result = nn::fs::GetEntryType(&type, path);

    return result.isSuccess() && type == nn::fs::DirectoryEntryType_File;
}

nn::Result Starlight::FS::writeFile(const char *path, const void *data, size_t size)
{
    nn::fs::FileHandle fileHandle{};
    if (doesFileExist(path))
    {
        nn::fs::DeleteFile(path);
    }

    if (nn::fs::CreateFile(path, size).isFailure())
    {
        return 1;
    }

    if (nn::fs::OpenFile(&fileHandle, path, nn::fs::OpenMode_Write).isFailure())
    {
        return 1;
    }

    if (nn::fs::WriteFile(fileHandle, 0, data, size, nn::fs::WriteOption::CreateOption(nn::fs::WriteOptionFlag_Flush)).isFailure())
    {
        return 1;
    }

    nn::fs::CloseFile(fileHandle);

    return 0;
}

void Starlight::FS::readFile(const char *path, void **data, size_t *size)
{
    nn::fs::FileHandle fileHandle{};

    EXL_ASSERT(Starlight::FS::doesFileExist(path), "Failed to Find File: %s", path);
    R_ABORT_UNLESS(nn::fs::OpenFile(&fileHandle, path, nn::fs::OpenMode_Read))

    long fileSize = 0;
    nn::fs::GetFileSize(&fileSize, fileHandle);

    *size = fileSize;
    *data = malloc(fileSize);

    EXL_ASSERT(*data, "Failed to Allocate Buffer! File Size: %ld", fileSize);
    R_ABORT_UNLESS(nn::fs::ReadFile(fileHandle, 0, *data, fileSize))

    nn::fs::CloseFile(fileHandle);
}