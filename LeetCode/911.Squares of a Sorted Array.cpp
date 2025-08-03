#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0;
        int right  = nums.size()-1;
        vector<int> num;
        while (left <= right)
        {
            int left_squ = nums[left]*nums[left];
            int right_squ = nums[right]*nums[right];

            if ( left_squ < right_squ )
            {
                num.push_back(right_squ);
                right --;
            }
            else
            {
                num.push_back(left_squ);
                left ++;
            }
        }
        
        // reverse the array
        vector<int> result;
        for (int i = num.size()-1; i >= 0; i--)
        {
          result.push_back(num[i]);
        }

        return result;

    }
};

int main()
{
  Solution sol;
  vector<int> nums = {-4,-1,0,3,10};
  auto ret = sol.sortedSquares(nums);  
}