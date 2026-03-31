#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

vector<int> read_ints_by_space();
void mergesort(int low, int high);
void merge(int low, int mid, int high);


 vector<int> v;

int main(){
    int n;
    
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    v = read_ints_by_space();
    v.insert(v.begin(), 0);
    mergesort(1,v.size()-1);
    for(int i=1; i < v.size()-1; i++)
        cout << v[i] << ' ';
    cout << v[v.size()-1] << endl;
    cout << v[0] << endl;

    return 0;
}



void merge(int low, int mid, int high){
    v[0] += 1;
    int i = low, j = mid+1,k=0;
    vector<int> u (high-low+1);
    while(i <= mid && j <= high)
        u[k++] = v[i] < v[j] ? v[i++] : v[j++];
    if(i > mid)
        while(j <= high)
            u[k++] = v[j++];
    else if(j > high)
        while(i<=mid)
            u[k++] = v[i++];
    for(int t = low; t <= high; t++)
        v[t] = u[t-low];

}
void mergesort(int low, int high){
  
    if (low < high){
        int mid = (low + high) /2;
        mergesort(low, mid);
        mergesort(mid+1, high);
        merge(low, mid, high);
    }
}

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