#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>

#include "base85ed.h"

static const char b85_alphabet[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

namespace base85{
    std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes)
    {
        std::vector<uint8_t> out;
        out.reserve(bytes.size() * 5 / 4 + 5);

        size_t i = 0; 
        while (i < bytes.size())
        {
            uint32_t chunk = 0;
            int bytes_count = 0;
            for (int j = 0; j < 4 && (i + j) < bytes.size(); ++j)
            {
                chunk = (chunk << 8) | bytes[i + j];
                bytes_count++;
            }
            if (bytes_count < 4) {
                chunk = chunk << ((4 - bytes_count) * 8);
            }

            uint8_t digits[5];
            for (int k = 4; k >= 0; --k) {
                digits[k] = chunk % 85;
                chunk /= 85;
            }
            for (int k = 0; k < 5; ++k) {
                if (k < bytes_count + 1) {
                    out.push_back(static_cast<uint8_t>(b85_alphabet[digits[k]]));
                }
            }

            i += 4;
        }
        return out;
    }


    std::vector<uint8_t> decode(std::vector<uint8_t> const &b85str)
    {
        std::vector<uint8_t> out;
        out.reserve(b85str.size() * 4 / 5 + 4);

        size_t i = 0;
        while (i < b85str.size())
        {
            uint64_t chunk = 0;
            int chars_count = 0;

            for (int j = 0; j < 5 && (i + j) < b85str.size(); ++j)
            {
                char c = static_cast<char>(b85str[i + j]);
                chars_count++;

                int idx = -1;

                for (int k = 0; b85_alphabet[k] != '\0'; ++k)
                {
                    if (b85_alphabet[k] == c)
                    {
                        idx = k;
                        break;
                    }
                }

                if (idx == -1)
                {
                    throw std::runtime_error("Неизвестный символ в Base85 строке");
                }

                chunk = chunk * 85 + idx;
            }

            int padding = 5 - chars_count;
            for (int k = 0; k < padding; ++k)
            {
                chunk = chunk * 85 + 84;
            }

            int bytes_to_output =
                (chars_count <= 1) ? 0 : chars_count - 1;

            for (int j = 0; j < bytes_to_output; ++j)
            {
                out.push_back(
                    static_cast<uint8_t>(
                        (chunk >> (24 - j * 8)) & 0xFF
                    )
                );
            }

            i += chars_count;
        }

        return out;
    }
}
