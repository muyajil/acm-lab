#include <iostream>
#include <vector>

using namespace std;

int main(){
        int length; cin >> length;
        vector<int> a_array(length);
        vector<int> b_array(length);
        for(int i = 0; i < length; i++){
                int tmp; cin >> tmp;
                a_array[i] = tmp;
        }
        for(int i = 0; i < length; i++){
                int tmp; cin >> tmp;
                b_array[i] = tmp;
        }
}
