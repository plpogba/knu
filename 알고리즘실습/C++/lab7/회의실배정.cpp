#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting {
    int start;
    int end;
};

bool compare(const Meeting& a, const Meeting& b) {
    if (a.end == b.end) {
        return a.start < b.start;
    }
    return a.end < b.end;
}

int main() {
    
    int N;
    if (!(cin >> N)) return 0;

    vector<Meeting> schedule(N);
    vector<Meeting> assign;
    for (int i = 0; i < N; i++) {
        cin >> schedule[i].start >> schedule[i].end;
    }

   
    sort(schedule.begin(), schedule.end(), compare);

    int count = 0;
    int last_end_time = 0;

   
    for (int i = 0; i < N; i++) {
        
        if (schedule[i].start >= last_end_time) {
            count++;
            assign.push_back(schedule[i]);
            last_end_time = schedule[i].end;
        }
    }

    cout << count << "\n";
    for(Meeting i : assign)
        cout << i.start << ' ' << i.end << endl;
    return 0;
}