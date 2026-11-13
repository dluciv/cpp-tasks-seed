#include <gtest/gtest.h>

#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "base85ed.h"

namespace
{
std::vector<std::uint8_t> as_bytes(const std::string& text)
{
    return {text.begin(), text.end()};
}
}

TEST(Base85, KnownEncodingAndDecoding)
{
    const std::vector<std::pair<std::string, std::string>> cases = {
        {"", ""},
        {"1", "F#"},
        {"12", "F){"},
        {"123", "F)}j"},
        {"1234", "F)}kW"},
        {"hello", "Xk~0{Zv"},
        {"hello world", "Xk~0{Zy<MXa%^M"}
    };

    for (const auto& item : cases)
    {
        SCOPED_TRACE(item.first);

        EXPECT_EQ(
            base85::encode(as_bytes(item.first)),
            as_bytes(item.second)
        );

        EXPECT_EQ(
            base85::decode(as_bytes(item.second)),
            as_bytes(item.first)
        );
    }
}

TEST(Base85, BinaryData)
{
    const std::vector<std::uint8_t> input = {
        0, 0, 0, 0, 255, 255, 255, 255
    };

    const auto encoded = as_bytes("00000|NsC0");

    EXPECT_EQ(base85::encode(input), encoded);
    EXPECT_EQ(base85::decode(encoded), input);
}

TEST(Base85, AllByteValues)
{
    std::vector<std::uint8_t> input;

    for (unsigned int value = 0; value < 256; ++value)
    {
        input.push_back(static_cast<std::uint8_t>(value));
    }

    EXPECT_EQ(
        base85::decode(base85::encode(input)),
        input
    );
}

TEST(Base85, RandomDataOfDifferentLengths)
{
    std::mt19937 engine(42);
    std::uniform_int_distribution<int> distribution(0, 255);

    for (std::size_t length : {
        0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u,
        8u, 9u, 16u, 31u, 32u, 33u,
        100u, 257u, 1024u, 8193u, 65537u
    })
    {
        SCOPED_TRACE(length);

        std::vector<std::uint8_t> input(length);

        for (auto& byte : input)
        {
            byte = static_cast<std::uint8_t>(
                distribution(engine)
            );
        }

        EXPECT_EQ(
            base85::decode(base85::encode(input)),
            input
        );
    }
}

TEST(Base85, RejectsInvalidCharacters)
{
    EXPECT_THROW(
        base85::decode(as_bytes("0000 ")),
        std::invalid_argument
    );

    EXPECT_THROW(
        base85::decode(as_bytes("0000\n")),
        std::invalid_argument
    );
}

TEST(Base85, RejectsOverflow)
{
    EXPECT_THROW(
        base85::decode(as_bytes("~~~~~")),
        std::overflow_error
    );
}