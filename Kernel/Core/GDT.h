#pragma once

#include <LibC/stddef.h>

class GDT
{
private:
    static constexpr size_t EntrySize = 8;
    static constexpr size_t EntryCount = 9;
    uint16_t m_ActiveEntries{ 0 };

    enum AccessAttributes : uint8_t
    {
        NULL_ACCESS = 0,
        PRESENT = 1 << 7,
        RING_3 = 1 << 5 | 1 << 6,
        CODE_OR_DATA = 1 << 4,
        EXECUTEABLE = 1 << 3,
        READABLE = 1 << 1,
        WRITEABLE = 1 << 1,
        GROWS_DOWN = 1 << 2,
        ALLOW_LOWER = 1 << 2
    };

    enum FlagAttributes : uint8_t
    {
        NULL_FLAG = 0,
        GRANULARITY_1B = 0,
        GRANULARITY_4KB = 1 << 3,
        SIZE_16_BIT = 0,
        SIZE_32_BIT = 1 << 2,
        SIZE_64_BIT = 1 << 1
    };

    friend AccessAttributes operator|(AccessAttributes left, AccessAttributes right)
    {
        return static_cast<AccessAttributes>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
    }

    friend FlagAttributes operator|(FlagAttributes left, FlagAttributes right)
    {
        return static_cast<FlagAttributes>(static_cast<uint8_t>(left) | static_cast<uint8_t>(right));
    }

    struct PACKED Entry
    {
        uint16_t LimitLower;
        uint16_t BaseLower;
        uint8_t BaseMiddle;
        AccessAttributes Access;
        uint8_t LimitUpper : 4;
        FlagAttributes Flags : 4;
        uint8_t BaseUpper;
    } m_Entries[EntryCount];

    struct PACKED Ptr
    {
        uint16_t Size;
        uint64_t Address;
    } m_Ptr;

    static GDT m_Instance;

public:
    GDT();

    void Install();
    void CreateBasicDescriptor();

    static GDT& Get();

    static constexpr uint16_t KernelCodeSelector() { return 0x8; }
    static constexpr uint16_t KernelDataSelector() { return 0x10; }

    static constexpr uint16_t UserlandCodeSelector() { return 0x18; }
    static constexpr uint16_t UserlandDataSelector() { return 0x20; }

private:
    void CreateDescriptor(uint32_t base, uint32_t limit, AccessAttributes accessAttributes, FlagAttributes flagAttributes);

    Entry& NewEntry();
};