#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <cstring>

#include "base85ed.h"

namespace base85 {

    std::vector<uint8_t> encode(std::vector<uint8_t> const& bytes) {
        std::vector<uint8_t> result;
        size_t i = 0;

        while (i < bytes.size()) {
            uint32_t value = 0;
            size_t block_size = 0;

            for (size_t j = 0; j < 4 && i + j < bytes.size(); ++j) {
                value = (value << 8) | bytes[i + j];
                block_size++;
            }

            if (block_size < 4) {
                value <<= 8 * (4 - block_size);
            }

            uint8_t encoded[5];
            for (int j = 4; j >= 0; --j) {
                encoded[j] = 33 + (value % 85);
                value /= 85;
            }

            size_t out_size = (block_size == 4) ? 5 : block_size + 1;
            result.insert(result.end(), encoded, encoded + out_size);
            i += block_size;
        }

        return result;
    }

    std::vector<uint8_t> decode(std::vector<uint8_t> const& b85str) {
        std::vector<uint8_t> result;
        size_t i = 0;

        while (i < b85str.size()) {
            size_t block_size = 0;
            size_t remaining = b85str.size() - i;

            if (remaining >= 5) {
                block_size = 5;
            }
            else {
                block_size = remaining;
            }

            uint32_t value = 0;
            for (size_t j = 0; j < block_size; ++j) {
                if (b85str[i + j] < 33 || b85str[i + j] > 117) {
                    throw std::runtime_error("Invalid Base85 character");
                }
                value = value * 85 + (b85str[i + j] - 33);
            }

            if (block_size < 5) {
                for (size_t j = block_size; j < 5; ++j) {
                    value = value * 85 + 84;
                }
            }

            size_t out_size = (block_size == 5) ? 4 : block_size - 1;
            for (size_t j = 0; j < out_size; ++j) {
                result.push_back((value >> (24 - 8 * j)) & 0xFF);
            }

            i += block_size;
        }

        return result;
    }

}
