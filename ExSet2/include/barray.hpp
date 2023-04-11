#pragma once
#include <vector>
#include <cstdint>
#include <bit>
#include <iostream>

namespace pfp
{

    class bit_array
    {
        std::vector<std::uint64_t> vec;
        std::vector<std::uint32_t> sums;

    public:
        bit_array(std::uint64_t bits)
        {
            vec = std::vector<std::uint64_t>(bits / 64, 0);
            sums = std::vector<std::uint32_t>();
        }

        void set(std::uint64_t bit)
        {
            while (bit >= vec.size() * 64)
            {
                vec.push_back((std::uint64_t)0);
            }

            size_t idx = bit / 64;
            unsigned short offset = bit % 64;

            vec[idx] |= 1UL << (offset);
        }

        bool get(std::uint64_t bit)
        {
            if (bit >= vec.size() * 64)
            {
                return false;
            }

            size_t idx = bit / 64;
            unsigned short offset = bit % 64;
            return (vec[idx] >> (offset)) & 1UL;
        }

        void sumPreproc()
        {
            std::uint32_t total = 0;
            for (auto v : vec)
            {
                total += std::popcount(v);
                sums.push_back(total);
            }
        }

        std::uint64_t sum(size_t bits)
        {
            const std::uint64_t fulls = bits / 64;
            const std::uint64_t remain = bits % 64;

            std::uint64_t count = fulls != 0 ? sums[fulls - 1] : 0;

            std::uint64_t last = vec[fulls];
            for (size_t i = 0; i < remain; i++)
            {
                count += last & 1;
                last >>= 1;
            }

            return count;

            // const std::uint64_t fulls = bits / 64;
            // const std::uint64_t remain = bits % 64;

            // // use STL to calculate bits in the full integers
            // std::uint64_t count = 0;
            // for (uint i = 0; i < fulls; i++)
            // {
            //     count += std::popcount(vec[i]);
            // }

            // // calculate the last x % 64 bits manually
            // std::uint64_t last = vec[fulls];
            // for (uint i = 0; i < remain; i++)
            // {
            //     count += last & 1;
            //     last >>= 1;
            // }

            // return count;
        }

        size_t location(size_t bitIdx)
        {
            std::uint64_t bitCount = 0;
            size_t idx = 0;
            for (size_t i = 0; i < sums.size(); i++)
            {
                if (sums[i] >= bitIdx)
                {
                    bitCount = sums[i - 1];
                    break;
                }
                idx++;
            }
            std::uint64_t num = vec[idx];
            idx *= 64;
            while (true)
            {
                if (bitCount == bitIdx)
                {
                    return idx;
                }
                bitCount += num & 1;
                num >>= 1;
                idx++;
            }

            // std::uint64_t bitCount = 0;
            // size_t idx = 0;
            // while (true)
            // {
            //     uint ones = std::popcount(vec[idx]);
            //     if (bitCount + ones >= bitIdx)
            //     {
            //         break;
            //     }
            //     bitCount += ones;
            //     idx++;
            // }

            // std::uint64_t num = vec[idx];
            // idx *= 64;
            // while (true)
            // {
            //     if (bitCount == bitIdx)
            //     {
            //         return idx;
            //     }
            //     bitCount += num & 1;
            //     num >>= 1;
            //     idx++;
            // }
        }
    };

} // namespace pfp