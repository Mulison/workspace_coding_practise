#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    vector<vector<int>> solutions;


    vector<vector<int>> threeSum(vector<int>& nums)
    {
      int i = 0;
      int j = 1;
      int k = nums.size()-1;

      for (; i < k-1 ; ++i)
      {
        int a = nums[k] - nums[j];
        for (; j < k ; ++j)
        {
          if ( i == j || j == k || i == k)
            break;
          if (i + j + k == 0)
          {
            solutions.push_back({i, j, k});
          }

        }
        if (j < i + 2)
          break;
        else
          j = i + 2; 
      }
      return solutions;
    }
  };

int main()
{
  Solution sol;
  vector<int> num = {-1,0,1,2,-1,-4};
  sort(num.begin(), num.end());
  auto solu = sol.threeSum(num);
}