#pragma once
#include <vector>
#include <cstdint>

namespace pfp
{

    class packed_array
    {
        // std::vector<bool> bits;

        size_t lastInsertBit;
        std::vector<std::uint64_t> ints;

        size_t width;

    public:
        packed_array(size_t bitsPerElem, size_t entryCount)
        {
            width = bitsPerElem;

            size_t intCount = 1 + ((width * entryCount) / 64);
            ints = std::vector<std::uint64_t>(intCount, 0);
            // ints = std::vector<std::uint64_t>(intCount, UINT64_MAX);
            // for (auto i : ints)
            // {
            //     std::cout << i << std::endl;
            // }
            // std::cout << ints.size() << std::endl;
            lastInsertBit = 0;
        }

        void append(std::uint64_t num)
        {
            // for (size_t i = 0; i < width; i++)
            // {
            //     bool bit = ((num >> i) & 1);
            //     bits.push_back(bit);
            // }
            for (size_t i = 0; i < width; i++)
            {
                bool bit = ((num >> i) & 1);
                // bool bit = 0;
                const size_t idx = (lastInsertBit + i) / 64;
                const size_t offset = (lastInsertBit + i) % 64;
                ints[idx] |= bit << (offset);
            }
            lastInsertBit += width;
        }

        std::uint64_t get(std::uint64_t entry)
        {
            // const size_t bitIdx = width * entry;
            // std::uint64_t num = 0;
            // for (size_t i = 0; i < width; i++)
            // {
            //     num |= (bits[bitIdx + i] << i);
            // }
            // return num;

            std::uint64_t num = 0;
            const size_t startBit = entry * width;
            for (size_t i = 0; i < width; i++)
            {
                size_t targetBit = i + startBit;
                size_t intIdx = targetBit / 64;
                size_t offset = targetBit % 64;
                bool bit = (ints[intIdx] >> offset) & 1;
                std::cout << targetBit << "/" << ints[intIdx] << "/" << intIdx << "/" << offset << "/" << width << "/" << bit << " "
                          << std::endl;
                num |= (bit << i);
            }
            // std::cout << std::endl;
            // std::cout << std::endl;
            return num;
        }
    };
} // namespace pfp