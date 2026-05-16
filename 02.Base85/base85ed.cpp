#include "base85ed.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace
{

const string BASE85_ALPHABET =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

// делаем таблицу для быстрого перевода символа Base85 обратно в число от 0 до 84.
vector<int> make_decode_table()
{
    vector<int> table(256, -1);

    for (int i = 0; i < (int)BASE85_ALPHABET.size(); i++)
    {
        unsigned char c = (unsigned char)BASE85_ALPHABET[i];
        table[c] = i;
    }

    return table;
}

// ПОЛучаем значение одного символа Base85
// Если символ не входит в алфавит, потом вернётся -1
int get_base85_digit(uint8_t ch)
{
    static vector<int> table = make_decode_table();

    return table[(unsigned char)ch];
}

// Добавляем число uint32_t в результат как несколько байтов в big-endian порядке
// т.е. сначала идёт старший байт, потом остальные
void append_uint32_as_big_endian(vector<uint8_t> &out, uint32_t value, int bytes_count)
{
    uint8_t bytes[4];

    bytes[0] = (uint8_t)((value >> 24) & 0xFF);
    bytes[1] = (uint8_t)((value >> 16) & 0xFF);
    bytes[2] = (uint8_t)((value >> 8) & 0xFF);
    bytes[3] = (uint8_t)(value & 0xFF);

    for (int i = 0; i < bytes_count; i++)
    {
        out.push_back(bytes[i]);
    }
}

} 

namespace base85
{

vector<uint8_t> encode(vector<uint8_t> const &bytes)
{
    vector<uint8_t> result;

    if (bytes.empty())
    {
        return result;
    }

    size_t full_blocks = bytes.size() / 4;
    size_t tail = bytes.size() % 4;

    size_t approx_size = full_blocks * 5;

    if (tail != 0)
    {
        approx_size += tail + 1;
    }

    result.reserve(approx_size);

    for (size_t i = 0; i < bytes.size(); i += 4)
    {
        size_t bytes_left = bytes.size() - i;
        size_t block_size = bytes_left >= 4 ? 4 : bytes_left;

        uint32_t value = 0;

        // собираем до 4х байтов в одно 32-битное число,
        // если байтов меньше 4, недостающие байты считаем нулями
        for (int j = 0; j < 4; j++)
        {
            value <<= 8;

            if ((size_t)j < block_size)
            {
                value |= bytes[i + j];
            }
        }


        char encoded[5];

        // переводим 32-битное число в 5 символов Base85
        for (int j = 4; j >= 0; j--)
        {
            encoded[j] = BASE85_ALPHABET[value % 85];
            value /= 85;
        }

        int symbols_to_write;

        // Для полного блока из 4 байтов пишем 5 символов
        // Для неполного блока пишем на 1 символ больше, чем было байтов.
        if (block_size == 4)
        {
            symbols_to_write = 5;
        }
        else
        {
            symbols_to_write = (int)block_size + 1;
        }

        for (int j = 0; j < symbols_to_write; j++)
        {
            result.push_back((uint8_t)encoded[j]);
        }
    }

    return result;
}

vector<uint8_t> decode(vector<uint8_t> const &b85str)

{
    vector<uint8_t> result;

    if (b85str.empty())
    {
        return result;
    }

    size_t full_groups = b85str.size() / 5;
    size_t tail = b85str.size() % 5;

    size_t approx_size = full_groups * 4;

    if (tail != 0)
    {
        approx_size += tail - 1;
    }

    result.reserve(approx_size);

    for (size_t i = 0; i < b85str.size(); i += 5)
    {
        size_t symbols_left = b85str.size() - i;
        size_t group_size = symbols_left >= 5 ? 5 : symbols_left;

        uint64_t value = 0;

        // берём до 5 символов Base85.
        // Если символов меньше 5, дополняем символом '~',
        for (int j = 0; j < 5; j++)
        {
            uint8_t ch;

            if ((size_t)j < group_size)
            {
                ch = b85str[i + j];
            }
            else
            {
                ch = (uint8_t)'~';
            }

            int digit = get_base85_digit(ch);

            if (digit < 0)
            {
                throw invalid_argument("плохой символ в строке Base85");
            }

            value = value * 85 + (uint64_t)digit;

            if (value > 0xFFFFFFFFULL)
            {
                throw invalid_argument("переполнение при декодировании Base85");
            }
        }

        int bytes_to_write;

        // из 5 символов получается 4 байта,
        // из неполной группы получается на 1 байт меньше, чем было символов:
        if (group_size == 5)
        {
            bytes_to_write = 4;
        }
        else
        {
            bytes_to_write = (int)group_size - 1;
        }

        append_uint32_as_big_endian(result, (uint32_t)value, bytes_to_write);
    }

    return result;
}

} 
