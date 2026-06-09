#include <gtest/gtest.h>

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string.h>
#include <string>

#include "base85ed.h"

const std::vector<std::pair<const char *, const char *>> short_cases =
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

TEST(Base85Encode, Empty)
{
    std::vector<uint8_t> data;
    std::vector<uint8_t> encoded = base85::encode(data);
    EXPECT_EQ(encoded, std::vector<uint8_t>());
}

TEST(Base85Decode, Empty)
{
    std::vector<uint8_t> data;
    std::vector<uint8_t> decoded = base85::decode(data);
    EXPECT_EQ(decoded, std::vector<uint8_t>());
}

TEST(Base85RoundTrip, OneByte)
{
    std::vector<uint8_t> data = cstr2v("1");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, TwoBytes)
{
    std::vector<uint8_t> data = cstr2v("12");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, ThreeBytes)
{
    std::vector<uint8_t> data = cstr2v("123");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, FourBytes)
{
    std::vector<uint8_t> data = cstr2v("1234");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, FiveBytes)
{
    std::vector<uint8_t> data = cstr2v("12345");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, ShortText)
{
    std::vector<uint8_t> data = cstr2v("hello");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, LongText)
{
    std::vector<uint8_t> data = cstr2v("Base85 test string for algorithms and data structures");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, WithSpaces)
{
    std::vector<uint8_t> data = cstr2v("a b c d e f g");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, WithPunctuation)
{
    std::vector<uint8_t> data = cstr2v("Hello, world! 12345.");
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, ZeroBytesInside)
{
    std::vector<uint8_t> data =
    {
        0, 1, 2, 3, 0, 4, 5, 0, 255
    };
    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85RoundTrip, AllByteValues)
{
    std::vector<uint8_t> data;
    for (int i = 0; i < 256; ++i)
    {
        data.push_back(static_cast<uint8_t>(i));
    }

    EXPECT_EQ(base85::decode(base85::encode(data)), data);
}

TEST(Base85Decode, InvalidTailLengthOne)
{
    std::vector<uint8_t> bad = cstr2v("0");
    EXPECT_THROW(base85::decode(bad), std::runtime_error);
}

TEST(Base85Decode, InvalidCharacterSpace)
{
    std::vector<uint8_t> bad = cstr2v("0000 ");
    EXPECT_THROW(base85::decode(bad), std::runtime_error);
}

TEST(Base85Decode, InvalidCharacterQuote)
{
    std::vector<uint8_t> bad = cstr2v("\"0000");
    EXPECT_THROW(base85::decode(bad), std::runtime_error);
}

TEST(Base85Decode, InvalidCharacterBackslash)
{
    std::vector<uint8_t> bad = cstr2v("\\0000");
    EXPECT_THROW(base85::decode(bad), std::runtime_error);
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