#include <gtest/gtest.h>

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char * >> short_cases =
{
    { "",      ""      },
    { "F#",    "1"     },
    { "F){",   "12"    },
    { "F)}j",  "123"   },
    { "F)}kW", "1234"  }
};

static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(
               s,
               s + std::string(s).size()
           );
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

TEST(Base85RoundTrip, DifferentLengths)
{
    const std::vector<std::vector<uint8_t>> cases =
    {
        cstr2v(""),
        cstr2v("a"),
        cstr2v("ab"),
        cstr2v("abc"),
        cstr2v("abcd"),
        cstr2v("abcde"),
        cstr2v("abcdef"),
        cstr2v("abcdefg"),
        cstr2v("abcdefgh"),
        cstr2v("hello"),
        cstr2v("hello world"),
        cstr2v("The quick brown fox jumps over the lazy dog")
    };

    for (const auto &data : cases)
    {
        EXPECT_EQ(base85::decode(base85::encode(data)), data);
    }
}

TEST(Base85RoundTrip, BinaryData)
{
    const std::vector<uint8_t> data =
    {
        0x00, 0x01, 0x02, 0x03,
        0x7F, 0x80, 0xFE, 0xFF,
        0x00, 0x10, 0x20, 0x30
    };

    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, AllByteValues)
{
    std::vector<uint8_t> data;

    for (int i = 0; i <= 255; ++i)
    {
        data.push_back(static_cast<uint8_t>(i));
    }

    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Decode, InvalidLength)
{
    EXPECT_THROW(base85::decode(cstr2v("F")), std::invalid_argument);
}

TEST(Base85Decode, InvalidCharacter)
{
    EXPECT_THROW(base85::decode(cstr2v("F\"")), std::invalid_argument);
}