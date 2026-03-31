#include <iostream>
#include <vector>


using namespace std;
typedef vector<vector<int>> matrix;

int cnt = 0, k;

matrix mult(matrix A, matrix B, int n){
    vector<int> row;
    matrix result;
    int sum;
    for(int i = 0; i < n; i++){
        row.clear();
        for(int j = 0; j < n; j++){
            sum = 0;
            for(int k = 0; k < n; k++){
                sum =(sum + (A[i][k] * B[k][j]));
            }
            row.push_back(sum);
        }
        result.push_back(row);
    }
    return result;
}



matrix madd(matrix A, matrix B , int size){
    matrix result;
    for(int i = 0; i < size; i++){
        vector<int> tmp;
        for(int j = 0; j < size; j++){
            tmp.push_back(A[i][j] + B[i][j]);
        }
        result.push_back(tmp);
    }
    return result;
}

matrix msub(matrix A, matrix B, int size){
     matrix result;
    for(int i = 0; i < size; i++){
        vector<int> tmp;
        for(int j = 0; j < size; j++){
            tmp.push_back(A[i][j] - B[i][j]);
        }
        result.push_back(tmp);
    }
    return result;
}


void printMatrix(matrix m, int size){
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size-1; j++){
            cout << m[i][j] << ' ';
        }
        cout << m[i][size-1] << endl;
    }
}

matrix complement(int size, matrix A){
    k = 1;
    int i;

    while(k < size){
        k *= 2;
    }
    if(k == size)
        return A;
    for(i = 0; i < size; i++){
        for(int j = 0; j < k-size; j++){
            A[i].push_back(0);
        }
    }
    vector<int> tmp;
    for(int a = 0; a < k; a++)
        tmp.push_back(0);
    for(;i<k;i++){
        A.push_back(tmp);
    }
    return A;
}
matrix resize(matrix A, int start_row, int start_col, int size){
    matrix result;
    for(int i = start_row; i < start_row+size; i++){
        vector<int> line;
        for(int j = start_col; j < start_col+size; j++){
            line.push_back(A[i][j]);
        }
        result.push_back(line);
    }
    return result;
}
vector<matrix> partition(matrix A, int size){
    vector<matrix> result;
    result.push_back(resize(A, 0, 0, size/2));
    result.push_back(resize(A, 0, size/2, size/2));
    result.push_back(resize(A, size/2, 0, size/2));
    result.push_back(resize(A, size/2, size/2, size /2));

    return result;
}

matrix combine(matrix A, matrix B, matrix C, matrix D, int size){
    matrix result;
    vector<int> line;
    for(int i = 0; i < size; i++){
        line.clear();
        for(int j =0; j < size; j++){
            line.push_back(A[i][j]);
        }
        for(int j =0; j < size; j++){
            line.push_back(B[i][j]);
        }
        result.push_back(line);
    }
     for(int i = 0; i < size; i++){
        line.clear();
        for(int j =0; j < size; j++){
            line.push_back(C[i][j]);
        }
        for(int j =0; j < size; j++){
            line.push_back(D[i][j]);
        }
        result.push_back(line);
    }
    return result;
}
matrix strassen(matrix A, matrix B, int size, int threshold){
    cnt += 1;
    if(size <= threshold){
        return mult(A,B,size);
    }
    else{
        vector<matrix> partitionA = partition(A, size);
        vector<matrix> partitionB = partition(B, size);
        matrix result;

        matrix m1 = strassen(madd(partitionA[0], partitionA[3], size/2), madd(partitionB[0], partitionB[3], size/2), size/2, threshold);
        matrix m2 = strassen(madd(partitionA[2], partitionA[3], size/2), partitionB[0], size/2, threshold);
        matrix m3 = strassen(partitionA[0], msub(partitionB[1], partitionB[3], size/2), size/2, threshold);
        matrix m4 = strassen(partitionA[3], msub(partitionB[2], partitionB[0], size/2), size/2, threshold);
        matrix m5 = strassen(madd(partitionA[0], partitionA[1], size/2), partitionB[3], size/2, threshold);
        matrix m6 = strassen(msub(partitionA[2], partitionA[0], size/2), madd(partitionB[0], partitionB[1], size/2), size/2, threshold);
        matrix m7 = strassen(msub(partitionA[1], partitionA[3], size/2), madd(partitionB[2], partitionB[3], size/2), size/2, threshold);

        matrix a = madd(msub(madd(m1, m4, size/2), m5, size/2), m7, size/2);
        matrix b = madd(m3, m5, size/2);
        matrix c = madd(m2, m4, size/2);
        matrix d = madd(msub(madd(m1, m3, size/2), m2, size/2), m6, size/2);

        result = combine(a,b,c,d, size/2);

        return result;
    }

}


int main(){
    int n,m;
    int a,b;
    cin >> n >> m;
    matrix A,B,C;
    for(int i = 0; i < n; i++){
        vector<int> line;
        for(int j = 0; j < n; j++){
            cin >> a;
            line.push_back(a);
        }
        A.push_back(line);
    }
    for(int i = 0; i < n; i++){
        vector<int> line;
        for(int j = 0; j < n; j++){
            cin >> a;
            line.push_back(a);
        }
        B.push_back(line);
    }

    matrix compA = complement(n, A);
    matrix compB = complement(n, B);

    C = strassen(compA, compB, k, m);
    cout << cnt << endl;
     printMatrix(C, n);
    
    
    
    return 0;
  
}