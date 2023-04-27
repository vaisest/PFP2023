#pragma once
// #include <vector>
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <span>
#include <vector>

namespace pfp
{

    class vb
    {
    public:
        uint64_t numCount;

        const uint64_t maxBlocks;
        const uint64_t stopBit;

        // uint64_t cap;
        // uint64_t size;
        // unsigned char *data;
        // double growthFactor;

        std::vector<bool> bs[8];
        // std::vector<uint32_t> bsums[8];
        // std::vector<unsigned char> as[8];

        // std::span<bool> bs[8];
        // bool *bs[8];
        // size_t bsSizes[8];
        // size_t bsCaps[8];

        // std::span<uint32_t> bsums[8];
        uint32_t *bsums[8];
        size_t bsumsSizes[8];
        size_t bsumsCaps[8];

        // std::span<unsigned char> as[8];
        unsigned char *as[8];
        size_t asSizes[8];
        size_t asCaps[8];

        vb()
            : numCount(0),
              maxBlocks(8),
              stopBit((1U << 7))
        {
            for (int i = 0; i < 8; i++)
            {
                // bs[i] = (bool *)std::malloc(32 * sizeof(bool));
                // // bs[i] = {(bool *)std::malloc(32 * sizeof(bool)), 32};
                // bsSizes[i] = 0U;
                // bsCaps[i] = 32U;

                bsums[i] = (uint32_t *)std::malloc(32 * sizeof(uint32_t));
                // bsums[i] = {(uint32_t *)std::malloc(32 * sizeof(uint32_t)), 32};
                bsumsSizes[i] = 0U;
                bsumsCaps[i] = 32U;

                as[i] = (unsigned char *)std::malloc(32 * sizeof(unsigned char));
                // as[i] = {(unsigned char *)std::malloc(32 * sizeof(unsigned char)), 32};
                asSizes[i] = 0U;
                asCaps[i] = 32U;
            }
        }

        template <typename T>
        void inline pushBack(T *&data, T item, size_t &curSize, size_t &curCap)
        {
            double growthFactor = 1.5;
            if (curSize == curCap)
            {
                curCap = (size_t)((curCap)*growthFactor);

                data = (T *)std::realloc(data, curCap * sizeof(T));

                if (data == nullptr) [[unlikely]]
                {
                    std::cout << "AAA PANIC!!!" << data << "/" << curSize << "/" << curCap << "/" << item << std::endl;
                    exit(666);
                }
            }

            *(data + curSize) = item;

            curSize++;
        }

        void
        encode(uint64_t num)
        {
            for (uint i = 0; i < maxBlocks; i++)
            {
                // auto temp = bs[i];
                if (num < stopBit)
                {
                    // output with stop bit
                    bs[i].push_back(true);
                    // pushBack(bs[i], true, bsSizes[i], bsCaps[i]);

                    if (bsumsSizes[i] == 0) [[unlikely]]
                    {
                        pushBack(bsums[i], 1U, bsumsSizes[i], bsumsCaps[i]);
                        // bsums[i].push_back(1);
                    }
                    else
                    {
                        pushBack(bsums[i], *(bsums[i] + bsumsSizes[i] - 1) + 1U, bsumsSizes[i], bsumsCaps[i]);
                        // bsums[i].push_back(bsums[i].back() + 1);
                    }

                    pushBack(as[i], (unsigned char)num, asSizes[i], asCaps[i]);
                    // as[i].push_back(num);
                    break;
                }

                uint64_t block = num % stopBit;
                // output without stop bit
                // pushBack(bs[i], false, bsSizes[i], bsCaps[i]);
                bs[i].push_back(false);

                // if (bsums[i].empty()) [[unlikely]]
                if (bsumsSizes[i] == 0) [[unlikely]]
                {
                    pushBack(bsums[i], 1U, bsumsSizes[i], bsumsCaps[i]);
                    // bsums[i].push_back(1);
                }
                else
                {
                    pushBack(bsums[i], *(bsums[i] + bsumsSizes[i] - 1) + 0U, bsumsSizes[i], bsumsCaps[i]);
                    // bsums[i].push_back(bsums[i].back() + 0);
                }

                pushBack(as[i], (unsigned char)block, asSizes[i], asCaps[i]);
                // as[i].push_back(block);
                // num /= stopBit;
                num >>= 7;
            }
            numCount++;
        }

        // void scan(uint64_t numIdx)
        // {
        //     uint64_t result = 0;
        //     uint64_t i = 0;
        //     uint64_t curIdx = 0;
        //     // mask without leftmost stop bit
        //     const uint64_t mask = ~stopBit;

        //     for (uint64_t bidx = 0; bidx < size; bidx++)
        //     {
        //         auto byte = *(data + bidx);
        //         // check leftmost bit
        //         bool stop = byte & stopBit;

        //         result += (uint64_t)(byte & mask) << (i * 7);
        //         if (stop)
        //         {

        //             if (curIdx == numIdx)
        //             {
        //                 std::cout << result << std::endl;
        //                 return;
        //             }

        //             result = 0;
        //             i = 0;
        //             curIdx++;
        //         }
        //         else
        //         {
        //             i++;
        //         }
        //     }
        // }

        void sum(uint64_t numIdx) const
        {
            uint64_t result = 0;

            for (uint64_t i = 0; i < maxBlocks; i++)
            {
                const bool stop = bs[i][numIdx];
                // const bool stop = *(bs[i] + numIdx);
                result += *(as[i] + numIdx) << (i * 7);

                if (stop) [[likely]]
                {
                    std::cout << result << "\n";
                    return;
                }

                // ones before numIdx
                numIdx -= *(bsums[i] + numIdx);
            }
        }

        // void sum(uint64_t numIdx)
        // {
        //     // uint64_t result = 0;
        //     // uint64_t i = 0;
        //     // uint64_t numCount = 0;
        //     // const uint64_t stopBit = (1U << k);

        //     // for (unsigned char byte : bytes)
        //     // {
        //     //     // check leftmost bit
        //     //     bool stop = byte & stopBit;

        //     //     if (stop)
        //     //     {
        //     //         // mask without leftmost stop bit
        //     //         const uint64_t mask = ~stopBit;
        //     //         result += (uint64_t)(byte & mask) << (i * k);

        //     //         if (numCount == numIdx)
        //     //         {
        //     //             std::cout << result << std::endl;
        //     //             return;
        //     //         }

        //     //         result = 0;
        //     //         i = 0;
        //     //         numCount += 1;
        //     //     }
        //     //     else
        //     //     {
        //     //         result += (uint64_t)byte << (i * k);
        //     //         i++;
        //     //     }
        //     // }
        // }
    };
} // namespace pfp