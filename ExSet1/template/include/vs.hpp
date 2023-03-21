/**
 * You can use this file for programmign task 1 of set 1.
 */

#pragma once
#include <vector>
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
      // std::vector<dtype> vec;
      isSorted = false;
    }
    void insert(dtype val)
    {
      vec.push_back(val);
      isSorted = false;
    }

    // void change_query_mode()
    // {
    //   std::sort(vec.begin(), vec.end());
    // }

    int count(dtype val)
    {
      if (!isSorted)
      {
        std::sort(vec.begin(), vec.end());
      }
      isSorted = true;
      return std::binary_search(vec.begin(), vec.end(), val);
    }
  };

} // namespace pfp
