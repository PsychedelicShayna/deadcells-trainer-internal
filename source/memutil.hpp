#ifndef MEMUTIL_HPP
#define MEMUTIL_HPP

#ifdef __WIN64
#define memaddr_t uint64_t
#else
#define memaddr_t uint32_t
#endif

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <vector>

extern memaddr_t ResolvePointerOffsets(memaddr_t base_address, std::vector<memaddr_t> offsets);
extern memaddr_t GetModuleBaseAddres(const wchar_t* module_name);

extern std::vector<uint8_t> OverwriteInstructions(memaddr_t address, const std::vector<uint8_t>& new_instructions);

extern uint8_t* FindInstructionPatternInVector(std::vector<uint8_t>& data, const std::vector<uint8_t>& pattern, const std::vector<uint8_t>& mask, const uint8_t& xor_byte);
extern std::vector<memaddr_t> ScanInstructionPattern(memaddr_t starting_address, memaddr_t end_address, const std::vector<uint8_t>& pattern, const std::vector<uint8_t>& mask, const uint8_t& xor_byte);



#endif // MEMUTIL_HPP
