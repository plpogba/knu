#include <iostream>
#include <vector>

using namespace std;
typedef vector<vector<int>> matrix;

char bwx(matrix A, int start_row, int start_col, int size){
    int flag0 = 0, flag1 =0;
    for(int i = start_row; i < start_row + size; i++){
        for(int j = start_col; j < start_col + size; j++){
            if(A[i][j] ==1)
                flag1 += 1;//0
            else
                flag0 += 1;//1
        }
    }
    if(flag0 == 0)
            return 'b';
    else if(flag1 == 0)
        return 'w';
    else return 'x';
}

void qEncoder(matrix A, int start_row, int start_col, int size, vector<char>& encoding){
    char c;
    c = bwx(A, start_row, start_col, size);
    if(size == 1){
        encoding.push_back(c);
        return;
    }
    else if(c != 'x'){
        encoding.push_back(c);
        return;
    }
    else{
        encoding.push_back(c);
        qEncoder(A, start_row, start_col, size/2, encoding);
        qEncoder(A, start_row, start_col + size/2, size/2, encoding);
        qEncoder(A, start_row + size/2, start_col, size/2, encoding);
        qEncoder(A, start_row + size/2, start_col + size/2, size/2, encoding);
    }
}
int main(){
    int n, tmp;
    cin >> n;
    vector<int> line;
    matrix field;
    vector<char> compressed;
    for(int i = 0; i < n; i++){
        line.clear();
        for(int j = 0; j < n; j++){
            cin >> tmp;
            line.push_back(tmp);
        }
        field.push_back(line);
    }
    qEncoder(field, 0, 0, n, compressed);
    for(char i: compressed)
        cout << i;
}