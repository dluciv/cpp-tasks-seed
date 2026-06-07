#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#include "base85ed.h"

static const char B85_ALPHA[86] =
    "0123456789"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "!#$%&()*+-;<=>?@^_`{|}~";

static const uint8_t* decode_table()
{
    static uint8_t tbl[256];
    static bool built = false;
    if (!built)
    {
        for (int i = 0; i < 256; ++i) tbl[i] = 0xFF;
        for (int i = 0; i < 85; ++i) tbl[(uint8_t)B85_ALPHA[i]] = (uint8_t)i;
        built = true;
    }
    return tbl;
}

static void encode_word(uint32_t val, char out[5])
{
    for (int i = 4; i >= 0; --i)
    {
        out[i] = B85_ALPHA[val % 85];
        val /= 85;
    }
}

static uint32_t decode_word(const uint8_t idx[5])
{
    uint32_t val = 0;
    for (int i = 0; i < 5; ++i)
        val = val * 85u + idx[i];
    return val;
}

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> out;
    out.reserve((bytes.size() / 4 + 1) * 5);
    const size_t n = bytes.size();
    for (size_t i = 0; i < n; )
    {
        const size_t chunk = (n - i >= 4) ? 4u : (n - i);
        uint32_t val = 0;
        for (size_t j = 0; j < 4; ++j)
        {
            val <<= 8u;
            if (j < chunk)
                val |= bytes[i + j];
        }
        char enc[5];
        encode_word(val, enc);
        const size_t emit = (chunk == 4) ? 5u : chunk + 1u;
        for (size_t j = 0; j < emit; ++j)
            out.push_back(static_cast<uint8_t>(enc[j]));
        i += chunk;
    }
    return out;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    const uint8_t* const dtbl = decode_table();
    std::vector<uint8_t> out;
    out.reserve((b85str.size() / 5) * 4 + 4);
    const size_t n = b85str.size();
    for (size_t i = 0; i < n; )
    {
        const size_t chunk = (n - i >= 5) ? 5u : (n - i);
        if (chunk == 1)
            throw std::runtime_error(
                "base85::decode: недопустимая длина данных");
        uint8_t idx[5];
        for (size_t j = 0; j < 5; ++j)
        {
            if (j < chunk)
            {
                const uint8_t c = b85str[i + j];
                const uint8_t v = dtbl[c];
                if (v == 0xFF)
                    throw std::runtime_error(
                        std::string("base85::decode: недопустимый символ: ")
                        + static_cast<char>(c));
                idx[j] = v;
            }
            else
            {
                idx[j] = 84u;
            }
        }
        const uint32_t val = decode_word(idx);
        const size_t emit = (chunk == 5) ? 4u : chunk - 1u;
        for (size_t j = 0; j < emit; ++j)
            out.push_back(static_cast<uint8_t>((val >> (8u * (3u - j))) & 0xFFu));
        i += chunk;
    }
    return out;
}
