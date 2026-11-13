#include "base85ed.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace
{
constexpr char alphabet[] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

const std::array<int, 256>& decode_table()
{
    static const auto table = []
    {
        std::array<int, 256> result{};
        result.fill(-1);

        for (int index = 0; index < 85; ++index)
        {
            result[static_cast<unsigned char>(alphabet[index])] = index;
        }

        return result;
    }();

    return table;
}
}

std::vector<std::uint8_t> base85::encode(const std::vector<std::uint8_t>& bytes)
{
    std::vector<std::uint8_t> result;

    result.reserve(
        (bytes.size() / 4) * 5 +
        (bytes.size() % 4 ? bytes.size() % 4 + 1 : 0)
    );

    for (std::size_t pos = 0; pos < bytes.size();)
    {
        const std::size_t count =
            std::min(std::size_t{4}, bytes.size() - pos);

        std::uint32_t block = 0;

        for (std::size_t i = 0; i < count; ++i)
        {
            block = (block << 8) | bytes[pos + i];
        }

        block <<= 8 * (4 - count);

        std::array<std::uint8_t, 5> encoded{};

        for (int i = 4; i >= 0; --i)
        {
            encoded[static_cast<std::size_t>(i)] =
                static_cast<std::uint8_t>(alphabet[block % 85]);

            block /= 85;
        }

        const std::size_t output_length =
            count == 4 ? 5 : count + 1;

        result.insert(
            result.end(),
            encoded.begin(),
            encoded.begin() + output_length
        );

        pos += count;
    }

    return result;
}

std::vector<std::uint8_t> base85::decode(
    const std::vector<std::uint8_t>& b85str)
{
    std::vector<std::uint8_t> result;

    result.reserve(
        (b85str.size() / 5) * 4 +
        (b85str.size() % 5 ? b85str.size() % 5 - 1 : 0)
    );

    const auto& table = decode_table();

    for (std::size_t pos = 0; pos < b85str.size();)
    {
        const std::size_t count =
            std::min(std::size_t{5}, b85str.size() - pos);

        std::uint64_t block = 0;

        for (std::size_t i = 0; i < 5; ++i)
        {
            const std::uint8_t symbol = i < count
                ? b85str[pos + i]
                : static_cast<std::uint8_t>('~');

            const int digit = table[symbol];

            if (digit < 0)
            {
                throw std::invalid_argument(
                    "Invalid Base85 character"
                );
            }

            block = block * 85 + static_cast<std::uint64_t>(digit);
        }

        if (block > 0xFFFFFFFFULL)
        {
            throw std::overflow_error(
                "Base85 block exceeds 32 bits"
            );
        }

        const std::size_t output_length =
            count == 5 ? 4 : count - 1;

        for (std::size_t i = 0; i < output_length; ++i)
        {
            result.push_back(
                static_cast<std::uint8_t>(
                    block >> (24 - 8 * i)
                )
            );
        }

        pos += count;
    }

    return result;
}