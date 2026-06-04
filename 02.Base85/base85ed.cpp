#include <array>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "base85ed.h"

namespace
{

const std::array<uint8_t, 85> ALPHABET =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z',
    '!', '#', '$', '%', '&', '(', ')', '*', '+', '-',
    ';', '<', '=', '>', '?', '@', '^', '_', '`', '{',
    '|', '}', '~'
};

std::array<int, 256> make_reverse_alphabet()
{
    std::array<int, 256> reverse{};

    reverse.fill(-1);

    for (size_t i = 0; i < ALPHABET.size(); ++i)
    {
        reverse[ALPHABET[i]] = static_cast<int>(i);
    }

    return reverse;
}

std::array<uint8_t, 5> encode_block(uint32_t value)
{
    std::array<uint8_t, 5> result{};

    for (int i = 4; i >= 0; --i)
    {
        result[i] = ALPHABET[value % 85];
        value /= 85;
    }

    return result;
}

std::array<uint8_t, 4> decode_block(const std::array<uint8_t, 5>& block)
{
    static const std::array<int, 256> reverse = make_reverse_alphabet();

    uint64_t value = 0;

    for (uint8_t symbol : block)
    {
        int digit = reverse[symbol];

        if (digit == -1)
        {
            throw std::invalid_argument("invalid Base85 character");
        }

        value = value * 85 + static_cast<uint64_t>(digit);
    }

    if (value > UINT32_MAX)
    {
        throw std::invalid_argument("invalid Base85 block");
    }

    uint32_t value32 = static_cast<uint32_t>(value);

    return
    {
        static_cast<uint8_t>((value32 >> 24) & 0xFF),
        static_cast<uint8_t>((value32 >> 16) & 0xFF),
        static_cast<uint8_t>((value32 >> 8) & 0xFF),
        static_cast<uint8_t>(value32 & 0xFF)
    };
}

}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;

    result.reserve((bytes.size() + 3) / 4 * 5);

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        size_t block_size = bytes.size() - i;

        if (block_size > 4)
        {
            block_size = 4;
        }

        uint32_t value = 0;

        for (size_t j = 0; j < 4; ++j)
        {
            value <<= 8;

            if (j < block_size)
            {
                value |= static_cast<uint32_t>(bytes[i + j]);
            }
        }

        std::array<uint8_t, 5> encoded_block = encode_block(value);

        for (size_t j = 0; j < block_size + 1; ++j)
        {
            result.push_back(encoded_block[j]);
        }
    }

    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    std::vector<uint8_t> result;

    result.reserve((b85str.size() + 4) / 5 * 4);

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        size_t block_size = b85str.size() - i;

        if (block_size > 5)
        {
            block_size = 5;
        }

        if (block_size == 1)
        {
            throw std::invalid_argument("invalid Base85 length");
        }

        std::array<uint8_t, 5> block{};

        for (size_t j = 0; j < block_size; ++j)
        {
            block[j] = b85str[i + j];
        }

        for (size_t j = block_size; j < 5; ++j)
        {
            block[j] = '~';
        }

        std::array<uint8_t, 4> decoded_block = decode_block(block);

        size_t decoded_size = 4;

        if (block_size < 5)
        {
            decoded_size = block_size - 1;
        }

        for (size_t j = 0; j < decoded_size; ++j)
        {
            result.push_back(decoded_block[j]);
        }
    }

    return result;
}