#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <array>

#include "base85ed.h"

namespace base85
{

static constexpr char b85chars[] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

static constexpr std::array<uint32_t, 256> build_b85_table()
{
    std::array<uint32_t, 256> table{};
    for (int i = 0; i < 256; ++i) table[i] = 255;
    for (uint32_t i = 0; i < 85; ++i)
    {
        table[static_cast<uint8_t>(b85chars[i])] = i;
    }
    return table;
}

static constexpr auto dec_table = build_b85_table();

std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;
    out.reserve((bytes.size() + 3) / 4 * 5);

    size_t i = 0;
    while (i < bytes.size())
    {
        uint32_t acc = 0;
        size_t chunk_len = 0;

        for (int j = 0; j < 4; ++j)
        {
            acc <<= 8;
            if (i < bytes.size())
            {
                acc |= bytes[i++];
                chunk_len++;
            }
        }

        if (chunk_len == 0) break;

        uint32_t d[5];
        for (int j = 4; j >= 0; --j)
        {
            d[j] = acc % 85;
            acc /= 85;
        }

        for (size_t j = 0; j <= chunk_len; ++j)
        {
            out.push_back(b85chars[d[j]]);
        }
    }
    return out;
}

std::vector<uint8_t> decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> out;
    out.reserve((b85str.size() + 4) / 5 * 4);

    size_t i = 0;
    while (i < b85str.size())
    {
        uint64_t acc = 0;
        size_t chunk_len = 0;

        for (int j = 0; j < 5; ++j)
        {
            while (i < b85str.size())
            {
                uint8_t c = b85str[i];
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                {
                    i++;
                }
                else
                {
                    break;
                }
            }

            if (i < b85str.size())
            {
                uint8_t c = b85str[i++];
                uint32_t val = dec_table[c];
                if (val == 255) throw std::invalid_argument("Invalid Base85 character");
                acc = acc * 85 + val;
                chunk_len++;
            }
            else
            {
                acc = acc * 85 + 84;
            }
        }

        if (chunk_len == 0) break;
        if (chunk_len == 1) throw std::invalid_argument("Invalid Base85 chunk length (1 character)");
        if (acc > 0xFFFFFFFF) throw std::invalid_argument("Base85 value overflow");

        out.push_back(static_cast<uint8_t>((acc >> 24) & 0xFF));
        if (chunk_len > 2) out.push_back(static_cast<uint8_t>((acc >> 16) & 0xFF));
        if (chunk_len > 3) out.push_back(static_cast<uint8_t>((acc >> 8) & 0xFF));
        if (chunk_len > 4) out.push_back(static_cast<uint8_t>(acc & 0xFF));
    }
    return out;
}
}