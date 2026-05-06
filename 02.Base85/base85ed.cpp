#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <algorithm>

#include "base85ed.h"

static const char rfc1924_alphabet[] = 
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static int get_char_index(char c) {
    const char* pos = strchr(rfc1924_alphabet, c);
    if (!pos) return -1;
    return static_cast<int>(pos - rfc1924_alphabet);
}

static void encode_block_rfc1924(const uint8_t input[4], char output[5]) {
    uint32_t val = (static_cast<uint32_t>(input[0]) << 24) |
                   (static_cast<uint32_t>(input[1]) << 16) |
                   (static_cast<uint32_t>(input[2]) << 8)  |
                   (static_cast<uint32_t>(input[3]));

    for (int i = 4; i >= 0; --i) {
        output[i] = rfc1924_alphabet[val % 85];
        val /= 85;
    }
}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes) {
    std::vector<uint8_t> result;
    size_t len = bytes.size();
    
    result.reserve((len / 4) * 5 + 5);

    size_t i = 0;
    for (; i + 4 <= len; i += 4) {
        char block_out[5];
        encode_block_rfc1924(&bytes[i], block_out);
        result.insert(result.end(), block_out, block_out + 5);
    }

    if (i < len) {
        uint8_t temp_block[4] = {0};
        int remaining = static_cast<int>(len - i);
        
        memcpy(temp_block, &bytes[i], remaining);
        
        char block_out[5];
        encode_block_rfc1924(temp_block, block_out);
        
        result.insert(result.end(), block_out, block_out + remaining + 1);
    }

    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str) {
    std::vector<uint8_t> result;
    size_t len = b85str.size();
    
    std::vector<char> cleaned;
    cleaned.reserve(len);
    for (uint8_t byte : b85str) {
        char c = static_cast<char>(byte);
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0') continue;
        cleaned.push_back(c);
    }

    size_t clean_len = cleaned.size();
    if (clean_len == 0) return {};

    size_t i = 0;
    while (i < clean_len) {
        int chars_read = 0;
        uint32_t val = 0;
        
        for (int j = 0; j < 5 && (i + j) < clean_len; ++j) {
            int digit = get_char_index(cleaned[i + j]);
            if (digit == -1) {
                throw std::runtime_error("Invalid Base85 character");
            }
            
            if (val > (UINT32_MAX - digit) / 85) {
                 throw std::runtime_error("Base85 overflow");
            }
            
            val = val * 85 + static_cast<uint32_t>(digit);
            chars_read++;
        }

        int missing_chars = 5 - chars_read;
        
        if (missing_chars > 0) {
            for (int k = 0; k < missing_chars; ++k) {
                 if (val > UINT32_MAX / 85) {
                      throw std::runtime_error("Base85 overflow during padding");
                 }
                 val *= 85;
            }
            
            int bytes_to_take = chars_read - 1;
            int zero_bytes = 4 - bytes_to_take;
            
            if (zero_bytes > 0) {
                uint32_t M = 1;
                for (int z = 0; z < zero_bytes; ++z) {
                    M *= 256;
                }
                
                uint32_t remainder = val % M;
                uint32_t half_M = M / 2;
                
                if (remainder >= half_M) {
                    if (val > UINT32_MAX - (M - remainder)) {
                         val = (val / M) * M;
                    } else {
                        val = val + (M - remainder);
                    }
                } else {
                    val = val - remainder;
                }
            }
            
            int bytes_to_add = chars_read - 1;
            if (bytes_to_add < 0) bytes_to_add = 0;
            
            for (int b = 0; b < bytes_to_add; ++b) {
                result.push_back(static_cast<uint8_t>((val >> 24) & 0xFF));
                val <<= 8;
            }
        } else {
            uint8_t decoded_bytes[4];
            decoded_bytes[0] = static_cast<uint8_t>((val >> 24) & 0xFF);
            decoded_bytes[1] = static_cast<uint8_t>((val >> 16) & 0xFF);
            decoded_bytes[2] = static_cast<uint8_t>((val >> 8) & 0xFF);
            decoded_bytes[3] = static_cast<uint8_t>(val & 0xFF);
            result.insert(result.end(), decoded_bytes, decoded_bytes + 4);
        }

        i += chars_read;
    }

    return result;
}
