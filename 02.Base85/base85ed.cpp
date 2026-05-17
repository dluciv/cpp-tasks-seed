#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <array>

#include "base85ed.h"

namespace base85
{

static const char ALPHABET[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static const uint32_t POW85[5] = {
    52200625,
    614125,
    7225,
    85,
    1
};

std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;
    if (bytes.empty()) return result;

    result.reserve((bytes.size() + 3) / 4 * 5);

    size_t i = 0;
    size_t len = bytes.size();

    for (; i + 4 <= len; i += 4)
    {
        uint32_t val = (static_cast<uint32_t>(bytes[i]) << 24) |
                       (static_cast<uint32_t>(bytes[i + 1]) << 16) |
                       (static_cast<uint32_t>(bytes[i + 2]) << 8) |
                       static_cast<uint32_t>(bytes[i + 3]);

        result.push_back(ALPHABET[val / POW85[0]]);
        result.push_back(ALPHABET[(val / POW85[1]) % 85]);
        result.push_back(ALPHABET[(val / POW85[2]) % 85]);
        result.push_back(ALPHABET[(val / POW85[3]) % 85]);
        result.push_back(ALPHABET[val % 85]);
    }

    if (i < len)
    {
        size_t rem = len - i;
        uint32_t val = 0;
        for (size_t j = 0; j < 4; ++j)
        {
            val <<= 8;
            if (j < rem)
            {
                val |= bytes[i + j];
            }
        }

        result.push_back(ALPHABET[val / POW85[0]]);
        if (rem >= 1) result.push_back(ALPHABET[(val / POW85[1]) % 85]);
        if (rem >= 2) result.push_back(ALPHABET[(val / POW85[2]) % 85]);
        if (rem >= 3) result.push_back(ALPHABET[(val / POW85[3]) % 85]);
    }

    return result;
}

std::vector<uint8_t> decode(std::vector<uint8_t> const &b85str)
{
    static const auto lookup = []()
    {
        std::array<int, 256> table;
        table.fill(-1);
        for (int i = 0; i < 85; ++i)
        {
            table[static_cast<unsigned char>(ALPHABET[i])] = i;
        }
        return table;
    }();

    std::vector<uint8_t> result;
    size_t len = b85str.size();
    if (len == 0) return result;

    result.reserve(len * 4 / 5);

    size_t i = 0;
    for (; i + 5 <= len; i += 5)
    {
        uint64_t val = 0;
        for (size_t j = 0; j < 5; ++j)
        {
            int code = lookup[b85str[i + j]];
            if (code == -1)
            {
                throw std::runtime_error("Invalid character in base85 string");
            }
            val += static_cast<uint64_t>(code) * POW85[j];
        }

        if (val > 0xFFFFFFFFU)
        {
            throw std::runtime_error("Base85 value overflow");
        }

        result.push_back((val >> 24) & 0xFF);
        result.push_back((val >> 16) & 0xFF);
        result.push_back((val >> 8) & 0xFF);
        result.push_back(val & 0xFF);
    }

    if (i < len)
    {
        size_t rem = len - i;
        if (rem == 1)
        {
            throw std::runtime_error("Invalid base85 string length");
        }

        uint64_t val = 0;
        for (size_t j = 0; j < 5; ++j)
        {
            int code = 84;
            if (j < rem)
            {
                code = lookup[b85str[i + j]];
                if (code == -1)
                {
                    throw std::runtime_error("Invalid character in base85 string");
                }
            }
            val += static_cast<uint64_t>(code) * POW85[j];
        }

        if (val > 0xFFFFFFFFU)
        {
            throw std::runtime_error("Base85 value overflow in padded block");
        }

        size_t bytes_to_keep = rem - 1;
        if (bytes_to_keep >= 1) result.push_back((val >> 24) & 0xFF);
        if (bytes_to_keep >= 2) result.push_back((val >> 16) & 0xFF);
        if (bytes_to_keep >= 3) result.push_back((val >> 8) & 0xFF);
    }

    return result;
}

}