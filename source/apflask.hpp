#ifndef APFLASK_HPP
#define APFLASK_HPP

#include <libght.hpp>

namespace DcInternalHacks {
    class APFlask {
    protected:
        byteptr_t previousPatternStartLocation;

        std::vector<byte_t> originalInstructions;
        std::vector<byte_t> patchedInstructions;

        bool currentlyPatched;

    public:
        Ght::AssemblyPattern AsmPattern;

        byteptr_t LocateStartingInstruction();

        int32_t Patch();
        int32_t Restore();
        int32_t Toggle();

        bool IsPatched() const;

        APFlask();
    };
};

#endif // APFLASK_HPP
