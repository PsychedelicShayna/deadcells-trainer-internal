#ifndef DC_ASM_PATCHES_H
#define DC_ASM_PATCHES_H

#include <array>

#include <libght.hpp>

extern Ght::Internal::GenericAssemblyPatch AP_NoFall;
extern Ght::Internal::GenericAssemblyPatch AP_InfiniteJump;
extern Ght::Internal::GenericAssemblyPatch AP_InfiniteFlasks;
extern Ght::Internal::GenericAssemblyPatch AP_DisableOutOfBounds;

class InertiaMultiPatch {
protected:
    std::array<Ght::Internal::GenericAssemblyPatch, 6> InertiaPatches;
    bool isPatched;

public:
    int32_t Patch();
    int32_t Restore();
    int32_t Toggle();

    bool IsPatched() const;

    InertiaMultiPatch();
} extern AP_InertiaMultiPatch;

#endif // DC_ASM_PATCHES_H
