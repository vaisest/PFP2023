/**
 * You can use this for programming task 2 of set 1
 */

#pragma once
// #include <bitset>
// #include <unordered_map>
// #include "bv.hpp"
#include <vector>
#include <set>

namespace pfp
{

    template <class dtype>
    class gf
    {
        // std::unordered_map<uint, pfp::bv<int>> blockMap;
        // // std::unordered_map<uint, unsigned long> blockMap;
        // // static const uint blockPower = 14;
        // static const uint blockSize = 128;

        // vec of buckets, i.e. a vector vector aka vecVec
        std::vector<std::vector<int>> vecVec;
        // std::vector<std::set<int>> setVec;

    private:
        int hash(int val)
        {
            return val % vecVec.size();
            // return val % setVec.size();
        }

    public:
        gf()
        {
            // around 100 000 buckets seems to perform the best for test 4
            const size_t bucketSize = (1 << 16);
            // const size_t bucketSize = 100003; // prime

            // a set is also quick, but
            // results are seemingly super random
            // 2^12: 3.54s
            // 2^14: 3.20s
            // 2^16: 1.71s
            // 2^17: 1.42s
            // 2^18: 3.26s
            // 2^19: 1.71s
            // 131101: 1.64s
            // 100003: 1.51s
            //  75001: 1.84
            //  70009: 1.35
            //  65003: 3.14
            //  50021: 3.07

            vecVec.resize(bucketSize);
            // setVec.resize(bucketSize);
        }

        void insert(dtype value)
        {
            // // divide by 2^blockSize because each block has that many values
            // // const uint blockIdx = value >> blockPower;
            // const uint blockIdx = value / blockSize;
            // // const uint blockIdx = value >> 6;
            // // offset is value from block start, i.e. (value - blockIdx * blockSize)
            // // const uint offset = value - blockIdx * (1 << blockPower);
            // const uint offset = value - blockIdx * blockSize;
            // // const uint offset = value - blockIdx * 64;

            // try
            // {
            //     blockMap.at(blockIdx).insert(offset);
            //     // ulong original = blockMap.at(blockIdx);
            //     // blockMap[blockIdx] |= 1UL << (offset);
            // }
            // catch (const std::out_of_range &e)
            // {
            //     // pfp::bv<int> block = bv(1 << blockPower);
            //     pfp::bv<int> block = bv((int)blockSize);
            //     block.insert(offset);
            //     blockMap.insert(std::make_pair(blockIdx, block));
            //     // ulong newNum = 1UL << (offset);
            //     // blockMap.insert(std::make_pair(blockIdx, newNum));
            // }

            // which bucket
            int bIdx = hash(value);
            for (size_t i = 0; i < vecVec[bIdx].size(); i++)
            {
                if (vecVec[bIdx][i] == value)
                {
                    return;
                }
            }
            vecVec[bIdx].push_back(value);
            // setVec[bIdx].insert(value);
        }

        int count(dtype value)
        {
            // // const uint blockIdx = value >> blockPower;
            // const uint blockIdx = value / blockSize;
            // // const uint blockIdx = value >> 6;
            // // const uint offset = value - blockIdx * (1 << blockPower);
            // const uint offset = value - blockIdx * blockSize;
            // // const uint offset = value - blockIdx * 64;

            // // if (blockIdx >= blockMap.size())
            // // {
            // //     return 0;
            // // }
            // // return (blockMap[blockIdx] >> offset) & 1UL;
            // try
            // {
            //     pfp::bv<int> block = blockMap.at(blockIdx);
            //     return block.count(offset);
            // }
            // catch (std::out_of_range &e)
            // {
            //     return 0;
            // }
            int bIdx = hash(value);
            for (size_t i = 0; i < vecVec[bIdx].size(); i++)
            {
                if (vecVec[bIdx][i] == value)
                {
                    return true;
                }
            }
            return false;
            // return setVec[bIdx].count(value);
        }
    };

} // namespace pf