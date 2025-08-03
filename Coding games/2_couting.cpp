#include <iostream>
#include <vector>

using namespace std;

int longestStreak(vector<int> & vector)
{
  int max = 0;
  int num = 0;
  for (auto& it : vector)
  {
    if (it > max)
    {
      num = 1;
      max = it;
      continue;
    }
    if (it == max )
    {
      num ++;
    }
  }
  return num;
}


int main() {
  vector<int> example = {1, 1, 2, 2, 2, 3, 3, 1};
  cout << "Longest streak: " << longestStreak(example) << endl; // 输出：3
  return 0;
}