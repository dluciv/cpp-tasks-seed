#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <string>
#include <algorithm>

#include "base85ed.h"

// Helper to convert C-string or char array to vector<uint8_t>
static std::vector<uint8_t> cstr2v(const char *s)
{
    return std::vector<uint8_t>(s, s + std::string(s).size());
}

// Helper to compare with Python's reference (optional)
static std::string v2str(const std::vector<uint8_t>& v)
{
    return std::string(v.begin(), v.end());
}

// ------------- Tests from original short cases -----------------
const std::vector<std::pair<const char *, const char *>> short_cases =
{
    { "",     ""     },
    { "F#",   "1"    },
    { "F){",  "12"   },
    { "F)}j", "123"  },
    { "F)}kW","1234" }
};

TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(v2str(base85::encode(cstr2v(p.second))), p.first);
    }
}

TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(v2str(base85::decode(cstr2v(p.first))), p.second);
    }
}

// ------------- Additional thorough tests -----------------------
TEST(Base85Test, EncodeDecodeRoundtripEmpty)
{
    std::vector<uint8_t> original;
    auto encoded = base85::encode(original);
    auto decoded = base85::decode(encoded);
    EXPECT_EQ(original, decoded);
}

TEST(Base85Test, EncodeDecodeRoundtripSingleByte)
{
    for (int v = 0; v <= 255; ++v)
    {
        std::vector<uint8_t> original = {static_cast<uint8_t>(v)};
        auto encoded = base85::encode(original);
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(original, decoded);
    }
}

TEST(Base85Test, EncodeDecodeRoundtripTwoBytes)
{
    for (int a = 0; a <= 255; a += 37)
        for (int b = 0; b <= 255; b += 53)
        {
            std::vector<uint8_t> original = {static_cast<uint8_t>(a), static_cast<uint8_t>(b)};
            auto encoded = base85::encode(original);
            auto decoded = base85::decode(encoded);
            EXPECT_EQ(original, decoded);
        }
}

TEST(Base85Test, EncodeDecodeRoundtripThreeBytes)
{
    for (int a = 0; a <= 255; a += 31)
        for (int b = 0; b <= 255; b += 47)
            for (int c = 0; c <= 255; c += 59)
            {
                std::vector<uint8_t> original = {static_cast<uint8_t>(a), static_cast<uint8_t>(b), static_cast<uint8_t>(c)};
                auto encoded = base85::encode(original);
                auto decoded = base85::decode(encoded);
                EXPECT_EQ(original, decoded);
            }
}

TEST(Base85Test, EncodeDecodeRoundtripFourBytes)
{
    for (int a = 0; a <= 255; a += 63)
        for (int b = 0; b <= 255; b += 71)
            for (int c = 0; c <= 255; c += 79)
                for (int d = 0; d <= 255; d += 89)
                {
                    std::vector<uint8_t> original = {static_cast<uint8_t>(a), static_cast<uint8_t>(b), static_cast<uint8_t>(c), static_cast<uint8_t>(d)};
                    auto encoded = base85::encode(original);
                    auto decoded = base85::decode(encoded);
                    EXPECT_EQ(original, decoded);
                }
}

TEST(Base85Test, EncodeDecodeRoundtripRandomLengths)
{
    for (size_t len = 0; len <= 100; ++len)
    {
        std::vector<uint8_t> original(len);
        for (size_t i = 0; i < len; ++i)
            original[i] = static_cast<uint8_t>((i * 65537) ^ 0xAA);
        auto encoded = base85::encode(original);
        auto decoded = base85::decode(encoded);
        EXPECT_EQ(original, decoded);
    }
}

TEST(Base85Test, EncodeDecodeLargeBlock)
{
    const size_t SIZE = 1024;
    std::vector<uint8_t> original(SIZE);
    for (size_t i = 0; i < SIZE; ++i)
        original[i] = static_cast<uint8_t>((i * 1103515245 + 12345) & 0xFF);
    auto encoded = base85::encode(original);
    auto decoded = base85::decode(encoded);
    EXPECT_EQ(original, decoded);
}

// Test that decode throws on invalid character (optional, if you add exception handling)
// But current implementation throws std::runtime_error, so we can test that
TEST(Base85Test, DecodeThrowsOnInvalidChar)
{
    std::vector<uint8_t> invalid = cstr2v("F#~?!"); // '?' is not in alphabet? Actually '?' is in alphabet? Check alphabet string: ... "?@^_`{|}~" so '?' is present. Let's use '[' which is not there.
    invalid.push_back('[');
    EXPECT_THROW(base85::decode(invalid), std::runtime_error);
}