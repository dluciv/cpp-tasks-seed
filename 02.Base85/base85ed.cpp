#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "base85ed.h"

static const char* alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

static uint8_t reverse_table[256];

static void init_reverse()
{
    static bool inited = false;
    if (inited) return;

    std::fill(std::begin(reverse_table), std::end(reverse_table), 0xFF);

    for (int i = 0; i < 85; ++i)
    {
        reverse_table[(uint8_t)alphabet[i]] = i;
    }

    inited = true;
}


std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;

    size_t i = 0;
    while (i < bytes.size())
    {
        uint32_t value = 0;
        size_t chunk = 0;
        for (; chunk < 4 && i < bytes.size(); ++chunk, ++i)
        {
            value = value * 256 + bytes[i];
        }

        // padding (from python realization)
        if (chunk < 4)
        {
            value <<= (4 - chunk) * 8;
        }

        char buf[5];
        for (int j = 4; j >= 0; --j)
        {
            buf[j] = alphabet[value % 85];
            value /= 85;
        }

        size_t out_len = (chunk < 4) ? chunk + 1 : 5;
        out.insert(out.end(), buf, buf + out_len);
    }

    return out;
}



std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    init_reverse();

    std::vector<uint8_t> out;

    size_t i = 0;
    while (i < b85str.size())
    {
        uint32_t value = 0;
        size_t chunk = 0;

        uint8_t block[5] = {0}; //read 5 symbols

        for (; chunk < 5 && i < b85str.size(); ++chunk, ++i)
        {
            uint8_t c = b85str[i];
            if (reverse_table[c] == 0xFF)
                throw std::runtime_error("invalid base85 character");

            block[chunk] = c;
        }

        if (chunk == 0) break;

        // padding (from python realization)
        for (size_t j = chunk; j < 5; ++j)
        {
            block[j] = alphabet[84];
        }

        for (int j = 0; j < 5; ++j)
        {
            value = value * 85 + reverse_table[block[j]];
        }

        uint8_t temp[4];
        for (int j = 3; j >= 0; --j)
        {
            temp[j] = value & 0xFF;
            value >>= 8;
        }

        size_t out_len = (chunk < 5) ? chunk - 1 : 4;
        out.insert(out.end(), temp, temp + out_len);
    }

    return out;
}