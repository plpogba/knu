#include <iostream>
#include <vector>

using namespace std;

void queens(int i, int n);
bool feasible(int col);
int compare(vector<int>& A, vector<int>& B);
int cnt=0;
vector<vector<int>> positions;
vector<int> cols;

int main(){
    int n;
    cin >> n;

    cols.resize(n,-1);
    queens(0, n);
    cout << cnt << endl;   
    int col, maxIndex=0;
    vector<int> max = positions[0];
    for(int i = 1; i < cnt; i++){
        if(compare(max, positions[i]) == 1)
            max = positions[i];
    }
    for(int i = 0; i < n; i++){
        cout << max[i]+1;
    }
    return 0;
}
void queens(int i, int n){
    if (i == n) {
        cnt++;
        positions.push_back(cols);
        return;
    }

    
    for (int j = 0; j < n; j++) {
        cols[i] = j;
        
        if (feasible(i)) {
            queens(i + 1, n); 
        }
    }
}
bool feasible(int row){
    for(int i = 0; i < row; i++){
        if((cols[row] == cols[i]) || (abs(cols[i] - cols[row]) == row - i))
            return false;
    }
    return true;
}

int compare(vector<int>& A, vector<int>& B) {
    int len = A.size();
    for (int i = 0; i < len; i++) {
        string sA = to_string(A[i] + 1);
        string sB = to_string(B[i] + 1);

        if (sA + sB > sB + sA) return 0; // A가 앞에 올 때 더 크면 A 승리(0 반환)
        if (sB + sA > sA + sB) return 1; // B가 앞에 올 때 더 크면 B 승리(1 반환)
    }
    return -1; // 완전히 같은 경우
}