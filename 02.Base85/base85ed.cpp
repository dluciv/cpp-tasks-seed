#include "base85ed.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace base85
{

static const char alphabet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static int8_t reverse_table[256];

static void init_reverse_table()
{
    static bool initialized = false;
    if (initialized)
    {
        return;
    }

    std::fill(std::begin(reverse_table), std::end(reverse_table), -1);

    for (int i = 0; i < 85; ++i)
    {
        reverse_table[static_cast<uint8_t>(alphabet[i])] = static_cast<int8_t>(i);
    }

    initialized = true;
}

std::vector<uint8_t> encode(const std::vector<uint8_t>& input)
{
    std::vector<uint8_t> out;
    out.reserve((input.size() * 5) / 4 + 5);

    size_t i = 0;

    while (i < input.size())
    {
        uint32_t value = 0;
        int bytes = 0;

        for (int j = 0; j < 4; ++j)
        {
            value <<= 8;
            if (i < input.size())
            {
                value |= input[i];
                i++;
                bytes++;
            }
        }

        char block[5];
        for (int j = 4; j >= 0; --j)
        {
            block[j] = alphabet[value % 85];
            value /= 85;
        }

        for (int j = 0; j < bytes + 1; ++j)
        {
            out.push_back(static_cast<uint8_t>(block[j]));
        }
    }

    return out;
}

std::vector<uint8_t> decode(const std::vector<uint8_t>& input)
{
    init_reverse_table();

    std::vector<uint8_t> out;
    std::vector<uint8_t> clean;

    for (uint8_t c : input)
    {
        if (!std::isspace(c))
        {
            clean.push_back(c);
        }
    }

    size_t i = 0;

    while (i < clean.size())
    {
        unsigned long long value = 0;
        int count = 0;

        for (int j = 0; j < 5; ++j)
        {
            if (i < clean.size())
            {
                uint8_t c = clean[i];
                i++;

                int8_t v = reverse_table[c];
                if (v == -1)
                {
                    throw std::runtime_error("Invalid Base85 character");
                }

                value = value * 85 + static_cast<unsigned>(v);
                count++;
            }
            else
            {
                value = value * 85 + 84;
            }
        }

        if (value > 0xFFFFFFFFULL)
        {
            throw std::runtime_error("Invalid Base85 block");
        }

        uint32_t decoded = static_cast<uint32_t>(value);
        uint8_t bytes[4];

        for (int j = 3; j >= 0; --j)
        {
            bytes[j] = decoded & 0xFF;
            decoded >>= 8;
        }

        for (int j = 0; j < count - 1; ++j)
        {
            out.push_back(bytes[j]);
        }

        if (count < 5)
        {
            break;
        }
    }

    return out;
}

} // namespace base85
