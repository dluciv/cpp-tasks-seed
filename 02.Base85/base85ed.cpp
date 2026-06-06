#include "base85ed.h"
#include <stdexcept>
#include <cstdint>
#include <cstring>

namespace
{

// Алфавит Ascii85 RFC 1924 – 85 символов по порядку
const char ENCODE_TABLE[86] = "0123456789"
                              "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                              "abcdefghijklmnopqrstuvwxyz"
                              "!#$%&()*+-;<=>?@^_`{|}~";

// Таблица декодирования: ASCII код -> значение 0..84, -1 если недопустим
int decode_table[128];
bool tables_initialized = false;

void init_tables()
{
    if (tables_initialized)
        {
            return;
        }

    memset(decode_table, -1, sizeof(decode_table));

    for (int i = 0; i < 85; ++i)
        {
            uint8_t c = ENCODE_TABLE[i];
            decode_table[c] = i;
        }

    // Пробельные символы (будем обрабатывать отдельно)
    decode_table[' '] = -2;
    decode_table['\t'] = -2;
    decode_table['\n'] = -2;
    decode_table['\r'] = -2;
    decode_table['\v'] = -2;
    decode_table['\f'] = -2;
    tables_initialized = true;
}

inline uint32_t pack_big_endian(const uint8_t *b)
{
    return (uint32_t(b[0]) << 24) |
           (uint32_t(b[1]) << 16) |
           (uint32_t(b[2]) << 8)  |
           (uint32_t(b[3]));
}

// Преобразование 32-битного числа в 5 base85-цифр (0..84, старший порядок)
void unpack85(uint32_t value, uint8_t *out)
{
    for (int i = 4; i >= 0; --i)
        {
            out[i] = value % 85;
            value /= 85;
        }
}

} // анонимное пространство

std::vector<uint8_t> base85::encode(const std::vector<uint8_t> &bytes)
{
    init_tables();
    std::vector<uint8_t> result;
    const size_t size = bytes.size();
    size_t i = 0;

    while (i < size)
        {
            size_t remaining = size - i;

            if (remaining >= 4)
                {
                    uint32_t val = pack_big_endian(&bytes[i]);
                    uint8_t digits[5];
                    unpack85(val, digits);

                    for (int j = 0; j < 5; ++j)
                        {
                            result.push_back(ENCODE_TABLE[digits[j]]);
                        }

                    i += 4;
                }
            else
                {
                    // Последний неполный блок (1..3 байта)
                    uint8_t padded[4] = {0, 0, 0, 0};

                    for (size_t j = 0; j < remaining; ++j)
                        {
                            padded[j] = bytes[i + j];
                        }

                    uint32_t val = pack_big_endian(padded);
                    uint8_t digits[5];
                    unpack85(val, digits);

                    // Выводим только remaining+1 символов
                    for (size_t j = 0; j < remaining + 1; ++j)
                        {
                            result.push_back(ENCODE_TABLE[digits[j]]);
                        }

                    i += remaining;
                }
        }

    return result;
}

std::vector<uint8_t> base85::decode(const std::vector<uint8_t> &b85str)
{
    init_tables();
    std::vector<uint8_t> result;
    std::vector<uint8_t> group; // значения 0..84
    group.reserve(5);

    auto decode_group = [&](std::vector<uint8_t> &grp, bool end_of_stream)
    {
        if (grp.empty())
            {
                return;
            }

        if (!end_of_stream && grp.size() != 5)
            {
                throw std::invalid_argument("Base85: incomplete group in the middle");
            }

        size_t len = grp.size();

        if (len == 1)
            {
                throw std::invalid_argument("Base85: single character in group");
            }

        // Дополняем до 5 символов цифрой 84 ('~')
        while (grp.size() < 5)
            {
                grp.push_back(84);
            }

        uint32_t value = 0;

        for (size_t i = 0; i < 5; ++i)
            {
                value = value * 85 + grp[i];
            }

        uint8_t bytes[4] =
        {
            uint8_t((value >> 24) & 0xFF),
            uint8_t((value >> 16) & 0xFF),
            uint8_t((value >> 8) & 0xFF),
            uint8_t(value & 0xFF)
        };
        size_t out_bytes = (len != 5) ? (len - 1) : 4;

        for (size_t i = 0; i < out_bytes; ++i)
            {
                result.push_back(bytes[i]);
            }

        grp.clear();
    };

    for (size_t i = 0; i < b85str.size(); ++i)
        {
            uint8_t c = b85str[i];

            if (c >= 128)
                {
                    throw std::invalid_argument(std::string("Base85: invalid character '") +
                                                char(c) + "' (code " + std::to_string(c) + ")");
                }

            int val = decode_table[c];

            if (val == -2)
                {
                    continue;    // пробел – игнорируем
                }

            if (val == -1)
                {
                    throw std::invalid_argument(std::string("Base85: invalid character '") +
                                                char(c) + "' (code " + std::to_string(c) + ")");
                }

            group.push_back(static_cast<uint8_t>(val));

            if (group.size() == 5)
                {
                    decode_group(group, false);
                }
        }

    if (!group.empty())
        {
            decode_group(group, true);
        }

    return result;
}