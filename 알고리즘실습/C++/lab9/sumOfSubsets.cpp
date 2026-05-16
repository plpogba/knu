#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> field;
void subsets(const vector<int> &sets, int index, int cur, const int w, const int n);
int cnt = 0;
int main(){
    int n, w, tmp;
    vector<int> sets;
    
    cin >> n >> w;
    
    for(int i = 0; i < n; i++){
        cin >> tmp;
        sets.push_back(tmp);
    }
    //n = 4; w = 13;
    //sets.push_back(3); sets.push_back(4); sets.push_back(5); sets.push_back(6);
    for(int i = 0; i < n; i++)
        subsets(sets, i, 0, w, n);
    cout << cnt << endl;
    for(int i = 0; i < cnt; i++){
        for(int j = 0; j < field[i].size()-1; j++){
            cout << field[i][j] << ' ';
        }
        cout << field[i][field[i].size()-1] << endl;
    }

}

void subsets(const vector<int> &sets, int index, int curVal, const int w, const int n){
    static vector<int> result;
    if (index >= n)
        return;
    if(curVal + sets[index] == w){
        cnt++;
        result.push_back(sets[index]);
        field.push_back(result);
        result.pop_back();
        return;
    }
    else if(curVal + sets[index] > w){
        return;
    }
    else{
        for(int i = index+1; i < n; i++){
            result.push_back(sets[index]);
            subsets(sets, i, curVal+sets[index], w, n);
            result.pop_back();
        }
    }
    
}