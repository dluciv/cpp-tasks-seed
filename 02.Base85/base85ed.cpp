#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "base85ed.h"

// Алфавит Python Base85 (RFC 1924)
const char* ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static uint8_t b85_char_to_val(char c) {
    for (int i = 0; i < 85; ++i) {
        if (ALPHABET[i] == c) {
            return i;
        }
    }
    throw std::runtime_error("Invalid character in Base85 string");
}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;
    result.reserve(bytes.size() * 5 / 4 + 5);

    size_t i = 0;
    while (i < bytes.size()) {
        uint32_t block = 0;
        int bytes_in_block = 0;

        for (int j = 0; j < 4; ++j) {
            if (i + j < bytes.size()) {
                block = (block << 8) | bytes[i + j];
                bytes_in_block++;
            } else {
                block = block << 8;
            }
        }

        uint8_t chars[5];
        for (int k = 4; k >= 0; --k) {
            chars[k] = ALPHABET[block % 85];
            block /= 85;
        }

        int chars_to_write = bytes_in_block + 1;
        for (int k = 0; k < chars_to_write; ++k) {
            result.push_back(chars[k]);
        }
        i += 4;
    }
    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;
    result.reserve(b85str.size() * 4 / 5 + 4);

    size_t i = 0;
    while (i < b85str.size()) {
        uint32_t block = 0;
        int chars_in_block = 0;

        for (int j = 0; j < 5; ++j) {
            if (i + j < b85str.size()) {
                block = block * 85 + b85_char_to_val(b85str[i + j]);
                chars_in_block++;
            } else {
                block = block * 85;
            }
        }

        uint8_t bytes[4];
        bytes[0] = (block >> 24) & 0xFF;
        bytes[1] = (block >> 16) & 0xFF;
        bytes[2] = (block >> 8)  & 0xFF;
        bytes[3] =  block        & 0xFF;

        int bytes_to_write = chars_in_block - 1;
        for (int k = 0; k < bytes_to_write; ++k) {
            result.push_back(bytes[k]);
        }
        i += 5;
    }
    return result;
}