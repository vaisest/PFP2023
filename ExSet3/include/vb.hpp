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
        uint64_t numCount;
        uint64_t last;
        uint64_t k;

        vb(uint64_t kin)
        {
            numCount = 0;
            last = 0;
            k = kin;
        }

        void encode(std::uint64_t num)
        {
            // std::cout << "num: " << num << std::endl;

            for (int i = 0; i < 8; i++)
            {
                if (num < (1 << k))
                {
                    // output with stop bit
                    bytes.push_back(num + (1 << k));
                    break;
                }

                uint64_t block = num % (1 << k);
                // output without stop bit
                bytes.push_back(block);
                num /= (1 << k);
            }
            numCount++;
        }

        void diffEncode(std::uint64_t num)
        {
            uint64_t increase = num - last;
            encode(increase);
            last = num;
        }

        void printDecodeAll()
        {
            std::cout << bytes.size() << "\n";

            uint64_t result = 0;
            uint64_t i = 0;
            for (unsigned char byte : bytes)
            {
                // check leftmost bit
                bool stop = byte & (1 << k);

                if (stop)
                {
                    // take 7 first bits and add them times 128^i to res
                    // 1 << 7*i == pow(128, i)
                    result += (uint64_t)(byte & 0x7F) << (i * k);

                    std::cout << result << "\n";

                    result = 0;
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

        void diffPrintDecodeAll()
        {
            std::cout << bytes.size() << "\n";

            uint64_t totalResult = 0;
            uint64_t result = 0;
            uint16_t i = 0;
            for (unsigned char byte : bytes)
            {
                // check leftmost bit
                bool stop = byte >= (1 << k);

                if (stop)
                {
                    // take 7 first bits and add them times 128^i to res
                    result += (uint64_t)(byte & 0x7F) << (i * k);

                    totalResult += result;
                    std::cout << totalResult << "\n";

                    result = 0;
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