#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        // for (int i = 0; i < nums.size(); i++)
        // {
        //     if (nums[i] == target)
        //         return i;
        //     if (nums[i] > target)
        //         return -1;
        // }
        // return -1;

        int left = 0;
        int right = nums.size()-1;        
        while (left <= right )
        {
            int middle = (left + right) /2;
            if (target < nums[middle])
                right = middle-1;
            else if (nums[middle] < target)
                left = middle +1;
            else
                return middle;
        }
        return -1;
    }
};


int main()
{
  Solution sol;
  vector<int> nums = {-1,0,3,5,9,12};
  int target = 9;
  auto ret = sol.search(nums, target);  
}