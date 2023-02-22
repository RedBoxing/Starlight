#include "starlight/memory.hpp"

void Starlight::Memory::ReadMemory(void *dst, uintptr_t src, size_t size)
{
    memcpy(dst, (void *)src, size);
}

void Starlight::Memory::WriteMemory(uintptr_t dst, const void *src, size_t size)
{
    memcpy((void *)dst, src, size);
}

u64 Starlight::Memory::ReadMemory64(uintptr_t src)
{
    return ReadMemory<u64>(src);
}

u32 Starlight::Memory::ReadMemory32(uintptr_t src)
{
    return ReadMemory<u32>(src);
}

u16 Starlight::Memory::ReadMemory16(uintptr_t src)
{
    return ReadMemory<u16>(src);
}

u8 Starlight::Memory::ReadMemory8(uintptr_t src)
{
    return ReadMemory<u8>(src);
}

void Starlight::Memory::WriteMemory64(uintptr_t dst, u64 src)
{
    WriteMemory(dst, src);
}

void Starlight::Memory::WriteMemory32(uintptr_t dst, u32 src)
{
    WriteMemory(dst, src);
}

void Starlight::Memory::WriteMemory16(uintptr_t dst, u16 src)
{
    WriteMemory(dst, src);
}

void Starlight::Memory::WriteMemory8(uintptr_t dst, u8 src)
{
    WriteMemory(dst, src);
}