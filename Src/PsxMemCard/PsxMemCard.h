#pragma once

#include <cstdint>

namespace Psx {
    namespace MemCard {
        namespace HeaderFrame {

            bool isBlockValid(const std::uint8_t* data) {
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
