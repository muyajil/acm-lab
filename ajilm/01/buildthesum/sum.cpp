#include <iostream>

using namespace std;

int main(){
    int testcases;
    cin >> testcases;
    for(int i = 0; i < testcases; i++ ){
        int numbercount;
        cin >> numbercount;
        float result=0.0;
        for(int j = 0; j < numbercount; j++){
            float curr_num;
            cin >> curr_num;
            result+=curr_num;
        }
        cout << result << endl;
    }
}
