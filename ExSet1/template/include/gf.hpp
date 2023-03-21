/**
 * You can use this for programming task 2 of set 1
 */

#pragma once
#include <bitset>

namespace pfp
{

    template <class dtype>
    class gf
    {
        std::bitset<INT32_MAX> *bs;

    public:
        gf()
        {
            bs = new std::bitset<INT32_MAX>();
        }

        void insert(dtype value)
        {
            (*bs).set(value - 1);
        }

        int count(dtype value)
        {
            return (*bs)[value - 1];
        }
    };

} // namespace pfp