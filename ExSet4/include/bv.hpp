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
    std::vector<unsigned char> vec;

  public:
    bv(dtype limit)
    {
      vec = std::vector<unsigned char>(limit / 8, 0);
    }

    void insert(dtype value)
    {
      while ((unsigned int)value >= vec.size() * 8)
      {
        vec.push_back((unsigned char)0);
      }

      size_t idx = value / 8;
      unsigned short bit = value % 8;

      vec[idx] |= 1UL << (bit);
    }

    int count(dtype value) const
    {
      if ((unsigned int)value >= vec.size() * 8)
      {
        return false;
      }

      size_t idx = value / 8;
      unsigned short bit = value % 8;
      return (vec[idx] >> (bit)) & 1UL;
    }
  };
} // namespace pfp