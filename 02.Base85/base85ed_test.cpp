#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <random>
#include <string>

#include "base85ed.h"



static std::vector<uint8_t> str_to_vec(const char* s)
{
    return std::vector<uint8_t>(s, s + std::string(s).size());
}

static std::vector<uint8_t> random_data(size_t n, uint32_t seed = 42)
{
    std::vector<uint8_t> data(n);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 255);
    for (size_t i = 0; i < n; ++i)
    {
        data[i] = static_cast<uint8_t>(dist(gen));
    }
    return data;
}

static void test_roundtrip(const std::vector<uint8_t>& orig)
{
    auto enc = base85::encode(orig);
    auto dec = base85::decode(enc);
    EXPECT_EQ(dec, orig);
}

const std::vector<std::pair<const char*, const char*>> test_vectors =
{
    {"", ""},
    {"F#", "1"},
    {"F){", "12"},
    {"F)}j", "123"},
    {"F)}kW", "1234"},
};

TEST(Base85Encode, ShortVectors)
{
    for (const auto& tv : test_vectors)
    {
        auto got = base85::encode(str_to_vec(tv.second));
        EXPECT_EQ(std::string(got.begin(), got.end()), tv.first);
    }
}

TEST(Base85Roundtrip, RandomData)
{
    auto data = random_data(1024);
    test_roundtrip(data);
}

TEST(Base85Roundtrip, VariousSizes)
{
    for (int len = 1; len <= 20; ++len)
    {
        auto data = random_data(len, len);
        test_roundtrip(data);
    }
}

TEST(Base85Special, AllZeros)
{
    std::vector<uint8_t> zeros(100, 0);
    test_roundtrip(zeros);
}

TEST(Base85Special, AllMax)
{
    std::vector<uint8_t> maxes(100, 0xFF);
    test_roundtrip(maxes);
}

TEST(Base85Whitespace, IgnoreSpaces)
{
    std::vector<uint8_t> with_spaces = {'F', ' ', '#', '\n', '\t'};
    auto dec = base85::decode(with_spaces);
    EXPECT_EQ(dec, str_to_vec("1"));
}

