#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "base85ed.h"

namespace
{
const char *BASE85_ALPHABET =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

int char_to_value(uint8_t c)
{
    for (int i = 0; i < 85; ++i)
    {
        if (static_cast<uint8_t>(BASE85_ALPHABET[i]) == c)
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

    size_t i = 0;
    while (i + 4 <= bytes.size())
    {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(bytes[i]) << 24;
        value |= static_cast<uint32_t>(bytes[i + 1]) << 16;
        value |= static_cast<uint32_t>(bytes[i + 2]) << 8;
        value |= static_cast<uint32_t>(bytes[i + 3]);

        uint8_t block[5];
        for (int j = 4; j >= 0; --j)
        {
            block[j] = static_cast<uint8_t>(BASE85_ALPHABET[value % 85]);
            value /= 85;
        }

        for (int j = 0; j < 5; ++j)
        {
            result.push_back(block[j]);
        }

        i += 4;
    }

    size_t rest = bytes.size() - i;
    if (rest > 0)
    {
        uint32_t value = 0;

        value |= static_cast<uint32_t>(bytes[i]) << 24;
        if (rest >= 2)
        {
            value |= static_cast<uint32_t>(bytes[i + 1]) << 16;
        }
        if (rest >= 3)
        {
            value |= static_cast<uint32_t>(bytes[i + 2]) << 8;
        }

        uint8_t block[5];
        for (int j = 4; j >= 0; --j)
        {
            block[j] = static_cast<uint8_t>(BASE85_ALPHABET[value % 85]);
            value /= 85;
        }

        for (size_t j = 0; j < rest + 1; ++j)
        {
            result.push_back(block[j]);
        }
    }

    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;

    size_t i = 0;
    while (i < b85str.size())
    {
        size_t left = b85str.size() - i;

        if (left >= 5)
        {
            uint32_t value = 0;

            for (int j = 0; j < 5; ++j)
            {
                int digit = char_to_value(b85str[i + j]);
                if (digit == -1)
                {
                    throw std::runtime_error("invalid base85 character");
                }
                value = value * 85 + static_cast<uint32_t>(digit);
            }

            result.push_back(static_cast<uint8_t>((value >> 24) & 255));
            result.push_back(static_cast<uint8_t>((value >> 16) & 255));
            result.push_back(static_cast<uint8_t>((value >> 8) & 255));
            result.push_back(static_cast<uint8_t>(value & 255));

            i += 5;
        }
        else
        {
            if (left == 1)
            {
                throw std::runtime_error("invalid base85 tail");
            }

            uint32_t value = 0;

            for (size_t j = 0; j < left; ++j)
            {
                int digit = char_to_value(b85str[i + j]);
                if (digit == -1)
                {
                    throw std::runtime_error("invalid base85 character");
                }
                value = value * 85 + static_cast<uint32_t>(digit);
            }

            for (size_t j = left; j < 5; ++j)
            {
                value = value * 85 + 84;
            }

            uint8_t block[4];
            block[0] = static_cast<uint8_t>((value >> 24) & 255);
            block[1] = static_cast<uint8_t>((value >> 16) & 255);
            block[2] = static_cast<uint8_t>((value >> 8) & 255);
            block[3] = static_cast<uint8_t>(value & 255);

            for (size_t j = 0; j < left - 1; ++j)
            {
                result.push_back(block[j]);
            }

            break;
        }
    }

    return result;
}