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
    { "F){\\",  "12"   },
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

// Тесты encode для коротких строк
TEST(Base85ShortsEncode, TrivialShortEncodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::encode(cstr2v(p.second)), cstr2v(p.first));
    }
}

// Тесты decode для коротких строк
TEST(Base85ShortsDecode, TrivialShortDecodes)
{
    for (const auto &p : short_cases)
    {
        EXPECT_EQ(base85::decode(cstr2v(p.first)), cstr2v(p.second));
    }
}

// Тесты на обработку некорректных ситуаций (исключения)
TEST(Base85DecodeErrors, InvalidCharacters)
{
    // Пробел не входит в алфавит RFC 1924
    EXPECT_THROW(base85::decode(cstr2v("F #")), std::runtime_error);
    // Символы вроде кавычек отсутствуют в наборе b85
    EXPECT_THROW(base85::decode(cstr2v("F\"")), std::runtime_error);
}

TEST(Base85DecodeErrors, InvalidLength)
{
    // Остаток в 1 лишний символ не допускается спецификацией
    EXPECT_THROW(base85::decode(cstr2v("F#)kWF")), std::runtime_error);
}

TEST(Base85DecodeErrors, OverflowHandling)
{
    // Пять максимальных символов "~~~~~" превышают емкость 32-битного числа
    EXPECT_THROW(base85::decode(cstr2v("~~~~~")), std::runtime_error);
}

// Интеграционный юнит-тест на длинной последовательности данных
TEST(Base85LongCases, LongEncodingDecodingRoundtrip)
{
    std::vector<uint8_t> original = cstr2v("The quick brown fox jumps over the lazy dog. Base85 implementation in clean C++ without any python stubs!");
    std::vector<uint8_t> encoded = base85::encode(original);
    std::vector<uint8_t> decoded = base85::decode(encoded);
    
    EXPECT_EQ(original, decoded);
}
