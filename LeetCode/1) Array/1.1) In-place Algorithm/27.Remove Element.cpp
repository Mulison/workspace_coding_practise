#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {

        sort(nums.begin(), nums.begin() + nums.size());
        int k = 0;
        int i = 0;
        int n = nums.size();

        // while ( i < n)
        // {
        //     if (nums[i] == val)
        //     {
        //         k ++;
        //         nums[i] = nums[n-1];
        //         n --;
        //         continue;
        //     }

        //     i++;
        // }

        for (; i < n ; ++i)
        {
          if (nums[i] != val)
          {
            nums[k] = nums[i];
            k ++; 
          }
        }


        return k;
    }

    int removeElement2(vector<int>& nums, int target)
    {
      int index = 0;
      int right = nums.size()-1;
      while (index < right)
      {
        if (nums[index] == target)
        {
          nums[index] = nums[right];
          right --;
        }
        else 
          index ++;
      }
      return right+1;

    }
  };

int main()
{
  Solution sol;
  // vector<int> numbers = {3,2,2,3};
  // int val = 3;
  vector<int> numbers = {0,1,2,2,3,0,4,2};
  int val = 2;
  int k = sol.removeElement2(numbers, val);

}