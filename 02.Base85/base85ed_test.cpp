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

TEST(Base85Advanced, DecodeIgnoresWhitespace)
{
    const char* messy_input = " F) \n }k \t W \r ";
    EXPECT_EQ(base85::decode(cstr2v(messy_input)), cstr2v("1234"));
}

TEST(Base85Advanced, InvalidCharactersThrow)
{
    EXPECT_THROW(base85::decode(cstr2v("F)ыkW")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("F),kW")), std::invalid_argument);
}

TEST(Base85Advanced, InvalidLengthsThrow)
{
    EXPECT_THROW(base85::decode(cstr2v("F")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("000000")), std::invalid_argument);
}

TEST(Base85Advanced, OverflowThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("~~~~~")), std::invalid_argument);
}