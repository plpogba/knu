#include <iostream>
#include <vector>


using namespace std;
typedef vector<vector<int>> matrix;
typedef long long long_t;


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
matrix mult(matrix A, matrix B, long_t n, int m){
    vector<int> row;
    matrix result;
    int sum;
    for(int i = 0; i < n; i++){
        row.clear();
        for(int j = 0; j < m; j++){
            sum = 0;
            for(int k = 0; k < n; k++){
                sum =(sum + (A[i][k] * B[k][j]))%10007;
            }
            row.push_back(sum);
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
            return mult(tmp, tmp, size, size);
        }
        else{
            matrix ex = expon(m, n/2, size);
            return mult(m, mult(ex, ex, size, size), size, size);
        }
    }
}
matrix fib(long_t n){
    matrix a, b;
    vector<int> line;
    line.push_back(1);
    line.push_back(1);
    a.push_back(line);
    line.clear();
    line.push_back(1);
    line.push_back(0);
    a.push_back(line);
    line.clear();
    line.push_back(1);
    b.push_back(line);
    line.clear();
    line.push_back(0);
    b.push_back(line);
    a = expon(a, n, 2);
    a = mult(a, b, 2, 1);
    return a;
}
int main(){
    int n;
    cin >> n;
    
    long_t num = fib(n)[0][0];

    cout << num << endl;

}