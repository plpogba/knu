#include <iostream>
#include <vector>

using namespace std;


vector<int> binoCoef(int n, int k){//nCk = n-1Ck-1 + n-1Ck
    vector<int> B(k+1);
    for(int i = 0; i <= n; i++){
        for(int j = k+1; j >=0; j--){
        if(j == n || j== 0)
            B[j] = 1;
        else
            B[j] = B[j] + B[j-1];
    }
   }
   return B;
}
int main(){
    int n, k;
    cin >> n >> k;
    vector<int> coef = binoCoef(n, k);
    cout << coef[k];
}