#include "base85ed.h"

#include <stdexcept>
#include <string>

namespace
{
    const char* ALPHABET =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "!#$%&()*+-;<=>?@^_`{|}~";

    int decode_char(uint8_t c)
    {
        for (int i = 0; i < 85; ++i)
        {
            if (ALPHABET[i] == c)
                return i;
        }
        return -1;
    }
}

std::vector<uint8_t> base85::encode(const std::vector<uint8_t>& bytes)
{
    std::vector<uint8_t> out;

    size_t i = 0;

    while (i < bytes.size())
    {
        uint32_t value = 0;
        size_t remain = bytes.size() - i;
        size_t chunk = remain >= 4 ? 4 : remain;

        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;

            if (j < chunk)
                value |= bytes[i + j];
        }

        char encoded[5];

        for (int k = 4; k >= 0; --k)
        {
            encoded[k] = ALPHABET[value % 85];
            value /= 85;
        }

        for (size_t k = 0; k < chunk + 1; ++k)
        {
            out.push_back(encoded[k]);
        }

        i += chunk;
    }

    return out;
}

std::vector<uint8_t> base85::decode(const std::vector<uint8_t>& b85str)
{
    std::vector<uint8_t> out;

    size_t i = 0;

    while (i < b85str.size())
    {
        size_t remain = b85str.size() - i;
        size_t chunk = remain >= 5 ? 5 : remain;

        uint32_t value = 0;

        for (size_t j = 0; j < 5; ++j)
        {
            value *= 85;

            if (j < chunk)
            {
                int d = decode_char(b85str[i + j]);

                if (d < 0)
                    throw std::runtime_error("Invalid Base85 character");

                value += d;
            }
            else
            {
                value += 84;
            }
        }

        uint8_t decoded[4];

        for (int k = 3; k >= 0; --k)
        {
            decoded[k] = value & 0xFF;
            value >>= 8;
        }

        for (size_t k = 0; k < chunk - 1; ++k)
        {
            out.push_back(decoded[k]);
        }

        i += chunk;
    }

    return out;
}
