#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int char_count; cin >> char_count;
    vector<int> text(char_count,0);
    for(int i = 0; i < char_count; i++){
      int temp;
      cin >> temp;
      text[i] = temp;
    }
    vector<int> pairs(char_count,0);
    int pairs_sum = 0;
    if(!text[0]){
      pairs[0] = 1;
      pairs_sum = 1;
    }
    for(int i = 1; i < char_count; i++){
      if(!text[i]){
        pairs[i] = pairs[i-1]+1;
      }
      else{
        pairs[i] = i - pairs[i-1];
      }
      pairs_sum+=pairs[i];
    }
    cout << pairs_sum;
}
