#include <vector>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <cstring>

#include "base85ed.h"

// Официальный алфавит RFC 1924
static const char ALPHABET[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#$%&()*+-;<=>?@^_`{|}~";

std::vector<uint8_t> base85::encode(std::vector<uint8_t> const &bytes)
{
    std::vector<uint8_t> result;
    size_t i = 0;
    size_t size = bytes.size();

    while (i < size) {
        size_t rem = size - i;
        
        if (rem >= 4) {
            // Собираем полноценный 32-битный блок (Big-endian)
            uint32_t val = (static_cast<uint32_t>(bytes[i]) << 24) |
                           (static_cast<uint32_t>(bytes[i+1]) << 16) |
                           (static_cast<uint32_t>(bytes[i+2]) << 8) |
                           (static_cast<uint32_t>(bytes[i+3]));
            i += 4;
            
            // Разделяем на 5 символов по основанию 85
            uint32_t d4 = val % 85; val /= 85;
            uint32_t d3 = val % 85; val /= 85;
            uint32_t d2 = val % 85; val /= 85;
            uint32_t d1 = val % 85; val /= 85;
            uint32_t d0 = val % 85;
            
            result.push_back(ALPHABET[d0]);
            result.push_back(ALPHABET[d1]);
            result.push_back(ALPHABET[d2]);
            result.push_back(ALPHABET[d3]);
            result.push_back(ALPHABET[d4]);
        } else {
            // Математически верная обработка неполного блока (1, 2 или 3 байта)
            uint32_t val = 0;
            val |= (static_cast<uint32_t>(bytes[i]) << 24);
            if (rem > 1) val |= (static_cast<uint32_t>(bytes[i+1]) << 16);
            if (rem > 2) val |= (static_cast<uint32_t>(bytes[i+2]) << 8);
            i += rem;
            
            uint32_t d4 = val % 85; val /= 85;
            uint32_t d3 = val % 85; val /= 85;
            uint32_t d2 = val % 85; val /= 85;
            uint32_t d1 = val % 85; val /= 85;
            uint32_t d0 = val % 85;
            
            char block[5] = {
                static_cast<char>(ALPHABET[d0]),
                static_cast<char>(ALPHABET[d1]),
                static_cast<char>(ALPHABET[d2]),
                static_cast<char>(ALPHABET[d3]),
                static_cast<char>(ALPHABET[d4])
            };
            
            // Записываем ровно rem + 1 символов
            for (size_t j = 0; j < rem + 1; ++j) {
                result.push_back(block[j]);
            }
        }
    }
    return result;
}

std::vector<uint8_t> base85::decode(std::vector<uint8_t> const &b85str)
{
    // Таблица быстрого обратного поиска символов
    std::vector<int> rev(256, -1);
    for (int idx = 0; idx < 85; ++idx) {
        rev[static_cast<unsigned char>(ALPHABET[idx])] = idx;
    }

    std::vector<uint8_t> result;
    size_t i = 0;
    size_t size = b85str.size();

    while (i < size) {
        size_t rem_chars = size - i;
        if (rem_chars >= 5) {
            uint64_t val = 0;
            for (size_t j = 0; j < 5; ++j) {
                int digit = rev[b85str[i + j]];
                if (digit == -1) {
                    throw std::runtime_error("Invalid base85 character encountered");
                }
                val = val * 85 + digit;
            }
            if (val > 0xFFFFFFFF) {
                throw std::runtime_error("Base85 value overflow (> 32-bit)");
            }
            result.push_back((val >> 24) & 0xFF);
            result.push_back((val >> 16) & 0xFF);
            result.push_back((val >> 8) & 0xFF);
            result.push_back(val & 0xFF);
            i += 5;
        } else {
            if (rem_chars == 1) {
                throw std::runtime_error("Invalid base85 string length");
            }
            
            uint64_t val = 0;
            for (size_t j = 0; j < 5; ++j) {
                int digit = 0;
                if (j < rem_chars) {
                    digit = rev[b85str[i + j]];
                    if (digit == -1) {
                        throw std::runtime_error("Invalid base85 character encountered");
                    }
                } else {
                    digit = 84; // Заполнение символом '~' согласно спецификации
                }
                val = val * 85 + digit;
            }
            if (val > 0xFFFFFFFF) {
                throw std::runtime_error("Base85 value overflow (> 32-bit)");
            }
            
            uint8_t bytes[4] = {
                static_cast<uint8_t>((val >> 24) & 0xFF),
                static_cast<uint8_t>((val >> 16) & 0xFF),
                static_cast<uint8_t>((val >> 8) & 0xFF),
                static_cast<uint8_t>(val & 0xFF)
            };
            
            for (size_t j = 0; j < rem_chars - 1; ++j) {
                result.push_back(bytes[j]);
            }
            i += rem_chars;
        }
    }
    return result;
}
