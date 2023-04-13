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

        vb()
        {
            numCount = 0;
        }

        void encode(std::uint64_t num)
        {
            // std::cout << "num: " << num << std::endl;

            for (int i = 0; i < 8; i++)
            {
                uint64_t block = num % 128;
                if (num < 128)
                {
                    // output with stop bit
                    bytes.push_back(block + 128);
                    break;
                }
                // output without stop bit
                bytes.push_back(block);
                num /= 128;
            }
            numCount++;
        }

        void printDecodeAll()
        {
            std::cerr << bytes.size() << "\n";
            uint64_t result = 0;
            uint16_t i = 0;
            for (unsigned char byte : bytes)
            {
                // check leftmost bit
                bool stop = byte >= 128;
                // std::cout << (uint32_t)byte << "/" << stop << std::endl;

                if (stop)
                {
                    // take 7 first bits and add them times 128^i to res
                    result += (byte - 128) * pow(128, i);

                    std::cerr << result << "\n";

                    result = 0;
                    i = 0;
                }
                else
                {
                    result += byte * pow(128, i);
                    i++;
                }
            }
            std::cerr << std::flush;
        }

        // for (int i = 0; i < 8; i++)
        // {
        //     blockCount++;
        //     // copy a byte at a time
        //     uint8_t byte = (num >> (8 * i)) & 0xFF;

        //     // check leftmost bit
        //     bool stop = byte >= 128;
        //     std::cout << (uint32_t)byte << "/" << stop << std::endl;

        //     if (stop)
        //     {
        //         // take 7 first bits and add them times 128^i to res
        //         result += (byte - 128) * pow(128, i);
        //         break;
        //     }
        //     else
        //     {
        //         result += byte * pow(128, i);
        //     }
        // }
        // vec.push_back(result);
    };
} // namespace pfp