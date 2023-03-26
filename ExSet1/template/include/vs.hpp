/**
 * You can use this file for programmign task 1 of set 1.
 */

#pragma once
#include <vector>
// #include <deque>
#include <algorithm>

namespace pfp
{

  template <class dtype>
  class vs
  {
  private:
    std::vector<dtype> vec;
    bool isSorted;

  public:
    vs()
    {
      isSorted = false;
      constexpr int elems = 1000000;
      vec.reserve(elems);
    }
    void insert(dtype val)
    {
      vec.push_back(val);
      isSorted = false;
    }

    int count(dtype val)
    {
      if (!isSorted)
      {
        std::sort(vec.begin(), vec.end());
        isSorted = true;
      }
      return std::binary_search(vec.begin(), vec.end(), val);
    }
  };

} // namespace pfp
