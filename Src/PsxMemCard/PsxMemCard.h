#pragma once

#include <cstdint>

namespace Psx {
    namespace MemCard {
        namespace HeaderFrame {

            inline bool isBlockValid(const std::uint8_t* data) {
                if((data[0] != 'M') || (data[1] != 'C')){
                    return false;
                }

                std::uint8_t checksum = 0x00;
                for(std::uint8_t i = 0; i < 127; ++i){
                    checksum ^= data[i];
                }
                return checksum == data[127];
            }
        }

        enum class BlockAllocationState : std::uint8_t {
            FirstFileBlock = 0x51,
            MiddleFileBlock = 0x52,
            LastFileBlock = 0x53,
            Formatted = 0xa0,
            FirstFileBlockDeleted = 0xa1,
            MiddleFileBlockDeleted = 0xa2,
            LastFileBlockDeleted = 0xa3
        };

#pragma pack(push, 1)
        struct DirectoryFrame {
            std::uint8_t allocationState[4];
            std::uint8_t fileSize[4]; //in bytes
            std::uint8_t nextBlockId[2];
            std::uint8_t name[21];
            std::uint8_t unused;
            std::uint8_t garbage[95];
            std::uint8_t checksum;

            bool isValidChecksum() const {
                const std::uint8_t* data = &allocationState[0];
                std::uint8_t checksum = 0x00;
                for(std::uint8_t i = 0; i < 127; ++i){
                    checksum ^= data[i];
                }
                return checksum == data[127];
            }
        };
#pragma pack(pop)
    }
}
