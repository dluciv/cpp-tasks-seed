#include <array>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

#include "base85ed.h"

namespace
{

constexpr std::array<uint8_t, 85> ALPHABET =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
    'y', 'z', '!', '#', '$', '%', '&', '(', ')', '*',
    '+', '-', ';', '<', '=', '>', '?', '@', '^', '_',
    '`', '{', '|', '}', '~'
};

std::array<int16_t, 256> make_decode_table()
{
    std::array<int16_t, 256> table{};
    table.fill(-1);

    for (size_t i = 0; i < ALPHABET.size(); ++i)
    {
        table[ALPHABET[i]] = static_cast<int16_t>(i);
    }

    return table;
}

uint32_t read_u32_be(std::vector<uint8_t> const &bytes, size_t pos, size_t count)
{
    uint32_t value = 0;

    for (size_t i = 0; i < 4; ++i)
    {
        value <<= 8U;
        if (i < count)
        {
            value |= bytes[pos + i];
        }
    }

    return value;
}

void append_u32_be(std::vector<uint8_t> &out, uint32_t value, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        size_t shift = 24U - 8U * i;
        out.push_back(static_cast<uint8_t>((value >> shift) & 0xFFU));
    }
}

} // namespace

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;
    out.reserve((bytes.size() + 3U) / 4U * 5U);

    for (size_t pos = 0; pos < bytes.size(); pos += 4U)
    {
        size_t block_size = std::min<size_t>(4U, bytes.size() - pos);
        uint32_t value = read_u32_be(bytes, pos, block_size);
        std::array<uint8_t, 5> block{};

        for (size_t i = block.size(); i > 0; --i)
        {
            block[i - 1U] = ALPHABET[value % 85U];
            value /= 85U;
        }

        out.insert(out.end(), block.begin(), block.begin() + block_size + 1U);
    }

    return out;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    static const std::array<int16_t, 256> decode_table = make_decode_table();

    if (b85str.size() % 5U == 1U)
    {
        throw std::invalid_argument("invalid Base85 length");
    }

    std::vector<uint8_t> out;
    out.reserve(b85str.size() / 5U * 4U + 4U);

    for (size_t pos = 0; pos < b85str.size(); pos += 5U)
    {
        size_t block_size = std::min<size_t>(5U, b85str.size() - pos);
        uint64_t value = 0;

        for (size_t i = 0; i < 5U; ++i)
        {
            uint8_t symbol = i < block_size ? b85str[pos + i] : static_cast<uint8_t>('~');
            int16_t digit = decode_table[symbol];

            if (digit < 0)
            {
                throw std::invalid_argument("invalid Base85 character");
            }

            value = value * 85U + static_cast<uint64_t>(digit);
        }

        if (value > std::numeric_limits<uint32_t>::max())
        {
            throw std::invalid_argument("Base85 value overflow");
        }

        append_u32_be(out, static_cast<uint32_t>(value), block_size - 1U);
    }

    return out;
}
