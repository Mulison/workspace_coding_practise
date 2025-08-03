#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> matrix;
    int order;
public:
    vector<vector<int>> generateMatrix(int n) {
      order = n;
      matrix = vector<vector<int>>(n, vector<int>(n, 0));

      // iteration
      // int i = 1;
      int row = 0;
      int colnum = 0;
      int value = 1;

      while (value <= n)
      {
      
        // 1) direction right
        // total number: n
        goRight(row, colnum, colnum + order -1, value);

        // 2) direction downwards 
        // total number: n-1
        // total number : nlast column n --> 

        // 3) direction left 
        // total number: n-1
        // last column n --> 

        // 4) direction upwards
        // total number: n-2

      }
    }

    void goRight(int firstRow, int firstColnum, int endColnum, int firstValue)
    {
      int currentColnum = firstColnum;
      for (int currentValue = firstValue; currentValue <= (endColnum - firstColnum + 1) ; currentValue++)
      {
        write(firstRow, currentColnum, currentValue);
        currentColnum++;
      }

    }


    void write(int row, int colnum, int value)
    {
      matrix[row][colnum] = value; 

    }
    
};

int main()
{
  Solution sol;
  vector<vector<int>> result;

  int n = 3;  
  result = sol.generateMatrix(n);

}