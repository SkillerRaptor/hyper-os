#include <Kernel/Core/GDT.h>

#include <LibC/stdio.h>

GDT GDT::m_Instance;

GDT::GDT()
    : m_Entries(), m_Ptr({ 0, (uintptr_t)m_Entries })
{
}

void GDT::Install()
{
    asm volatile("lgdt %0\n"
        "mov %1, %%ds\n"
        "mov %1, %%es\n"
        "mov %1, %%fs\n"
        "mov %1, %%gs\n"
        "mov %1, %%ss"
        :: "m"(m_Ptr), "r"(static_cast<size_t>(KernelDataSelector())), "r"(static_cast<size_t>(KernelCodeSelector())) : "memory"
        );

    printf("[CPU] GDT loaded...\n");
}

void GDT::CreateBasicDescriptor()
{
    CreateDescriptor(0, 0, AccessAttributes::NULL_ACCESS, FlagAttributes::NULL_FLAG);

    /* Kernel | Code */
    CreateDescriptor(0x00000000, 0xFFFFFFFF,
        AccessAttributes::CODE_OR_DATA |
        AccessAttributes::PRESENT |
        AccessAttributes::EXECUTEABLE |
        AccessAttributes::READABLE,
        FlagAttributes::GRANULARITY_4KB |
        FlagAttributes::SIZE_64_BIT);

    /* Kernel | Data */
    CreateDescriptor(0x00000000, 0xFFFFFFFF,
        AccessAttributes::CODE_OR_DATA |
        AccessAttributes::PRESENT |
        AccessAttributes::WRITEABLE,
        FlagAttributes::GRANULARITY_4KB |
        FlagAttributes::SIZE_32_BIT);

    /* Userspace | Code */
    CreateDescriptor(0x00000000, 0xFFFFFFFF,
        AccessAttributes::CODE_OR_DATA |
        AccessAttributes::PRESENT |
        AccessAttributes::RING_3 |
        AccessAttributes::EXECUTEABLE |
        AccessAttributes::READABLE,
        FlagAttributes::GRANULARITY_4KB |
        FlagAttributes::SIZE_64_BIT);

    /* Userspace | Data */
    CreateDescriptor(0x00000000, 0xFFFFFFFF,
        AccessAttributes::CODE_OR_DATA |
        AccessAttributes::PRESENT |
        AccessAttributes::RING_3 |
        AccessAttributes::WRITEABLE,
        FlagAttributes::GRANULARITY_4KB |
        FlagAttributes::SIZE_32_BIT);

    m_Ptr.Address = (uintptr_t)m_Entries;
}

void GDT::CreateDescriptor(uint32_t base, uint32_t limit, AccessAttributes accessAttributes, FlagAttributes flagAttributes)
{
    auto& entry = NewEntry();

    entry.BaseLower = base & 0x0000FFFF;
    entry.BaseMiddle = (base & 0x00FF0000) >> 16;
    entry.BaseUpper = (base & 0xFF000000) >> 24;

    entry.Access = accessAttributes;
    entry.Flags = flagAttributes;

    entry.LimitLower = limit & 0x0000FFFF;
    entry.LimitUpper = (limit & 0x000F0000) >> 16;
}

GDT::Entry& GDT::NewEntry()
{
    if (m_ActiveEntries >= EntryCount)
    {
        while (1);
        // TODO: Panic - GDT is out of free entries!
    }

    m_ActiveEntries++;
    m_Ptr.Size = sizeof(Entry) * m_ActiveEntries - 1;

    return m_Entries[m_ActiveEntries - 1];
}

GDT& GDT::Get()
{
    return m_Instance;
}