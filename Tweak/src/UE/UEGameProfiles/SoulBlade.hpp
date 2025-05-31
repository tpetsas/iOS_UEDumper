#pragma once

#include "../UEGameProfile.hpp"
using namespace UEMemory;

class SoulBladeProfile : public IGameProfile
{
public:
    SoulBladeProfile() = default;

    std::string GetAppName() const override
    {
        return "Soul Blade Revolution";
    }

    std::vector<std::string> GetAppIDs() const override
    {
        return {"com.netmarble.bnsmasia"};
    }

    bool isUsingCasePreservingName() const override
    {
        return false;
    }

    bool IsUsingFNamePool() const override
    {
        return false;
    }
    bool isUsingOutlineNumberName() const override
    {
        return false;
    }

    uintptr_t GetGUObjectArrayPtr() const override
    {
        return KittyScanner::findSymbol(GetExecutableInfo(), "_GUObjectArray");
    }

    uintptr_t GetNamesPtr() const override
    {
        // GFNameTableForDebuggerVisualizers_MT = &GNames
        uintptr_t name_table_p = KittyScanner::findSymbol(GetExecutableInfo(), "_GFNameTableForDebuggerVisualizers_MT");
        return name_table_p == 0 ? 0 : vm_rpm_ptr<uintptr_t>((void*)name_table_p);
    }

    UE_Offsets *GetOffsets() const override
    {
        static UE_Offsets offsets = UE_DefaultOffsets::UE4_20(isUsingCasePreservingName());
        return &offsets;
    }
};
