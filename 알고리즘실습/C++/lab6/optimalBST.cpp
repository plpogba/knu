#include <iostream>
#include <vector>
#define INF 1000000000
using namespace std;
typedef vector<vector<int>> matrix;


int optimalBST(matrix& A, matrix& path, vector<int> freq, int i, int j){
    if(i > j)
        return 0;
    if(A[i][j] != 0)
        return A[i][j];
    else{
        int min = INF;
        int tmp;
        int p=0;
        for(int t = i; t <=j; t++){
            p += freq[t];
        }
        for(int k = i; k <= j; k++){
            tmp = optimalBST(A, path, freq, i, k-1) + optimalBST(A, path, freq, k+1, j) + p;
            if(tmp < min){
                min = tmp;
                path[i][j] = k;
            }
        }
        A[i][j] = min;
        return min;
    }
}
void printM(matrix A){
    int size = A.size();
    for(int i = 1; i < size; i++){    
        cout << A[i][i-1];
        for(int j = i; j < size; j++){
            cout << ' ' << A[i][j];
        }
        cout << endl;
    }
    cout << 0 << endl;
}

void inorder(matrix A, vector<int> keys, int i, int j){
    if(i > j)
        return;
    int k = A[i][j];
    inorder(A,keys,i,k-1);
    if(k == 1)
        cout << keys[k-1];
    else
        cout << ' ' << keys[k-1];
    inorder(A,keys,k+1,j);
}

void preorder(matrix A, vector<int> keys, int i, int j, int n){
    if(i > j)
        return;
    int k = A[i][j];
    if(i == 1 && j == n)
        cout << keys[k-1];
    else
        cout << ' ' << keys[k-1];
    preorder(A, keys, i, k-1, n);
    preorder(A, keys, k+1, j, n);
}
int main(){
    int n,m;
    cin >> n;
    
    vector<int> keys, freq;
    for(int i = 0; i < n; i++){
        cin >> m;
        keys.push_back(m);
    }
    freq.push_back(0);
    for(int i = 0; i < n; i++){
        cin >> m;
        freq.push_back(m);
    }
    matrix A(n+1, vector<int>(n+1, 0));
    matrix path(n+1, vector<int>(n+1, 0));
    int result = optimalBST(A,path,freq,1,n);
    printM(A);
    printM(path);
    cout << result << endl;
    preorder(path, keys, 1, n, n);
    cout << endl;
    inorder(path, keys, 1, n);
}
