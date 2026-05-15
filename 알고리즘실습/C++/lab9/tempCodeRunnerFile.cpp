#include <iostream>
#include <vector>

using namespace std;

void queens(int i, int n);
bool feasible(int col);

int cnt=0;
vector<vector<int>> positions;
vector<int> cols;
int main(){
    int n;
    cin >> n;
    cols.resize(n,-1);
    queens(0, n);
    cout << cnt << endl;   
        for(int k : positions[cnt-1])
            cout << k+1;
        cout << endl;
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
