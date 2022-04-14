#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const char alpArr[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char spcArr[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()";
int len_str = sizeof(alpArr) - 1;

int main()
{
  int n;
  string sc;
  cout << "Enter pass length: ";
  cin >> n;
  cout << "Do you want to add special characters? [y/n] -> ";
  cin >> sc;
  if (sc == "y")
  {
    srand(time(0));
    cout << "Pass Generation Successful: ";
    for (int i = 0; i < n; i++)
    {
      cout << spcArr[rand() % len_str];
      // cout << endl;
    }
  }
  else if (sc == "n")
  {
    srand(time(0));
    cout << "Pass Generation Successful: ";
    for (int i = 0; i < n; i++)
    {
      cout << alpArr[rand() % len_str];
      // cout << endl;
    }
  }
  else
  {
    cout << "plz choose a valid option!";
  }
  cout << endl;
  return 0;
}