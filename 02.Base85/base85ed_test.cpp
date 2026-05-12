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

TEST(Base85RoundTrip, VariousLengths)
{
    for (size_t len = 0; len < 1024; ++len)
    {
        std::vector<uint8_t> data;

        for (size_t i = 0; i < len; ++i)
        {
            data.push_back(static_cast<uint8_t>(i % 256));
        }

        auto encoded = base85::encode(data);
        auto decoded = base85::decode(encoded);

        EXPECT_EQ(decoded, data);
    }
}

TEST(Base85RoundTrip, LongText)
{
    std::string s;

    for (int i = 0; i < 10000; ++i)
    {
        s += "The quick brown fox jumps over the lazy dog ";
    }

    std::vector<uint8_t> data(s.begin(), s.end());

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85RoundTrip, BinaryData)
{
    std::vector<uint8_t> data;

    for (int i = 0; i < 100000; ++i)
    {
        data.push_back(static_cast<uint8_t>(rand() % 256));
    }

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Decode, InvalidCharacter)
{
    std::vector<uint8_t> invalid = {'~', '~', '~', ' '};

    EXPECT_THROW(base85::decode(invalid), std::runtime_error);
}

TEST(Base85RoundTrip, VariousLengths)
{
    for (size_t len = 0; len < 1024; ++len)
    {
        std::vector<uint8_t> data;

        for (size_t i = 0; i < len; ++i)
        {
            data.push_back(static_cast<uint8_t>(i % 256));
        }

        auto encoded = base85::encode(data);
        auto decoded = base85::decode(encoded);

        EXPECT_EQ(decoded, data);
    }
}

TEST(Base85RoundTrip, LongText)
{
    std::string s;

    for (int i = 0; i < 10000; ++i)
    {
        s += "The quick brown fox jumps over the lazy dog ";
    }

    std::vector<uint8_t> data(s.begin(), s.end());

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85RoundTrip, BinaryData)
{
    std::vector<uint8_t> data;

    for (int i = 0; i < 100000; ++i)
    {
        data.push_back(static_cast<uint8_t>(rand() % 256));
    }

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Decode, InvalidCharacter)
{
    std::vector<uint8_t> invalid = {'~', '~', '~', ' '};

    EXPECT_THROW(base85::decode(invalid), std::runtime_error);
}
