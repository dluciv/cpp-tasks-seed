#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>

#include "base85ed.h"

static std::vector<uint8_t> cstr2v(const char* s)
{
    std::string str(s);
    return std::vector<uint8_t>(str.begin(), str.end());
}

// ===========================
// ТЕСТЫ КОДИРОВАНИЯ
// ===========================

TEST(Base85Encode, Empty)
{
    EXPECT_EQ(base85::encode({}), std::vector<uint8_t> {});
}

TEST(Base85Encode, OneByte)
{
    EXPECT_EQ(base85::encode(cstr2v("1")), cstr2v("F#"));
}

TEST(Base85Encode, TwoBytes)
{
    EXPECT_EQ(base85::encode(cstr2v("12")), cstr2v("F){"));
}

TEST(Base85Encode, ThreeBytes)
{
    EXPECT_EQ(base85::encode(cstr2v("123")), cstr2v("F)}j"));
}

TEST(Base85Encode, FourBytes)
{
    EXPECT_EQ(base85::encode(cstr2v("1234")), cstr2v("F)}kW"));
}

TEST(Base85Encode, SingleZero)
{
    std::vector<uint8_t> input = {0x00};
    EXPECT_EQ(base85::encode(input), cstr2v("00"));
}

TEST(Base85Encode, OneNonZero)
{
    std::vector<uint8_t> input = {0x01};
    EXPECT_EQ(base85::encode(input), cstr2v("0R"));
}

TEST(Base85Encode, FourZeros)
{
    std::vector<uint8_t> input(4, 0);
    EXPECT_EQ(base85::encode(input), cstr2v("00000"));
}

TEST(Base85Encode, PartialBlockSizes)
{
    for (size_t n = 1; n <= 3; ++n)
    {
        std::vector<uint8_t> data(n, 0x42);
        EXPECT_EQ(base85::encode(data).size(), n + 1);
    }
}

// ===========================
// ТЕСТЫ ДЕКОДИРОВАНИЯ
// ===========================

TEST(Base85Decode, DecodeOneChar)
{
    EXPECT_EQ(base85::decode(cstr2v("F#")), cstr2v("1"));
}

TEST(Base85Decode, DecodeTwoChars)
{
    EXPECT_EQ(base85::decode(cstr2v("F){")), cstr2v("12"));
}

TEST(Base85Decode, DecodeThreeChars)
{
    EXPECT_EQ(base85::decode(cstr2v("F)}j")), cstr2v("123"));
}

TEST(Base85Decode, DecodeFourChars)
{
    EXPECT_EQ(base85::decode(cstr2v("F)}kW")), cstr2v("1234"));
}

TEST(Base85Decode, SingleZero)
{
    std::vector<uint8_t> in = cstr2v("00");
    std::vector<uint8_t> expected = {0x00};
    EXPECT_EQ(base85::decode(in), expected);
}

TEST(Base85Decode, OneNonZero)
{
    EXPECT_EQ(base85::decode(cstr2v("0R")), std::vector<uint8_t> {0x01});
}

TEST(Base85Decode, FourZeros)
{
    auto dec = base85::decode(cstr2v("00000"));
    std::vector<uint8_t> expected(4, 0);
    EXPECT_EQ(dec, expected);
}

TEST(Base85Decode, WhitespaceIgnored)
{
    // Пробелы и переводы строк должны игнорироваться, не разбивая группу
    std::vector<uint8_t> in = cstr2v("  F  #   \n\t\r\v\f");
    auto out = base85::decode(in);
    std::vector<uint8_t> expected = { '1' };
    EXPECT_EQ(out, expected);
}

TEST(Base85Decode, IncompleteGroups)
{
    // Проверка дополнения неполных групп
    EXPECT_EQ(base85::decode(base85::encode(cstr2v("a"))), cstr2v("a"));
    EXPECT_EQ(base85::decode(base85::encode(cstr2v("ab"))), cstr2v("ab"));
    EXPECT_EQ(base85::decode(base85::encode(cstr2v("abc"))), cstr2v("abc"));
}

TEST(Base85Decode, ThrowsSingleChar)
{
    EXPECT_THROW(base85::decode(cstr2v("!")), std::invalid_argument);
    EXPECT_THROW(base85::decode(cstr2v("z")), std::invalid_argument);
}

TEST(Base85Decode, ThrowsInvalidChar)
{
    // '[' нет в алфавите, должно выбросить исключение
    EXPECT_THROW(base85::decode(cstr2v("Fe[")), std::invalid_argument);
}

// ===========================
// ОБРАТИМОСТЬ
// ===========================

TEST(Base85Roundtrip, VariousData)
{
    auto test = [](const std::vector<uint8_t>& d)
    {
        EXPECT_EQ(base85::decode(base85::encode(d)), d);
    };
    test({});
    for (size_t len = 1; len <= 20; ++len)
    {
        std::vector<uint8_t> d(len);
        for (size_t i = 0; i < len; ++i) d[i] = static_cast<uint8_t>(i * 7 + len);
        test(d);
    }
    std::vector<uint8_t> all(256);
    for (int i = 0; i < 256; ++i) all[i] = static_cast<uint8_t>(i);
    test(all);
    std::vector<uint8_t> zeros(4096, 0);
    test(zeros);
}