#include "base85ed.h"
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace base85
{

static const char b85chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> res;
    size_t n = bytes.size();

    for (size_t i = 0; i < n; i += 4)
    {
        uint32_t val = 0;
        for (int j = 0; j < 4; ++j)
        {
            val = (val << 8) | (i + j < n ? bytes[i + j] : 0);
        }

        char out[5];
        uint32_t temp = val;
        for (int j = 4; j >= 0; j--)
        {
            out[j] = b85chars[temp % 85];
            temp /= 85;
        }

        int len = std::min<int>(5, n - i + 1);
        res.insert(res.end(), out, out + len);
    }
    return res;
}

std::vector<uint8_t> decode(std::vector<uint8_t> const &str)
{
    std::vector<uint8_t> res;
    size_t n = str.size();

    for (size_t i = 0; i < n; i += 5)
    {
        uint64_t val = 0;
        int chunk_len = std::min<int>(5, n - i);

        if (chunk_len == 1)
        {
            throw std::invalid_argument("Invalid Base85 string length");
        }

        for (int j = 0; j < 5; ++j)
        {
            val *= 85;
            if (j < chunk_len)
            {
                const char* p = std::strchr(b85chars, str[i + j]);
                if (!p) throw std::invalid_argument("Invalid Base85 character");
                val += (p - b85chars);
            }
            else
            {
                val += 84;
            }
        }

        int out_len = chunk_len - 1;
        for (int j = 3; j >= 4 - out_len; --j)
        {
            res.push_back(static_cast<uint8_t>((val >> (j * 8)) & 0xFF));
        }
    }
    return res;
}

}