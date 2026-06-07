#include <gtest/gtest.h>

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string.h>

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
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
}

// Тесты encode
TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

// Тесты decode
TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85Exceptions, InvalidCharacters)
{
    EXPECT_THROW(base85::decode(cstr2v("F*")), std::runtime_error);
    EXPECT_THROW(base85::decode(cstr2v("F ")), std::runtime_error);
}

TEST(Base85Exceptions, IsolatedCharacter)
{
    EXPECT_THROW(base85::decode(cstr2v("F")), std::runtime_error);
    EXPECT_THROW(base85::decode(cstr2v("12345F")), std::runtime_error);
}

TEST(Base85Exceptions, Overflow)
{
    EXPECT_THROW(base85::decode(cstr2v("~~~~~")), std::runtime_error);
}
