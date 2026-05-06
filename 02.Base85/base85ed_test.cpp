#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string.h>
#include <random>

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

static std::vector<uint8_t> generate_random_data(size_t len, uint32_t seed = 42) {
    std::vector<uint8_t> data(len);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(0, 255);
    for (size_t i = 0; i < len; ++i) {
        data[i] = static_cast<uint8_t>(dist(gen));
    }
    return data;
}

static void check_cycle(const std::vector<uint8_t>& original) {
    auto encoded = base85::encode(original);
    auto decoded = base85::decode(encoded);
    EXPECT_EQ(decoded, original);
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

TEST(Base85LongCycle, RandomLargeData)
{
    auto data = generate_random_data(1024);
    check_cycle(data);
    
    auto data_large = generate_random_data(10240, 123);
    check_cycle(data_large);
}

TEST(Base85Lengths, VariousLengthsCycle)
{
    for (int len = 1; len <= 20; ++len) {
        auto data = generate_random_data(len, len);
        check_cycle(data);
    }
}

TEST(Base85SpecialCases, AllZeros)
{
    std::vector<uint8_t> zeros(100, 0x00);
    check_cycle(zeros);
    
    std::vector<uint8_t> small_zeros(3, 0x00);
    check_cycle(small_zeros);
}

TEST(Base85SpecialCases, AllMaxBytes)
{
    std::vector<uint8_t> maxs(100, 0xFF);
    check_cycle(maxs);
}

TEST(Base85SpecialCases, AlternatingBytes)
{
    std::vector<uint8_t> alt;
    for(int i=0; i<100; ++i) {
        alt.push_back(i % 2 == 0 ? 0x00 : 0xFF);
    }
    check_cycle(alt);
}

TEST(Base85Stress, VeryLongString)
{
    size_t size = 1024 * 1024; 
    auto data = generate_random_data(size, 999);
    
    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);
    
    EXPECT_EQ(decoded.size(), data.size());
    EXPECT_EQ(decoded, data);
}

TEST(Base85Whitespace, IgnoreSpaces)
{
    std::vector<uint8_t> input_with_spaces = { 'F', ' ', '#', '\n', '\t' };
    auto decoded = base85::decode(input_with_spaces);
    EXPECT_EQ(decoded, cstr2v("1"));
}
