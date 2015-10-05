#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<int> primesieve (int high){
  vector<int> numbers(high,0);
  numbers[0]=1;
  numbers[1]=1;
  for (int i = 2; i <= high; i++){
    if (!numbers[i]) {
      for(int j=2*i; j <= high; j+=i){
        numbers[j]=1;
      }
    }
  }
  return numbers;
}

int main() {
    int num_testcases;
    cin >> num_testcases;
    while(num_testcases--){
      int lower, higher; cin >> lower >> higher;
      if (higher){
        vector<int> primes = primesieve(higher);
        for (int k = lower; k <= higher; k++){
          if (!primes[k]){
            cout << k << endl;
          }
          else{}
        }
      }
    }
}
