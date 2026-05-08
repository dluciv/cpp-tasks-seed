#include "base85ed.h"
#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <algorithm>
#include <array>

namespace
{
const char ALPHABET[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

int char_index(char c)
{
    const char* pos = strchr(ALPHABET, c);
    if (!pos)
    {
        return -1;
    }
    return static_cast<int>(pos - ALPHABET);
}

std::array<char, 5> pack_block(const uint8_t src[4])
{
    uint32_t val = (static_cast<uint32_t>(src[0]) << 24) |
                   (static_cast<uint32_t>(src[1]) << 16) |
                   (static_cast<uint32_t>(src[2]) << 8)  |
                   static_cast<uint32_t>(src[3]);

    std::array<char, 5> dst;
    for (int i = 4; i >= 0; --i)
    {
        dst[i] = ALPHABET[val % 85];
        val /= 85;
    }
    return dst;
}
}

std::vector<uint8_t> base85::encode(const std::vector<uint8_t>& bytes)
{
    std::vector<uint8_t> res;
    size_t i = 0;
    for (; i + 4 <= bytes.size(); i += 4)
    {
        uint8_t block[4] = {bytes[i], bytes[i + 1], bytes[i + 2], bytes[i + 3]};
        auto buf = pack_block(block);
        res.insert(res.end(), buf.begin(), buf.end());
    }
    size_t rem = bytes.size() - i;
    if (rem > 0)
    {
        uint8_t tail[4] = {};
        std::memcpy(tail, &bytes[i], rem);
        auto buf = pack_block(tail);
        res.insert(res.end(), buf.begin(), buf.begin() + rem + 1);
    }
    return res;
}

std::vector<uint8_t> base85::decode(const std::vector<uint8_t>& input)
{
    std::vector<uint8_t> result;
    size_t len = input.size();

    std::vector<char> cleaned;
    cleaned.reserve(len);
    for (uint8_t b : input)
    {
        char c = static_cast<char>(b);
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\0')
        {
            continue;
        }
        cleaned.push_back(c);
    }

    size_t clean_len = cleaned.size();
    if (clean_len == 0) return {};

    size_t pos = 0;
    while (pos < clean_len)
    {
        int got = 0;
        uint32_t val = 0;

        for (int j = 0; j < 5 && (pos + j) < clean_len; ++j)
        {
            int digit = char_index(cleaned[pos + j]);
            if (digit == -1)
            {
                throw std::runtime_error("Invalid Base85 character");
            }
            if (val > (UINT32_MAX - digit) / 85)
            {
                throw std::runtime_error("Base85 overflow");
            }
            val = val * 85 + static_cast<uint32_t>(digit);
            got++;
        }

        int missing = 5 - got;
        if (missing > 0)
        {
            for (int k = 0; k < missing; ++k)
            {
                if (val > UINT32_MAX / 85)
                {
                    throw std::runtime_error("Base85 overflow during padding");
                }
                val *= 85;
            }

            int bytes_out = got - 1;
            int zero_bytes = 4 - bytes_out;

            if (zero_bytes > 0)
            {
                uint32_t M = 1;
                for (int z = 0; z < zero_bytes; ++z)
                {
                    M *= 256;
                }
                uint32_t rem = val % M;
                uint32_t half = M / 2;
                if (rem >= half)
                {
                    if (val > UINT32_MAX - (M - rem))
                    {
                        val = (val / M) * M;
                    }
                    else
                    {
                        val = val + (M - rem);
                    }
                }
                else
                {
                    val = val - rem;
                }
            }

            int add = got - 1;
            if (add < 0)
            {
                add = 0;
            }

            for (int b = 0; b < add; ++b)
            {
                result.push_back(static_cast<uint8_t>((val >> 24) & 0xFF));
                val <<= 8;
            }
        }
        else
        {
            uint8_t bytes[4];
            bytes[0] = static_cast<uint8_t>((val >> 24) & 0xFF);
            bytes[1] = static_cast<uint8_t>((val >> 16) & 0xFF);
            bytes[2] = static_cast<uint8_t>((val >> 8) & 0xFF);
            bytes[3] = static_cast<uint8_t>(val & 0xFF);
            result.insert(result.end(), bytes, bytes + 4);
        }

        pos += got;
    }

    return result;
}
