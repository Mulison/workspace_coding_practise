#include <iostream>
#include <vector>
using namespace std;

// 1. write a function to transform a "n" into a 4-element arry

void function_1(int input)
{  
  int a[4];
  int n = 3;
  while ( input % 10 > 0)
  {
      a[n] = input % 10;
      input /= 10;
      n--;
  }
  return;
}

// 2. write a function to know if a number "n" is a prime number or not. 
// The function returns 1 if it is a prime number, 0 otherwise

bool function_2(int input)
{
  bool status = true;

  for (int i = 2; i < input ; i++)
  {
    if (input % i == 0)
    {
      status = false;
      break;
    }
  }
  return status;
}

// 3. write a funciton returning an array of all prime numbers within 
// a given interval (e.g. interval is [1-9999])

vector<int> function_3(int start, int end)
{
  vector<int> list;
  for (int i = start; i<= end; i++)
  {
    if (function_2(i))
    {
      list.push_back(i);
    }
  }
  return list;
}


int main()
{
  // function_1(1487);
  // bool result = function_2(9);
  vector<int> result = function_3(1, 999);

  int a = 0;

  return 0;
}