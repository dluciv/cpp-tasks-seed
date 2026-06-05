#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>

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
    return std::vector<uint8_t>(s, s + std::string(s).size());
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

// ТЕСТЫ

TEST(Base85SneakyTests, AllZeros)
{
    std::vector<uint8_t> zeros = {0, 0, 0, 0};
    EXPECT_EQ(base85::encode(zeros), cstr2v("00000"));
    EXPECT_EQ(base85::decode(cstr2v("00000")), zeros);
}

TEST(Base85SneakyTests, MaxValues)
{
    std::vector<uint8_t> max_bytes = {0xFF, 0xFF, 0xFF, 0xFF};
    EXPECT_EQ(base85::encode(max_bytes), cstr2v("|NsC0"));
    EXPECT_EQ(base85::decode(cstr2v("|NsC0")), max_bytes);
}

TEST(Base85SneakyTests, WhitespaceHandling)
{
    std::vector<uint8_t> expected = cstr2v("1234");
    std::vector<uint8_t> input_with_spaces = cstr2v(" F ) } k W \n \t ");
    EXPECT_EQ(base85::decode(input_with_spaces), expected);
}

TEST(Base85SneakyTests, InvalidCharactersThrow)
{
    EXPECT_THROW(base85::decode(cstr2v("F,}kW")), std::invalid_argument);
    EXPECT_THROW(base85::decode({0xFF}), std::invalid_argument);
}

TEST(Base85SneakyTests, OverflowThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("~~~~~")), std::invalid_argument);
}

TEST(Base85SneakyTests, InvalidLengthThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("F")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("F)}kWF")), std::invalid_argument);
}