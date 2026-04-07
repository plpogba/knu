#include <iostream>
#include <vector>
#define INF 9999

using namespace std;
typedef vector<vector<int>> matrix;

int chainM(matrix& A, vector<int> d, int i, int j, matrix& path);
void printM(matrix A){
    int size = A.size();
    for(int i = 0; i < size; i++){
        if (A[i][i] != -1)
            cout << A[i][i];
        for(int j = i+1; j < size; j++){
            if(A[i][j] != -1){
                cout << ' ' << A[i][j];
            }       
        }
        cout << endl;
    }
}

void order(int i,int j, matrix& P,string& s){
    if(i==j)
        s+=string("(A")+to_string(i+1) + string(")");
    else{
        int k=P[i][j]-1;
        s+=string("(");
        order(i,k,P,s);
        order(k+1,j,P,s);
        s+=string(")");
    }
}
int main(){
    int n, m;
    vector<int> d;
    string s = "";
    cin >> n;
    for(int i = 0; i < n+1; i++){
        cin >> m;
        d.push_back(m);
    }
    matrix A(n, (vector<int>(n,-1)));
    matrix path(n, (vector<int>(n,-1)));
    for(int i = 0; i < n; i++){
        path[i][i] = 0;
    }
    int result = chainM(A,d,0,n-1, path);
    printM(A);
    printM(path);
    cout <<  result << endl;
    order(0, n-1, path, s);
    cout << s;
    return 0;
}

int chainM(matrix& A, vector<int> d, int i, int j, matrix& path){
    if(i == j){
        A[i][j] = 0;
        return 0;
    }
    else if(A[i][j] != -1)
        return A[i][j];
    else{
        int min = INF;
        int tmp, tmp2;
        for(int k = i; k < j; k++){
            tmp = chainM(A,d,i,k, path) + chainM(A,d, k+1, j, path) + d[i] * d[k+1] * d[j+1];
            if(tmp < min){
                min = tmp;
                path[i][j] = k+1;
            }
        }
        A[i][j] = min;
        return min;
    }
}