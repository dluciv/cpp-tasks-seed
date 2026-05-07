#include "base85ed.h"
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <algorithm>

namespace {
    const char ALPHABET[] = 
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";
    const int RADIX = 85;

    int get_index(char c) {
        const char* p = strchr(ALPHABET, c);
        if (!p) throw std::runtime_error("Invalid Base85 character");
        return p - ALPHABET;
    }

    void encode_block(uint32_t n, char out[5]) {
        for (int i = 4; i >= 0; --i) {
            out[i] = ALPHABET[n % RADIX];
            n /= RADIX;
        }
    }

    uint32_t decode_block(const char in[5]) {
        uint32_t res = 0;
        for (int i = 0; i < 5; ++i) {
            res = res * RADIX + get_index(in[i]);
        }
        return res;
    }
}

std::vector<uint8_t> base85::encode(const std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> res;
    size_t i = 0;
    for (; i + 4 <= bytes.size(); i += 4) {
        uint32_t n = (bytes[i] << 24) | (bytes[i+1] << 16) | (bytes[i+2] << 8) | bytes[i+3];
        char buf[5];
        encode_block(n, buf);
        res.insert(res.end(), buf, buf + 5);
    }
    size_t rem = bytes.size() - i;
    if (rem > 0) {
        uint32_t n = 0;
        for (size_t j = 0; j < 4; ++j) {
            n <<= 8;
            if (j < rem) n |= bytes[i + j];
        }
        char buf[5];
        encode_block(n, buf);
        res.insert(res.end(), buf, buf + rem + 1);
    }
    return res;
}

std::vector<uint8_t> base85::decode(const std::vector<uint8_t>& b85str) {
    if (b85str.empty()) return {};
    std::vector<uint8_t> res;
    size_t i = 0;
    
    while (i < b85str.size()) {
        // пропускаем пробельные символы в начале
        while (i < b85str.size() && (b85str[i] == ' ' || b85str[i] == '\t' || b85str[i] == '\n' || b85str[i] == '\r')) {
            ++i;
        }
        if (i >= b85str.size()) break;
        
        size_t block_len = 0;
        char in[5];
        for (int j = 0; j < 5 && i < b85str.size(); ++j) {
            // пропускаем пробелы внутри блока
            while (i < b85str.size() && (b85str[i] == ' ' || b85str[i] == '\t' || b85str[i] == '\n' || b85str[i] == '\r')) {
                ++i;
            }
            if (i >= b85str.size()) break;
            in[j] = static_cast<char>(b85str[i]);
            ++i;
            ++block_len;
        }
        
        for (size_t j = block_len; j < 5; ++j) {
            in[j] = ALPHABET[RADIX - 1];
        }
        
        uint32_t n = decode_block(in);
        size_t out_bytes = block_len - 1;
        res.push_back(static_cast<uint8_t>((n >> 24) & 0xFF));
        if (out_bytes > 1) res.push_back(static_cast<uint8_t>((n >> 16) & 0xFF));
        if (out_bytes > 2) res.push_back(static_cast<uint8_t>((n >> 8) & 0xFF));
        if (out_bytes > 3) res.push_back(static_cast<uint8_t>(n & 0xFF));
    }
    
    return res;
}
