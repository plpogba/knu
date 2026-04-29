#include <iostream>
#include <vector>
#include <queue>

#define INF 0xffff
using namespace std;

typedef vector<vector<int>> matrix;
typedef struct edge_t{
    int u,v,w;
}edge_t;


typedef vector<edge_t> set_of_edges;

void printTable(int n, vector<int> table){
    if(n < 2){
        return;
    }
    cout << table[2];
    for(int i = 3; i <= n; i++)
        cout << ' ' << table[i];
    cout << '\n';
}

void printPath(vector<int> table, int n){
    if(n == 1){
        cout << 1 << '\n';
        return;
    }
    vector<int> path;
    int i;
    for(i = n; table[i] != 1; i = table[i])
        path.push_back(i);
    path.push_back(i);

    cout << 1;
    for(int j = path.size()-1; j >= 0; j--)
        cout << ' ' << path[j];
    cout << '\n';
}

vector<int> dijkstra(int n, matrix& W, set_of_edges& F){
    int vnear, min;
    vector<int> touch(n+1), length(n+1);
    F.clear();

    if(n == 1){
        printTable(n, touch);
        return touch;
    }

    for(int i = 2; i <= n; i++){
        touch[i] = 1;
        length[i] = W[1][i];
    }
    printTable(n, touch);

    for(int k = 0; k < n-1; k++){
        min = INF;
        vnear = -1;
        for(int i = 2; i <= n; i++)
            if(0 <= length[i] && length[i] < min){
                min = length[i];
                vnear = i;
            }
        if(vnear == -1) break;

        edge_t e;
        e.u = touch[vnear];
        e.v = vnear;
        e.w = W[touch[vnear]][vnear];  
        F.push_back(e);

        for(int i = 2; i <= n; i++)
            if(length[i] > length[vnear] + W[vnear][i]){
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        length[vnear] = -1;
        printTable(n, touch);
    }
    return touch;
}

int main(){
    int n, k, numOfTestCase;
    int u, v, w;
    cin >> n >> k;

    matrix W(n+1, vector<int>(n+1, INF));
    set_of_edges E, F;
    vector<int> testcase;

    for(int i = 0; i < k; i++){
        cin >> u >> v >> w;
        W[u][v] = w;       
        edge_t a;
        a.u = u;
        a.v = v;
        a.w = w;
        E.push_back(a);
    }

    cin >> numOfTestCase;
    for(int i = 0; i < numOfTestCase; i++){
        int tmp;
        cin >> tmp;
        testcase.push_back(tmp);
    }

    vector<int> touch = dijkstra(n, W, F);

    for(edge_t i : F)
        cout << i.u << ' ' << i.v << ' ' << i.w << '\n';

    for(int i : testcase)
        printPath(touch, i);

    return 0;
}