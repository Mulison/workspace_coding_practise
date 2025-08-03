#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
      int k = 2;  // the elements before k are affective

      for (int i = 2; i< nums.size(); ++i)
      {
        if (nums[i] == nums[k-1])  // 
        {
          if (nums[i-1] == nums[k-2])
          {
            continue;
          }
          nums[k]=nums[i];
          k++;
          continue;
        }
        nums[k]=nums[i];
        k++;
      }
      return k;
    }
};

int main()
{
  Solution sol;
  // vector<int> numbers = {3,2,2,3};
  // int val = 3;
  vector<int> numbers = {1,1,1,2,2,3};

  int k = sol.removeDuplicates(numbers);

}