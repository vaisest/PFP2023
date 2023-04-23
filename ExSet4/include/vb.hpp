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
        std::vector<unsigned char> bytes;
        uint64_t k;
        // bool diffed;
        uint64_t numCount;
        uint64_t last;
        struct Layer
        {
            int control;
            unsigned char blocks[8];
        };

        vb(std::uint64_t kk)
            : k(kk),
              numCount(0),
              last(0)
        {
        }

        void encode(std::uint64_t num)
        {
            const uint64_t maxBlocks = 64 / k;
            const uint64_t stopBit = (1U << k);

            for (uint i = 0; i < maxBlocks; i++)
            {
                if (num < stopBit)
                {
                    // output with stop bit
                    bytes.push_back(num + stopBit);
                    break;
                }

                uint64_t block = num % stopBit;
                // output without stop bit
                bytes.push_back(block);
                num /= stopBit;
            }
            numCount++;
        }

        void scan(uint64_t numIdx)
        {
            uint64_t result = 0;
            uint64_t i = 0;
            uint64_t numCount = 0;
            const uint64_t stopBit = (1U << k);

            for (unsigned char byte : bytes)
            {
                // check leftmost bit
                bool stop = byte & stopBit;

                if (stop)
                {
                    // mask without leftmost stop bit
                    const uint64_t mask = ~stopBit;
                    result += (uint64_t)(byte & mask) << (i * k);

                    if (numCount == numIdx)
                    {
                        std::cout << result << std::endl;
                        return;
                    }

                    result = 0;
                    i = 0;
                    numCount += 1;
                }
                else
                {
                    result += (uint64_t)byte << (i * k);
                    i++;
                }
            }
        }
        void sum(uint64_t numIdx)
        {
            uint64_t result = 0;
            uint64_t i = 0;
            uint64_t numCount = 0;
            const uint64_t stopBit = (1U << k);

            for (unsigned char byte : bytes)
            {
                // check leftmost bit
                bool stop = byte & stopBit;

                if (stop)
                {
                    // mask without leftmost stop bit
                    const uint64_t mask = ~stopBit;
                    result += (uint64_t)(byte & mask) << (i * k);

                    if (numCount == numIdx)
                    {
                        std::cout << result << std::endl;

                        return;
                    }

                    result = 0;
                    i = 0;
                    numCount += 1;
                }
                else
                {
                    result += (uint64_t)byte << (i * k);
                    i++;
                }
            }
        }
    };
} // namespace pfp