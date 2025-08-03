#include <vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {

      // int sum = 0;
      // int minimumSize = nums.size();
      // for (int end = 0; end < nums.size() ; end ++)
      // {
      //   sum += nums[end];        
      //   if (sum >= target)
      //   {
      //     for (int start = 0; start <= end; start ++)
      //     {
      //       sum -= nums[start];
      //       if (sum <= target)
      //         minimumSize = end - start + 1;
      //     }
      //   }
      // }
      // return minimumSize;

      int sum = 0;
      int minimum = 0;
      bool minimumExist = false;
      int start = 0;
      int end = 0;

      for (; end < nums.size(); end++)
      {
        sum += nums[end];
        if (sum >= target)
        {
          for (; start <= end; start++)
          {
            if (sum - nums[start] < target)  // found, which means, the current start should kept
            {
              if (!minimumExist)
              {
                minimum = end - start +1;
                minimumExist = true;
              }
              else if (minimumExist && (minimum > end - start +1))
                minimum = end - start +1;
              break;
            }
            else     //  substracted the current start, the remaining still greater or equal the target
              sum -= nums[start];
          }
        }

      }

      return minimum;
        
    }
};

int main()
{
  Solution sol;
  vector<int> nums1 = {2,3,1,2,4,3};
  int target1 = 7;
  auto ret = sol.minSubArrayLen(target1, nums1);  

  vector<int> nums2 = {1,4,4};
  int target2 = 4;
  auto ret2 = sol.minSubArrayLen(target2, nums2);  

  vector<int> nums3 = {5,1,3,5,10,7,4,9,2,8};
  int target3 = 15;
  auto ret3 = sol.minSubArrayLen(target3, nums3);  

  
}