#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>
#include <vector>

#include "base85ed.h"

TEST(Base85Test, EncodesAndDecodesEmptyVector)
{
    std::vector<uint8_t> data;

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Test, EncodesAndDecodesFourBytes)
{
    std::vector<uint8_t> data{1, 2, 3, 4};

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Test, EncodesAndDecodesPartialBlock)
{
    std::vector<uint8_t> data{1, 2, 3};

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Test, EncodesAndDecodesLongData)
{
    std::vector<uint8_t> data
    {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13
    };

    auto encoded = base85::encode(data);
    auto decoded = base85::decode(encoded);

    EXPECT_EQ(decoded, data);
}

TEST(Base85Test, ThrowsOnInvalidLength)
{
    std::vector<uint8_t> invalid{'!'};

    EXPECT_THROW(base85::decode(invalid), std::invalid_argument);
}