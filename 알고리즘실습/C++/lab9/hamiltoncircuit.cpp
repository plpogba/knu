#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> matrix;

int cnt = 0;
bool promising(const matrix &graph, vector<int> &vindex, int i, int n);
void hamilton(const matrix &graph, vector<int> &vindex, int i, int n);
int main(){
    int n, m;
    int u,v;
    cin >> n >> m;

    matrix graph(n+1, vector<int>(n+1,0));
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    vector<int> vindex(n+1);
    vindex[0] = 1;
    hamilton(graph, vindex, 0, n);
    cout << cnt;
}

void hamilton(const matrix &graph, vector<int> &vindex, int i, int n){
    int j;
    if(promising(graph, vindex, i, n)){
        if(i == n - 1)
            cnt++;
        else{
            for(j = 2; j <= n; j++){
                vindex[i+1] = j;
                hamilton(graph, vindex, i+1, n);
            }
        }
    }
}

bool promising(const matrix &graph, vector<int> &vindex, int i, int n){
    int j;
    bool flag;

    if(i == n-1 && !graph[vindex[n-1]][vindex[0]])
        flag = false;
    else if(i > 0 && !graph[vindex[i-1]][vindex[i]])
        flag = false;
    else{
        flag = true;
        j = 1;
        while(j < i && flag){
            if(vindex[i] == vindex[j])
                flag = false;
            j++;
        }
    }
    return flag;
}