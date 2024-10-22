#include "memutil.hpp"

memaddr_t ResolvePointerOffsets(memaddr_t base_address, std::vector<memaddr_t> offsets) {
    memaddr_t current_address { base_address };

    for(const memaddr_t& offset : offsets) {
        current_address = *reinterpret_cast<memaddr_t*>(current_address);
        current_address += offset;
    }

    return current_address;
}

memaddr_t GetModuleBaseAddres(const wchar_t* module_name) {
    return reinterpret_cast<memaddr_t>(GetModuleHandle(module_name));
}

std::vector<uint8_t> OverwriteInstructions(memaddr_t address, const std::vector<uint8_t>& new_instructions) {
    uint8_t* address_bptr { reinterpret_cast<BYTE*>(address) };
    std::vector<uint8_t> old_instruction_bytes(new_instructions.size());

    DWORD old_protection_flag;
    VirtualProtect(address_bptr, new_instructions.size(), PAGE_EXECUTE_READWRITE, &old_protection_flag);

    memcpy(old_instruction_bytes.data(), address_bptr, old_instruction_bytes.size());
    memcpy(address_bptr, new_instructions.data(), new_instructions.size());

    VirtualProtect(address_bptr, new_instructions.size(), old_protection_flag, &old_protection_flag);

    return old_instruction_bytes;
}

uint8_t* FindInstructionPatternInVector(std::vector<uint8_t>& data, const std::vector<uint8_t>& pattern, const std::vector<uint8_t>& mask, const uint8_t& xor_byte) {
    for(size_t i { 0 }; i < data.size(); ++i) {
        bool found_patten { true };

        for(size_t c { 0 }; c < pattern.size(); ++c) {
            if(i + c >= data.size()) {
                found_patten = false;
                break;
            }

            if(mask[c] != 0x00 && (pattern[c] ^ xor_byte) != data[i + c]) {
                found_patten = false;
                break;
            }
        }

        if(found_patten) {
            memaddr_t data_addr { reinterpret_cast<memaddr_t>(data.data()) };
            return reinterpret_cast<uint8_t*>(data_addr + i);
        }
    }

    return nullptr;
}

constexpr int test { 1337 };

std::vector<memaddr_t> ScanInstructionPattern(memaddr_t starting_address, memaddr_t end_address, const std::vector<uint8_t>& pattern, const std::vector<uint8_t>& mask, const uint8_t& xor_byte) {
    std::vector<memaddr_t> match_locations;

    uint8_t* starting_address_ptr    { reinterpret_cast<uint8_t*>(starting_address) };
    uint8_t* ending_address_ptr      { reinterpret_cast<uint8_t*>(end_address)      };

    MEMORY_BASIC_INFORMATION memory_info;

    uint8_t* calling_module_allocation_base { nullptr };

    if(VirtualQuery(&test, &memory_info, sizeof(memory_info))) {
        calling_module_allocation_base = reinterpret_cast<uint8_t*>(memory_info.AllocationBase);
        std::cout << "Calling module allocation base: " << std::setw(2) << std::setfill('0') << std::hex << (memaddr_t)calling_module_allocation_base << "\n";
    } else {
        std::cout << "Unable to determine the allocation base address!\n";
        return match_locations;
    }

    memory_info.RegionSize = 0x1000;

    for(uint8_t* current = starting_address_ptr; current < ending_address_ptr; current += memory_info.RegionSize) {
        if(!VirtualQuery(current, &memory_info, sizeof(memory_info))) continue;
        if(memory_info.State != MEM_COMMIT || memory_info.Protect == PAGE_NOACCESS) continue;
        if(reinterpret_cast<uint8_t*>(memory_info.AllocationBase) == calling_module_allocation_base) continue;

        DWORD old_protection_flag { NULL };

        if(VirtualProtect(memory_info.BaseAddress, memory_info.RegionSize, PAGE_EXECUTE_READWRITE, &old_protection_flag)) {
            std::vector<uint8_t> region_bytes(memory_info.RegionSize);
            memcpy(region_bytes.data(), memory_info.BaseAddress, region_bytes.size());
            VirtualProtect(memory_info.BaseAddress, memory_info.RegionSize, old_protection_flag, &old_protection_flag);

            uint8_t* pattern_location { FindInstructionPatternInVector(region_bytes, pattern, mask, xor_byte) };

            if(pattern_location != nullptr) {
                uint8_t* absolute_location { reinterpret_cast<uint8_t*>(memory_info.BaseAddress) + (pattern_location - region_bytes.data()) };

                std::cout << "Found a matching pattern!\n";
                std::cout << "Absolute location: " << std::hex << std::setw(2) << std::setfill('0') << reinterpret_cast<memaddr_t>(absolute_location) << "\n";
                std::cout << "Pattern allocation base: " << std::hex << memory_info.AllocationBase << "\n";

                match_locations.emplace_back(reinterpret_cast<memaddr_t>(absolute_location));
            }
        }
    }

    return match_locations;
}



