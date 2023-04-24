#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>

namespace pfp
{

    class vb
    {
    public:
        uint64_t numCount;

        const uint64_t maxBlocks;
        const uint64_t stopBit;

        uint64_t cap;
        uint64_t size;
        unsigned char *data;
        double growthFactor;

        vb()
            : numCount(0),
              maxBlocks(64 / 7),
              stopBit((1U << 7))
        {
            cap = 1024;
            size = 0;
            data = (unsigned char *)std::malloc(cap);
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

        void scan(uint64_t numIdx)
        {
            uint64_t result = 0;
            uint64_t i = 0;
            uint64_t curIdx = 0;
            // mask without leftmost stop bit
            const uint64_t mask = ~stopBit;

            for (uint64_t bidx = 0; bidx < size; bidx++)
            {
                auto byte = *(data + bidx);
                // check leftmost bit
                bool stop = byte & stopBit;

                result += (uint64_t)(byte & mask) << (i * 7);
                if (stop)
                {

                    if (curIdx == numIdx)
                    {
                        std::cout << result << std::endl;
                        return;
                    }

                    result = 0;
                    i = 0;
                    curIdx++;
                }
                else
                {
                    i++;
                }
            }
        }
        void sum(uint64_t numIdx)
        {
            // uint64_t result = 0;
            // uint64_t i = 0;
            // uint64_t numCount = 0;
            // const uint64_t stopBit = (1U << k);

            // for (unsigned char byte : bytes)
            // {
            //     // check leftmost bit
            //     bool stop = byte & stopBit;

            //     if (stop)
            //     {
            //         // mask without leftmost stop bit
            //         const uint64_t mask = ~stopBit;
            //         result += (uint64_t)(byte & mask) << (i * k);

            //         if (numCount == numIdx)
            //         {
            //             std::cout << result << std::endl;
            //             return;
            //         }

            //         result = 0;
            //         i = 0;
            //         numCount += 1;
            //     }
            //     else
            //     {
            //         result += (uint64_t)byte << (i * k);
            //         i++;
            //     }
            // }
        }
    };
} // namespace pfp