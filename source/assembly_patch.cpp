#include "assembly_patch.hpp"

byteptr_t AssemblyPatch::locateStartingInstruction() {
    if(previousPatternStartLocation != nullptr) {
        const std::vector<byteptr_t>& pattern_scan_matches {
            Ght::Internal::ScanMemoryPagesForBytePatternMatches(previousPatternStartLocation - 1024, previousPatternStartLocation + asmPattern.PatternBytes.size() + 1024, asmPattern, true)
        };

        if(pattern_scan_matches.size()) {
            return pattern_scan_matches[0] + offsetFromPatternStart;
        }
    }

    const std::vector<byteptr_t>& pattern_scan_matches {
        Ght::Internal::ScanMemoryPagesForBytePatternMatches(0x00, 0x7FFFFFFF, asmPattern, true)
    };

    if(pattern_scan_matches.size()) {
        previousPatternStartLocation = pattern_scan_matches[0];
        return pattern_scan_matches[0] + offsetFromPatternStart;
    }

    return nullptr;
}

int32_t AssemblyPatch::Patch() {
    byteptr_t instruction_location { locateStartingInstruction() };

    if(instruction_location == nullptr) return 1;
    if(isPatched) return 2;

    originalInstructions = Ght::Internal::ReplaceBytes(instruction_location, patchedInstructions);

    isPatched = true;

    return 0;
}

int32_t AssemblyPatch::Restore() {
    byteptr_t instruction_location { locateStartingInstruction() };

    if(instruction_location == nullptr) return 1;
    if(!isPatched) return 2;

    Ght::Internal::ReplaceBytes(instruction_location, originalInstructions);

    isPatched = false;

    return 0;
}

int32_t AssemblyPatch::Toggle() {
    return isPatched ? Restore() : Patch();
}

bool AssemblyPatch::IsPatched() const {
    return isPatched;
}

AssemblyPatch::AssemblyPatch()
    :
      previousPatternStartLocation    { nullptr },
      offsetFromPatternStart          { 0       },
      isPatched                       { false   }
{

}
