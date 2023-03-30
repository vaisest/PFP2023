#pragma once
#include <vector>
#include <bitset>

namespace pfp
{

    class bit_array
    {
        std::vector<unsigned long> vec;

    public:
        bit_array(ulong bits)
        {
            vec = std::vector<unsigned long>(bits / 64, 0);
        }

        void set(ulong bit)
        {
            while (bit >= vec.size() * 64)
            {
                vec.push_back(0UL);
            }

            size_t idx = bit / 64;
            unsigned short offset = bit % 64;

            vec[idx] |= 1UL << (offset);
        }

        int get(ulong bit) const
        {
            if (bit >= vec.size() * 64)
            {
                return false;
            }

            size_t idx = bit / 64;
            unsigned short offset = bit % 64;
            return (vec[idx] >> (offset)) & 1UL;
        }
    };

} // namespace pfp