#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

using namespace std;
typedef long long long_t;
typedef vector<vector<int>> matrix;

vector<int> read_ints_by_space() {
    vector<int> result;
    string line;
    if (!getline(cin, line))
        return result;

    istringstream iss(line);
    int value;
    while (iss >> value) {
        result.push_back(value);
    }
    return result;
}
matrix mult(matrix A, matrix B, long_t n){
    vector<int> row;
    matrix result;
    int sum;
    for(int i = 0; i < n; i++){
        row.clear();
        for(int j = 0; j < n; j++){
            sum = 0;
            for(int k = 0; k < n; k++){
                sum =(sum + (A[i][k] * B[k][j]))%1000;
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return result;
}
matrix imatrix(long_t size){
    vector<int> row;
    matrix result;
    for(long_t i = 0; i < size; i++){
        row.clear();
        for(long_t j = 0; j < size; j++){
            if(i == j)
                row.push_back(1);
            else
                row.push_back(0);
            
        }
        result.push_back(row);
    }
    return result;
}
matrix expon(matrix m, long_t n, long_t size){
    matrix result;
    if(n == 0){
        result = imatrix(size);
        return result;
    }
    else if(n == 1)
        return m;
    else{
        if(n%2 == 0){
            matrix tmp = expon(m,n/2, size);
            return mult(tmp, tmp, size);
        }
        else{
            matrix ex = expon(m, n/2, size);
            return mult(m, mult(ex, ex, size), size);
        }
    }
}
int main(){
    long_t n, k;
    cin >> n >> k;
    matrix M;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for(long_t i = 0; i < n; i++)
        M.push_back(read_ints_by_space());
    
    matrix a =  expon(M, k, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            cout << a[i][j] << ' ';
        }
        cout << a[i][n-1] << endl;
    }
        
    return 0;
}
