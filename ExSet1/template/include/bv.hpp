/**
 * You can use this for programming task 2 of set 1
 */

#pragma once
#include <vector>

namespace pfp
{

  template <class dtype>
  class bv
  {
    std::vector<bool> vec;

  public:
    bv(dtype limit)
    {
      vec = std::vector<bool>(limit, false);
    }

    void insert(dtype value)
    {
      vec[value - 1] = true;
    }

    int count(dtype value) const
    {
      return vec[value - 1];
    }
  };

} // namespace pfp