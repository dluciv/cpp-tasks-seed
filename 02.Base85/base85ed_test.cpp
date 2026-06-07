#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
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

const std::vector<std::pair<const char *, const char * >> medium_cases =
{
    { "F)}kWH2",          "12345"      },
    { "F)}kWH8u",         "123456"     },
    { "F)}kWH8wW",        "1234567"    },
    { "F)}kWH8wXm",       "12345678"   },
    { "F)}kWH8wXmIR",     "123456789"  },
    { "F)}kWH8wXmIWP",    "1234567890" },
};

const std::vector<std::pair<const char *, const char * >> long_cases =
{
    {
        "RA^-&adl~9Yan8BZ+C7WW^Z^PYISXJb0BYaWpW^NXk{R5VS0HWWN&8",
        "The quick brown fox jumps over the lazy dog"
    },
    {
        "P+?<hAZ>XdVsCgLcWHEJAZBTHWguj4dSz}PY-w?IZ*m}Nb!T%fAVhC&Wg!",
        "Pack my box with five dozen liquor jugs. Done!"
    },
};

const std::vector<std::pair<std::vector<uint8_t>, std::vector<uint8_t> >> edge_cases =
{
    { {0x30, 0x30},                         {0x00}                   },
    { {0x30, 0x30, 0x30, 0x30, 0x30},       {0x00, 0x00, 0x00, 0x00} },
    { {0x7b, 0x7b},                         {0xff}                   },
    { {0x7c, 0x4e, 0x73, 0x43, 0x30},       {0xff, 0xff, 0xff, 0xff} },
    { {0x30, 0x52, 0x49, 0x36, 0x30},       {0x00, 0xff, 0x00, 0xff} },
    { {0x66, 0x50, 0x73, 0x52, 0x38},       {0x80, 0x81, 0x82, 0x83} },
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

TEST(Base85MediumEncode, MediumEncodes)
{
    for (const auto &p : medium_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85LongEncode, LongEncodes)
{
    for (const auto &p : long_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85EdgeEncode, EdgeEncodes)
{
    for (const auto &p : edge_cases)
    {
        EXPECT_EQ(base85::encode(p.second), p.first);
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

TEST(Base85MediumDecode, MediumDecodes)
{
    for (const auto &p : medium_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85LongDecode, LongDecodes)
{
    for (const auto &p : long_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85EdgeDecode, EdgeDecodes)
{
    for (const auto &p : edge_cases)
    {
        EXPECT_EQ(base85::decode(p.first), p.second);
    }
}
