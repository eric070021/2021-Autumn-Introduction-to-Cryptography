#include <iostream>
#include <math.h>

using namespace std;

# define pi 3.14159265358979323846

int main(){
    double a[8] = {0,1,0,3,0,1,0,3};
    double sum;
    for(double j=0; j<4;j++){
        sum = 0;
        for(int i=0; i<8 ;i++){
            sum += a[i]*sin(2*pi*j/8*i);
        }
    cout<<j<<": "<<sum<<'\n';
    }
   
}