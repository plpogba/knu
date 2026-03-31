#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

int cnt = 0;
vector<int> arr;

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

void swap(int i, int j, vector<int>& arr){
    cnt++;
    int tmp;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
void partition(int low, int high, int& pivot){
    int pivotitem = arr[low];
    int j = low;
    for(int i = low+1; i<=high; i++){
        if (arr[i] < pivotitem){
            swap(i,++j,arr);
        }
    }
    pivot = j;
    swap(low,j,arr);
}

void quicksort(int low, int high){
    int pivot;

    if(low < high){
        partition(low, high, pivot);
        quicksort(low, pivot-1);
        quicksort(pivot+1, high);
    }
}


int main(){
    int n;
    cin >> n;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    arr = read_ints_by_space();

    quicksort(0, arr.size()-1);
    for (int i=0; i<arr.size()-1; i++)
        cout << arr[i] << ' ';
    cout << arr[arr.size()-1] << endl;
    cout << cnt;

    return 0;
}