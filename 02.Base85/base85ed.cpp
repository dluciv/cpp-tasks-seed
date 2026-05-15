#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>

#include "base85ed.h"

namespace base85
{

static const char b85chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static int get_b85_value(uint8_t c)
{
    for (int i = 0; i < 85; ++i)
    {
        if (b85chars[i] == c) return i;
    }
    return -1;
}

std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;
    size_t i = 0;

    while (i < bytes.size())
    {
        uint32_t val = 0;
        size_t chunk_size = 0;

        for (int j = 0; j < 4; ++j)
        {
            val <<= 8;
            if (i < bytes.size())
            {
                val |= bytes[i++];
                chunk_size++;
            }
        }

        if (chunk_size == 0) break;

        uint8_t chunk[5];
        for (int j = 4; j >= 0; --j)
        {
            chunk[j] = b85chars[val % 85];
            val /= 85;
        }

        for (size_t j = 0; j <= chunk_size; ++j)
        {
            result.push_back(chunk[j]);
        }
    }
    return result;
}

std::vector<uint8_t> decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;

    std::vector<uint8_t> filtered;
    for (uint8_t c : b85str)
    {
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t') continue;
        if (get_b85_value(c) == -1) throw std::invalid_argument("Invalid Base85 character");
        filtered.push_back(c);
    }

    size_t i = 0;
    while (i < filtered.size())
    {
        uint64_t val = 0;
        size_t chunk_size = 0;

        for (int j = 0; j < 5; ++j)
        {
            if (i < filtered.size())
            {
                val = val * 85 + get_b85_value(filtered[i++]);
                chunk_size++;
            }
            else
            {
                val = val * 85 + 84;
            }
        }

        if (chunk_size == 1)
        {
            throw std::invalid_argument("Invalid Base85 sequence length");
        }
        if (chunk_size == 0) break;

        if (val > 0xFFFFFFFF)
        {
            throw std::invalid_argument("Base85 decoded value overflows 32 bits");
        }

        uint8_t decoded[4];
        for (int j = 3; j >= 0; --j)
        {
            decoded[j] = val & 0xFF;
            val >>= 8;
        }

        for (size_t j = 0; j < chunk_size - 1; ++j)
        {
            result.push_back(decoded[j]);
        }
    }
    return result;
}

}