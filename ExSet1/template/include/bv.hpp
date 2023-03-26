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
      // std::cout << idx << "/" << bit << std::endl;

      vec[idx] |= 1UL << (bit);
      // std::cout << "newnum" << vec[idx] << std::endl;
    }

    int count(dtype value) const
    {
      if ((unsigned int)value >= vec.size() * 64)
      {
        // std::cout << "falsed" << std::flush;
        return false;
      }

      size_t idx = value / 64;
      // size_t idx = value >> 6;
      unsigned short bit = value % 64;
      // unsigned short bit = value - idx * 64;
      // std::cout << idx << "num" << vec[idx] << "bit" << bit << "ret" << ((vec[idx] >> (bit)) & 1UL) << std::flush;
      return (vec[idx] >> (bit)) & 1UL;
    }
  };

} // namespace pfp