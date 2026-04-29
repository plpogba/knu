#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int deadline;
    int profit;
}job;

vector<job> scheduling(vector<job> joblist);
int main(){
    int n, tmp;
    cin >> n;

    vector<job> joblist(n);
    for(int i = 0; i < n; i++){
        cin >> tmp;
        joblist[i].deadline = tmp;
    }
    for(int i = 0; i < n; i++){
        cin >> tmp;
        joblist[i].profit = tmp;
    }

    vector<job> result = scheduling(joblist);
    int sum = 0;
    for(int i = 0; i < result.size(); i++){
        sum += result[i].profit;
    }
    cout << sum << endl;
    for(int i = 0; i < result.size()-1; i++){
        cout << result[i].profit << ' ';
    }
    cout << result[result.size()-1].profit << endl;
    return 0;
}

vector<job> scheduling(vector<job> joblist){
    int n = joblist.size();
    vector<job> result;
    result.push_back(joblist[0]);
    for(int i = 1; i < n; i++){
        int size = result.size();
        int location, flag = 1;
        for(int k = 0; k < size; k++){
            if(result[k].deadline > joblist[i].deadline){
                result.emplace(result.begin()+k, joblist[i]);
                location = k;
                flag = 0;
                break;
            }
        }
        if(flag){
            result.push_back(joblist[i]);
            location = size;
        }
        for(int k = 0; k < size+1; k++){
                if(result[k].deadline < k+1){
                    result.erase(result.begin()+location);
                    break;
                }
            }
    }
    return result;
}