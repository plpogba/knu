#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

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

int cnt;
int binsearch2(int low, int high, vector<int> s, int x);

int main(){
    int n,m,tmp, find;
    cin >> n >> m;

    vector<int> arr;
    for (int i = 0; i < n; i++){
        cin >> tmp;
        arr.push_back(tmp);
    }

    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<int> search_values = read_ints_by_space();

    sort(arr.begin(), arr.end());

    for (int i = 0; i < (int)search_values.size(); i++){
        cnt = 0;
        int k = binsearch2(0, arr.size()-1, arr, search_values[i]) + 1;
        
        
        cout << cnt << ' ' << k << endl;
       
    }
}

int binsearch2(int low, int high, vector<int> s, int x){
    int mid;
    cnt += 1;
    if (low > high)
        return -1;
    else{
        mid = (high + low)/2;
        if (s[mid] == x){
            return mid;
        }
        else if(x < s[mid]){
            return binsearch2(low,mid-1,s,x);
        }
        else{
            return binsearch2(mid+1,high,s,x);
        }
    }
}