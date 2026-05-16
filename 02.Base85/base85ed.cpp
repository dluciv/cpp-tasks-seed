#include <vector>
#include <cstdint>
#include <stdexcept>

#include "base85ed.h"

namespace
{
const char *B85_ALPHABET =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

int find_b85_char(uint8_t c)
{
    for (int i = 0; i < 85; ++i)
    {
        if (static_cast<uint8_t>(B85_ALPHABET[i]) == c)
        {
            return i;
        }
    }

    return -1;
}
} // namespace

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        uint32_t value = 0;
        size_t block_size = bytes.size() - i;
        if (block_size > 4)
        {
            block_size = 4;
        }

        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;
            if (j < block_size)
            {
                value += bytes[i + j];
            }
        }

        uint8_t encoded[5];
        for (int j = 4; j >= 0; --j)
        {
            encoded[j] = B85_ALPHABET[value % 85];
            value /= 85;
        }

        size_t out_size = block_size;
        if (block_size != 0)
        {
            out_size += 1;
        }
        for (size_t j = 0; j < out_size; ++j)
        {
            result.push_back(encoded[j]);
        }
    }

    return result;
}


std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    if (b85str.size() % 5 == 1)
    {
        throw std::runtime_error("bad base85 length");
    }

    std::vector<uint8_t> result;

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        size_t block_size = b85str.size() - i;
        if (block_size > 5)
        {
            block_size = 5;
        }

        uint64_t value = 0;
        for (size_t j = 0; j < 5; ++j)
        {
            int digit = 84;
            if (j < block_size)
            {
                digit = find_b85_char(b85str[i + j]);
                if (digit < 0)
                {
                    throw std::runtime_error("bad base85 character");
                }
            }
            value = value * 85 + static_cast<uint64_t>(digit);
        }

        uint8_t decoded[4];
        for (int j = 3; j >= 0; --j)
        {
            decoded[j] = value & 255;
            value >>= 8;
        }

        size_t out_size = 4;
        if (block_size != 5)
        {
            out_size = block_size - 1;
        }
        for (size_t j = 0; j < out_size; ++j)
        {
            result.push_back(decoded[j]);
        }
    }

    return result;
}
