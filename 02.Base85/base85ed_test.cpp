#include <gtest/gtest.h>
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

TEST(Base85TrickyTests, EdgeValues)
{
    std::vector<uint8_t> zeroes = {0, 0, 0, 0};
    EXPECT_EQ(base85::encode(zeroes), cstr2v("00000"));
    EXPECT_EQ(base85::decode(cstr2v("00000")), zeroes);

    std::vector<uint8_t> max_bytes = {0xFF, 0xFF, 0xFF, 0xFF};
    EXPECT_EQ(base85::encode(max_bytes), cstr2v("|NsC0"));
    EXPECT_EQ(base85::decode(cstr2v("|NsC0")), max_bytes);
}

TEST(Base85TrickyTests, ComprehensiveLengths)
{
    for (size_t len = 1; len <= 32; ++len)
    {
        std::vector<uint8_t> original;
        for (size_t i = 0; i < len; ++i)
        {
            original.push_back(static_cast<uint8_t>((i * 23 + 7) % 256));
        }

        std::vector<uint8_t> encoded = base85::encode(original);
        std::vector<uint8_t> decoded = base85::decode(encoded);

        EXPECT_EQ(encoded.size(), (len / 4) * 5 + (len % 4 ? (len % 4) + 1 : 0));
        EXPECT_EQ(original, decoded);
    }
}
