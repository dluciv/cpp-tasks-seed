#include <gtest/gtest.h>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <string>

#include "base85ed.h"

// Вспомогательная функция для конвертации строковых литералов в vector<uint8_t>
static std::vector<uint8_t> to_vec(const char *s)
{
    return std::vector<uint8_t>(s, s + std::string(s).size());
}

// Тест стандартных коротких и неполных блоков
const std::vector<std::pair<std::string, std::string>> test_cases = {
    { "",        "" },
    { "F#",      "1" },
    { "F){",     "12" },
    { "F)}j",    "123" },
    { "F)}kW",   "1234" },
    { "00",      "\x00" },
    { "nm=QN",   "C++" }
};

// Проверка кодирования (Encode)
TEST(Base85Tests, BasicEncoding)
{
    for (const auto &tc : test_cases)
    {
        EXPECT_EQ(base85::encode(to_vec(tc.second.c_str())), to_vec(tc.first.c_str()));
    }
}

// Проверка декодирования (Decode)
TEST(Base85Tests, BasicDecoding)
{
    for (const auto &tc : test_cases)
    {
        EXPECT_EQ(base85::decode(to_vec(tc.first.c_str())), to_vec(tc.second.c_str()));
    }
}

// Тестирование обработки ошибок и исключений
TEST(Base85Tests, ExceptionHandling)
{
    // Одиночный символ не может существовать в валидной строке Base85
    EXPECT_THROW(base85::decode(to_vec("F")), std::runtime_error);

    // Запрещенные символы, которых нет в алфавите RFC 1924 (например, пробелы или спецсимволы)
    EXPECT_THROW(base85::decode(to_vec("F ")), std::runtime_error);
    EXPECT_THROW(base85::decode(to_vec("F#_")), std::runtime_error);

    // Значение, вызывающее переполнение 32-битного диапазона (больше чем 85^5 - 1)
    EXPECT_THROW(base85::decode(to_vec("~~~~~")), std::runtime_error);
}
