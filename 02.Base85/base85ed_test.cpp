#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
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

TEST(Base85Encode, LongerKnownStrings)
{
    EXPECT_EQ(base85::encode(cstr2v("12345")), cstr2v("F)}kWH2"));
    EXPECT_EQ(base85::encode(cstr2v("123456")), cstr2v("F)}kWH8u"));
    EXPECT_EQ(base85::encode(cstr2v("hello")), cstr2v("Xk~0{Zv"));
    EXPECT_EQ(base85::encode(cstr2v("hello world")), cstr2v("Xk~0{Zy<MXa%^M"));
}

TEST(Base85Decode, LongerKnownStrings)
{
    EXPECT_EQ(base85::decode(cstr2v("F)}kWH2")), cstr2v("12345"));
    EXPECT_EQ(base85::decode(cstr2v("F)}kWH8u")), cstr2v("123456"));
    EXPECT_EQ(base85::decode(cstr2v("Xk~0{Zv")), cstr2v("hello"));
    EXPECT_EQ(base85::decode(cstr2v("Xk~0{Zy<MXa%^M")), cstr2v("hello world"));
}

TEST(Base85Roundtrip, BinaryBytes)
{
    std::vector<uint8_t> bytes =
    {
        0x00, 0x01, 0x02, 0x03,
        0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B,
        0x0C, 0x0D, 0x0E, 0x0F
    };

    EXPECT_EQ(base85::encode(bytes), cstr2v("009C61O)~M2nh-c3=Iws"));
    EXPECT_EQ(base85::decode(cstr2v("009C61O)~M2nh-c3=Iws")), bytes);
}

TEST(Base85Roundtrip, ManyLengths)
{
    std::string sample = "abcdefghijklmnopqrstuvwxyz0123456789";

    for (size_t len = 0; len <= sample.size(); ++len)
    {
        std::vector<uint8_t> bytes(sample.begin(), sample.begin() + len);
        EXPECT_EQ(base85::decode(base85::encode(bytes)), bytes);
    }
}

TEST(Base85Decode, BadLengthThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("A")), std::runtime_error);
    EXPECT_THROW(base85::decode(cstr2v("123456")), std::runtime_error);
}

TEST(Base85Decode, BadCharThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("\"\"")), std::runtime_error);
    EXPECT_THROW(base85::decode(cstr2v("!!!!!\"")), std::runtime_error);
}
