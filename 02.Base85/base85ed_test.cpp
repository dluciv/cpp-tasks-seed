#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(s, s + std::strlen(s));
}

TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85Advanced, EmptyData)
{
    std::vector<uint8_t> input = {};
    EXPECT_EQ(base85::encode(input), std::vector<uint8_t> {});
    EXPECT_EQ(base85::decode({}), std::vector<uint8_t> {});
}

TEST(Base85Advanced, SingleByteZero)
{
    std::vector<uint8_t> input = {0x00};
    auto encoded = base85::encode(input);
    EXPECT_EQ(encoded.size(), 2);
    EXPECT_EQ(base85::decode(encoded), input);
}

TEST(Base85Advanced, AllZeros)
{
    std::vector<uint8_t> input(100, 0x00);
    EXPECT_EQ(base85::decode(base85::encode(input)), input);
}

TEST(Base85Advanced, AllOnes)
{
    std::vector<uint8_t> input(100, 0xFF);
    EXPECT_EQ(base85::decode(base85::encode(input)), input);
}

TEST(Base85Advanced, AlternatingPattern)
{
    std::vector<uint8_t> input;
    for(int i = 0; i < 100; ++i)
    {
        input.push_back(i % 2 == 0 ? 0xAA : 0x55);
    }
    EXPECT_EQ(base85::decode(base85::encode(input)), input);
}

TEST(Base85Advanced, LargePayload)
{
    std::vector<uint8_t> input;
    input.reserve(10000);
    for(int i = 0; i < 10000; ++i)
    {
        input.push_back(static_cast<uint8_t>(i % 256));
    }
    auto encoded = base85::encode(input);
    auto decoded = base85::decode(encoded);
    EXPECT_EQ(decoded, input);
}

TEST(Base85Exceptions, InvalidLength)
{
    std::vector<uint8_t> invalid_input = {'A'};
    EXPECT_THROW(base85::decode(invalid_input), std::invalid_argument);
}

TEST(Base85Exceptions, InvalidCharacters)
{
    std::vector<uint8_t> invalid_input = {'0', '0', '0', '0', ' '};
    EXPECT_THROW(base85::decode(invalid_input), std::invalid_argument);
}