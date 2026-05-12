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



TEST(Base85Roundtrip, Empty)
{
   std::vector<uint8_t> data;
   EXPECT_EQ(base85::decode(base85::encode(data)), data);
}


TEST(Base85Roundtrip, SingleByte)
{
   for (int v = 0; v <= 255; ++v)
   {
       std::vector<uint8_t> data = {static_cast<uint8_t>(v)};
       EXPECT_EQ(base85::decode(base85::encode(data)), data);
   }
}


TEST(Base85Roundtrip, MultipleBytes)
{
   for (int a = 0; a <= 255; a += 50)
       for (int b = 0; b <= 255; b += 50)
           for (int c = 0; c <= 255; c += 50)
           {
               std::vector<uint8_t> data = {static_cast<uint8_t>(a), static_cast<uint8_t>(b), static_cast<uint8_t>(c)};
               EXPECT_EQ(base85::decode(base85::encode(data)), data);
           }
}


TEST(Base85LargeData, LargeBlock)
{
   size_t size = 1024;
   std::vector<uint8_t> data(size);
   for (size_t i = 0; i < size; ++i)
       data[i] = static_cast<uint8_t>((i * 37) & 0xFF);
   auto encoded = base85::encode(data);
   auto decoded = base85::decode(encoded);
   EXPECT_EQ(decoded, data);
}


TEST(Base85MaxValues, MaxBytes)
{
   std::vector<uint8_t> max_bytes = {0xFF, 0xFF, 0xFF, 0xFF};
   EXPECT_EQ(base85::decode(cstr2v("|NsC0")), max_bytes);
   EXPECT_EQ(base85::encode(max_bytes), cstr2v("|NsC0"));
}


TEST(Base85Zeros, EncodeDecodeZeros)
{
   std::vector<uint8_t> zeros(10, 0);
   auto encoded = base85::encode(zeros);
   auto decoded = base85::decode(encoded);
   EXPECT_EQ(decoded, zeros);
}


TEST(Base85SneakyTests, InvalidCharacters)
{
   EXPECT_THROW(base85::decode(cstr2v("F) {")), std::invalid_argument);
   EXPECT_THROW(base85::decode(cstr2v("F)\n{")), std::invalid_argument);
}