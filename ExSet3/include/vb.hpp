#pragma once
// #include <vector>
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <iostream>

namespace pfp
{

    template <typename INT_T>
    class vb
    {

    public:
        uint64_t k;
        bool diffed;
        uint64_t numCount;

        uint64_t last;
        const uint64_t maxBlocks;
        const uint64_t stopBit;

        unsigned char *data;
        uint64_t cap;
        uint64_t size;
        double growthFactor;

        vb(std::uint64_t kk, bool ddiffed)
            : k(kk),
              diffed(ddiffed),
              numCount(0),
              last(0),
              maxBlocks(64 / k),
              stopBit((1U << k))
        {
            data = (unsigned char *)std::malloc(50);
            cap = 50;
            size = 0;
            growthFactor = 1.5;
        }

        void inline pushBack(unsigned char byte)
        {
            if (size == cap)
            {
                // std::cout << cap << "/extendingto/" << (uint64_t)(cap * growthFactor) << std::endl;
                cap = (uint64_t)(cap * growthFactor);
                data = (unsigned char *)std::realloc(data, cap);
            }

            *(data + size) = byte;

            size++;
        }

        void encode(std::uint64_t num)
        {
            for (uint i = 0; i < maxBlocks; i++)
            {
                if (num < stopBit)
                {
                    // output with stop bit
                    pushBack(num + stopBit);
                    break;
                }

                uint64_t block = num % stopBit;
                // output without stop bit
                pushBack(block);
                num /= stopBit;
            }
            numCount++;
        }

        void diffEncode(std::uint64_t num)
        {
            const auto temp = num;
            num = num - last;
            last = temp;

            encode(num);
        }

        void printDecodeAll()
        {
            std::cerr << size << std::endl;

            uint64_t result = 0;
            uint64_t i = 0;
            // mask without leftmost stop bit
            const uint64_t mask = ~stopBit;

            for (uint64_t bidx = 0; bidx < size; bidx++)
            {
                auto byte = *(data + bidx);
                // check leftmost bit
                bool stop = byte & stopBit;

                if (stop)
                {
                    result += (uint64_t)(byte & mask) << (i * k);

                    std::cout << result << "\n";

                    if (!diffed)
                    {
                        result = 0;
                    }
                    i = 0;
                }
                else
                {
                    result += (uint64_t)byte << (i * k);
                    i++;
                }
            }
            std::cout << std::flush;
        }
    };
} // namespace pfp