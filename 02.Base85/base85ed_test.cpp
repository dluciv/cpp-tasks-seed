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

const std::vector<std::pair<const char*, const char*>> medium_cases = {
    { "F)}kWH2",          "12345"      },
    { "F)}kWH8u",         "123456"     },
    { "F)}kWH8wW",        "1234567"    },
    { "F)}kWH8wXm",       "12345678"   },
    { "F)}kWH8wXmIR",     "123456789"  },
    { "F)}kWH8wXmIWP",    "1234567890" },
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

TEST(Base85MediumEncode, MediumEncodes)
{
    for (const auto &p : medium_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

TEST(Base85MediumDecode, MediumDecodes)
{
    for (const auto &p : medium_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

TEST(Base85RoundTrip_Short, EncodeDecodeShort)
{
    for (const auto &p : short_cases)
    {
        auto original = cstr2v(p.second);
        auto result = base85::decode(base85::encode(original));
        EXPECT_EQ(result, original);
    }
}

TEST(Base85RoundTrip_Medium, EncodeDecodeMedium)
{
    for (const auto &p : medium_cases)
    {
        auto original = cstr2v(p.second);
        auto result = base85::decode(base85::encode(original));
        EXPECT_EQ(result, original);
    }
}

TEST(Base85DecodeError, InvalidSymbol)
{
    std::vector<uint8_t> invalid = cstr2v("F#\\");
    EXPECT_THROW(base85::decode(invalid), std::runtime_error);
}
