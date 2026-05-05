#ifndef __BASE85ED__
#define __BASE85ED__

#include <vector>
#include <cstdint>

namespace base85
{
    /**
     * @brief Encodes bytes into a Base85.
     */
    std::vector<uint8_t> encode(std::vector<uint8_t> const &bytes);

    /**
     * @brief Decodes Base85 to bytes.
     */
    std::vector<uint8_t> decode(std::vector<uint8_t> const &b85str);
} // namespace base85

#endif // __BASE85ED__