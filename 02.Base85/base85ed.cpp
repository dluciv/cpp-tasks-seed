#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <array>
#include <algorithm>

#include "base85ed.h"

namespace {

constexpr char b85_alphabet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

constexpr std::array<int, 256> build_decode_map() {
    std::array<int, 256> map{};
    for (int i = 0; i < 256; ++i) map[i] = -1;
    for (int i = 0; i < 85; ++i) {
        map[static_cast<uint8_t>(b85_alphabet[i])] = i;
    }
    return map;
}

constexpr std::array<int, 256> decode_map = build_decode_map();

} 


// TODO: implement this in C++
std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;
    size_t size = bytes.size();
    if (size == 0) return out;
    
    out.reserve(size * 5 / 4 + 5);

    for (size_t i = 0; i < size; i += 4) {
        uint32_t acc = 0;
        size_t chunk_size = std::min<size_t>(4, size - i);

        for (size_t j = 0; j < 4; ++j) {
            acc <<= 8;
            if (j < chunk_size) {
                acc |= bytes[i + j];
            }
        }

        uint32_t divisors[] = { 52200625, 614125, 7225, 85, 1 };
        for (size_t j = 0; j <= chunk_size; ++j) {
            out.push_back(b85_alphabet[(acc / divisors[j]) % 85]);
        }
    }

    return out;
}


// TODO: implement this in C++
std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> out;
    size_t size = b85str.size();
    if (size == 0) return out;
    
    out.reserve(size * 4 / 5 + 4);

    for (size_t i = 0; i < size; i += 5) {
        size_t chunk_size = std::min<size_t>(5, size - i);
        if (chunk_size == 1) {
            throw std::runtime_error("invalid base85 string: isolated character");
        }

        uint64_t acc = 0;
        for (size_t j = 0; j < 5; ++j) {
            if (j < chunk_size) {
                int val = decode_map[b85str[i + j]];
                if (val == -1) {
                    throw std::runtime_error("invalid base85 character");
                }
                acc = acc * 85 + val;
            } else {
                acc = acc * 85 + 84;
            }
        }

        if (acc > 0xFFFFFFFF) {
            throw std::runtime_error("base85 sequence overflow");
        }

        if (chunk_size >= 2) out.push_back(static_cast<uint8_t>((acc >> 24) & 0xFF));
        if (chunk_size >= 3) out.push_back(static_cast<uint8_t>((acc >> 16) & 0xFF));
        if (chunk_size >= 4) out.push_back(static_cast<uint8_t>((acc >> 8) & 0xFF));
        if (chunk_size >= 5) out.push_back(static_cast<uint8_t>(acc & 0xFF));
    }

    return out;
}