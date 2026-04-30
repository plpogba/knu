#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long long_t;

int main(){
    long_t n;
    cin >> n;
  
    vector<long_t> fib;
    fib.push_back(0);
    fib.push_back(1);
    int i;
    for(i = 1; ;i++){
        fib.push_back(fib[i] + fib[i-1]);
        if(fib[i+1] > n)
            break;
    }
    long_t sum = n;
    vector<long_t> result;
    for(int k = i; sum > 0; k--){
        if(fib[k] <= sum){
            
            result.push_back(fib[k]);
            sum -= fib[k];
        }
    }

    for(int k = result.size()-1; k >= 0; k--)
        cout << result[k] << endl;

}