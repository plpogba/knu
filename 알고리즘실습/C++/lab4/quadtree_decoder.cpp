#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
typedef vector<vector<int>> matrix;

int k = 0;
void paint(matrix& A, int start_row, int start_col, int size, char code){
    for(int i = start_row; i < start_row + size; i++){
        for(int j = start_col; j < start_col + size; j++){
            if(code == 'b')
                A[i][j] = 1;
            else
                A[i][j] = 0;
        }
    }
}
void qDecoder(matrix& A, int start_row, int start_col, int size, char* code, char bwx){
    if(size == 1 || bwx != 'x'){
        paint(A, start_row, start_col, size, bwx);
        k++;
        return;
    }
    else{
        k++;
        qDecoder(A, start_row, start_col, size/2, code, code[k]);
        qDecoder(A, start_row, start_col+size/2, size/2, code, code[k]);
        qDecoder(A, start_row + size/2, start_col, size/2, code, code[k]);
        qDecoder(A, start_row + size/2, start_col + size/2, size/2, code, code[k]);
    }
}
matrix init(int n){
    matrix result;
    vector<int> line;
    for(int j = 0; j < n; j++)
        line.push_back(0);
    for(int i = 0; i < n; i++){
        result.push_back(line);
    }
    return result;
}
int main(){
    int n;
    char code[1000];
    cin >> n;
    cin.ignore();
    fgets(code, 1000, stdin);
    code[strcspn(code, "\n")] = '\0';
    matrix A = init(n);
    qDecoder(A, 0, 0, n, code, code[k]);

    cout << n << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            cout << A[i][j] << ' ';
        }
        cout << A[i][n-1] << endl;
    }
    return 0;
}