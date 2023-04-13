#pragma once
#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>

namespace pfp
{

    template <typename INT_T>
    class vb
    {

    public:
        std::vector<INT_T> bytes;
        uint64_t k;
        bool diffed;
        uint64_t numCount;
        uint64_t last;

        vb(std::uint64_t kk, bool ddiffed)
            : k(kk),
              diffed(ddiffed),
              numCount(0),
              last(0)
        {
        }

        void encode(std::uint64_t num)
        {
            const uint64_t maxBlocks = 64 / k;
            const uint64_t stopBit = (1U << k);

            if (diffed)
            {
                const auto temp = num;
                num = num - last;
                last = temp;
            }

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

        void printDecodeAll()
        {
            std::cout << bytes.size() << "\n";

            uint64_t result = 0;
            uint64_t i = 0;
            const uint64_t stopBit = (1U << k);

            for (INT_T byte : bytes)
            {
                // check leftmost bit
                bool stop = byte & stopBit;

                if (stop)
                {
                    // mask without leftmost stop bit
                    const uint64_t mask = ~stopBit;
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