#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<vector<int>> matrix;

void printM(matrix A){
    int size = A.size();
    for(int i = 0; i < size; i++){    
        cout << A[i][0];
        for(int j = 1; j < A[0].size(); j++){
            cout << ' ' << A[i][j];
        }
        cout << endl;
    }
    cout << 0 << endl;
}

int LCS(matrix& A, string s1, string s2, int i, int j, matrix& path){
    if(i == 0 || j == 0)
        return 0;
    if(A[i][j] != 0)
        return A[i][j];
    
    else{
        if(s1[i-1] == s2[j-1]){
            A[i][j] = LCS(A, s1, s2, i-1, j-1, path) + 1;
            path[i][j] = 1;
        }
        else{
            vector<int> line;
            int up =LCS(A, s1, s2, i-1, j, path);
            int left = LCS(A, s1, s2, i, j-1, path);
            A[i][j] = up >= left ? up : left;
            if(up >= left){
                path[i][j] = 2;
            }
            else {
                path[i][j] = 3;
            }
        }
        return A[i][j];
    }
}

void printS(matrix path, string s, int i, int j){
    if(i == 0 || j == 0)
        return;
    else{
        if(path[i][j] == 1){
            printS(path, s, i-1, j-1);
            cout << s[i-1];
        }
        else if(path[i][j] == 2){
            printS(path, s, i-1, j);
        }
        else
            printS(path, s, i, j-1);
    }
}
int main(){
    string x, y;
    cin >> x >> y;
    int size1 = x.size();
    int size2 = y.size();
    matrix A(size1+1, vector<int>(size2+1, 0));
    matrix path(size1+1, vector<int>(size2+1, 0));
    int result = LCS(A, x, y, size1, size2, path);
    cout << result << endl;
    printS(path, x, size1, size2);

}