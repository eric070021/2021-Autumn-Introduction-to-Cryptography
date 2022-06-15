#include <iostream>
#include <math.h>   

using namespace std;

int main(){
    long long n = 238589771;
    long long seed = 7477;
    int count_0 = 0, count_1 = 0, count_00 = 0, count_01 = 0, count_10 = 0, count_11 = 0;
    for(int i=0; i<1000000; i++){
        seed = (seed*seed)%n;
        if(seed % 2){
            count_1 += 1;
        }
        else{
            count_0 += 1;
        }
    }
    cout<< count_1 << " " << count_0 << '\n';

    long long one, two=7477;
    for(int i=0; i<500000; i++){
        one = (two*two)%n;
        two = (one*one)%n;

        if(one % 2){
           if(two % 2) count_11 += 1;
            else count_10 += 1;
        }
        else{
            if(two % 2) count_01 += 1;
            else count_00 += 1;
        }
    }

    cout<< count_00 << " " << count_01 << " " <<  count_10 << " " << count_11;
}