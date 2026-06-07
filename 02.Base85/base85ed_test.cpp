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

TEST(Base85ShortsEncode, FiveBytes)
{
    EXPECT_EQ(base85::encode(cstr2v("12345")), cstr2v("F)}kWH2"));
}

TEST(Base85ShortsDecode, FiveBytes)
{
    EXPECT_EQ(base85::decode(cstr2v("F)}kWH2")), cstr2v("12345"));
}

TEST(Base85ShortsEncode, AllZeroBytes)
{
    std::vector<uint8_t> zeros(4, 0x00);
    EXPECT_EQ(base85::encode(zeros), cstr2v("00000"));
}

TEST(Base85ShortsDecode, AllZeroChars)
{
    std::vector<uint8_t> expected(4, 0x00);
    EXPECT_EQ(base85::decode(cstr2v("00000")), expected);
}

TEST(Base85ShortsEncode, AllFFBytes)
{
    std::vector<uint8_t> all_ff(4, 0xFF);
    EXPECT_EQ(base85::encode(all_ff), cstr2v("|NsC0"));
}

TEST(Base85ShortsDecode, AllFFChars)
{
    std::vector<uint8_t> expected(4, 0xFF);
    EXPECT_EQ(base85::decode(cstr2v("|NsC0")), expected);
}

TEST(Base85KnownEncode, HelloWorld)
{
    EXPECT_EQ(base85::encode(cstr2v("Hello, World!")), cstr2v("NM&qnZ!92JZ*pv8Ap"));
}

TEST(Base85KnownDecode, HelloWorld)
{
    EXPECT_EQ(base85::decode(cstr2v("NM&qnZ!92JZ*pv8Ap")), cstr2v("Hello, World!"));
}

TEST(Base85Encode, OutputLength)
{
    for (size_t n = 0; n <= 16; ++n)
    {
        std::vector<uint8_t> input(n, 0x42);
        size_t got = base85::encode(input).size();
        size_t expected = (n / 4) * 5 + (n % 4 ? n % 4 + 1 : 0);
        EXPECT_EQ(got, expected) << "wrong length for n=" << n;
    }
}

TEST(Base85RoundTrip, VariousLengths)
{
    for (size_t n = 0; n <= 20; ++n)
    {
        std::vector<uint8_t> input(n);
        for (size_t i = 0; i < n; ++i) input[i] = static_cast<uint8_t>(i);
        EXPECT_EQ(base85::decode(base85::encode(input)), input)
                << "round-trip failed for length " << n;
    }
}

TEST(Base85RoundTrip, SingleByteAllValues)
{
    for (int v = 0; v <= 255; ++v)
    {
        std::vector<uint8_t> input = { static_cast<uint8_t>(v) };
        EXPECT_EQ(base85::decode(base85::encode(input)), input)
                << "round-trip failed for byte value " << v;
    }
}

TEST(Base85DecodeErrors, InvalidCharThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("F)}k ")), std::runtime_error);
}

TEST(Base85DecodeErrors, SingleTrailingCharThrows)
{
    EXPECT_THROW(base85::decode(cstr2v("F)}kWF")), std::runtime_error);
}