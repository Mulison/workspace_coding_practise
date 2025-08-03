#include <iostream>
#include <vector>
using namespace std;


class Solution {
    public:
        void moveZeroes(vector<int>& nums)
        {
          // iterate the array, if the element is zero, then swap it with the second element
          for (int j = 0; j < nums.size()-1; j++)
          {
            for (int i = 0; i < nums.size()-1; i++)
            {
              if (nums[i] == 0)
              {
                int swap = nums[i];
                nums[i] = nums[i+1];
                nums[i+1] = swap;
              }
            }
          }
          
          // for (int i = 0; i < nums.size(); i++)
          // {
          //   cout << nums[i] << " ";
          // }
        }
    };


int main()
{
  Solution sol;
  // vector<int> numbers = {3,2,2,3};
  // int val = 3;
  vector<int> numbers = {0};
  sol.moveZeroes(numbers);
}