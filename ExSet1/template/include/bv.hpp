/**
 * You can use this for programming task 2 of set 1
 */

#pragma once
#include <vector>
#include <bitset>

namespace pfp
{

  template <class dtype>
  class bv
  {
    // std::vector<bool> vec;
    // std::bitset bs;
    std::vector<unsigned long> vec;

  public:
    bv(dtype limit)
    {
      // vec = std::vector<bool>(limit, false);
      // bs = std::bitset<limit>();
      vec = std::vector<unsigned long>(limit / 64, 0);
    }

    void insert(dtype value)
    {
      while ((unsigned int)value >= vec.size() * 64)
      {
        vec.push_back(0UL);
      }

      size_t idx = value / 64;
      // size_t idx = value >> 6;
      unsigned short bit = value % 64;
      // unsigned short bit = value - idx * 64;

      vec[idx] |= 1UL << (bit);
    }

    int count(dtype value) const
    {
      if ((unsigned int)value >= vec.size() * 64)
      {
        return false;
      }

      size_t idx = value / 64;
      // size_t idx = value >> 6;
      unsigned short bit = value % 64;
      // unsigned short bit = value - idx * 64;
      return (vec[idx] >> (bit)) & 1UL;
    }
  };

} // namespace pfp