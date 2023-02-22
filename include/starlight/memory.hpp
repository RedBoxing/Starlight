#pragma once

#include <common.hpp>

namespace Starlight
{
    namespace Memory
    {
        void ReadMemory(void *dst, uintptr_t src, size_t size);
        void WriteMemory(uintptr_t dst, const void *src, size_t size);

        template <typename T>
        T ReadMemory(uintptr_t src)
        {
            T dst;
            ReadMemory(&dst, src, sizeof(T));
            return dst;
        }

        template <typename T>
        void WriteMemory(uintptr_t dst, T src)
        {
            WriteMemory(dst, &src, sizeof(T));
        }

        u64 ReadMemory64(uintptr_t src);
        u32 ReadMemory32(uintptr_t src);
        u16 ReadMemory16(uintptr_t src);
        u8 ReadMemory8(uintptr_t src);

        void WriteMemory64(uintptr_t dst, u64 src);
        void WriteMemory32(uintptr_t dst, u32 src);
        void WriteMemory16(uintptr_t dst, u16 src);
        void WriteMemory8(uintptr_t dst, u8 src);
    }
}