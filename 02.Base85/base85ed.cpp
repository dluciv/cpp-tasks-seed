#include "base85ed.h"
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>

namespace {
    const std::string& alphabet() {
        static const std::string alph =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";
        return alph;
    }

    void encode_block(uint32_t n, char out[5]) {
        for (int i = 4; i >= 0; --i) {
            out[i] = alphabet()[n % 85];
            n /= 85;
        }
    }

    uint32_t decode_block(const char in[5]) {
        uint32_t n = 0;
        for (int i = 0; i < 5; ++i) {
            size_t pos = alphabet().find(in[i]);
            if (pos == std::string::npos)
                throw std::runtime_error("invalid base85 char");
            n = n * 85 + static_cast<uint32_t>(pos);
        }
        return n;
    }
}

std::vector<uint8_t> base85::encode(const std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> res;
    size_t i = 0;
    for (; i + 4 <= bytes.size(); i += 4) {
        uint32_t n = (static_cast<uint32_t>(bytes[i]) << 24) |
                     (static_cast<uint32_t>(bytes[i+1]) << 16) |
                     (static_cast<uint32_t>(bytes[i+2]) << 8) |
                     static_cast<uint32_t>(bytes[i+3]);
        char buf[5];
        encode_block(n, buf);
        res.insert(res.end(), buf, buf+5);
    }
    size_t rem = bytes.size() - i;
    if (rem > 0) {
        uint32_t n = 0;
        for (size_t j = 0; j < 4; ++j) {
            n <<= 8;
            if (j < rem) n |= bytes[i+j];
        }
        char buf[5];
        encode_block(n, buf);
        size_t out_len = rem + 1;
        res.insert(res.end(), buf, buf + out_len);
    }
    return res;
}

std::vector<uint8_t> base85::decode(const std::vector<uint8_t>& b85str) {
    if (b85str.empty()) return {};
    std::vector<uint8_t> res;
    size_t i = 0;
    while (i < b85str.size()) {
        size_t block_len = std::min<size_t>(5, b85str.size() - i);
        char in[5];
        for (size_t j = 0; j < block_len; ++j)
            in[j] = static_cast<char>(b85str[i+j]);
        for (size_t j = block_len; j < 5; ++j)
            in[j] = '~';
        uint32_t n = decode_block(in);
        size_t out_bytes = block_len - 1;
        res.push_back(static_cast<uint8_t>((n >> 24) & 0xFF));
        if (out_bytes > 1)
            res.push_back(static_cast<uint8_t>((n >> 16) & 0xFF));
        if (out_bytes > 2)
            res.push_back(static_cast<uint8_t>((n >> 8) & 0xFF));
        if (out_bytes > 3)
            res.push_back(static_cast<uint8_t>(n & 0xFF));
        i += block_len;
    }
    return res;
}