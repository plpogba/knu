#include <iostream>
#include <vector>
#define INF 0xffff
using namespace std;

typedef vector<vector<int>> matrix;


void prim(matrix graph, matrix& setofedges, int n){
    int vnear, min;
    vector<int> line;
    vector<int> nearest(n+1), distance(n+1);
    for(int i = 2; i <= n; i++){
        nearest[i] = 1;
        distance[i]= graph[1][i];
    }
    for(int j = 2; j < n; j++){
            cout << nearest[j] << ' ';
    }
    cout << nearest[n] << endl;
    for(int i = 0; i < n-1; i++){
        line.clear();
        min = INF;
        for(int j = 2; j <= n; j++){
            if(0 <= distance[j] && distance[j] < min){
                min = distance[j];
                vnear = j;
            }
        }
        line.push_back(vnear);
        line.push_back(nearest[vnear]);
        line.push_back(min);
        setofedges.push_back(line);
        distance[vnear] = -1;

        for(int j = 2; j <= n; j++){
            if(distance[j] > graph[vnear][j]){
                distance[j] = graph[vnear][j];
                nearest[j] = vnear;
            }
        }
        for(int j = 2; j < n; j++){
            cout << nearest[j] << ' ';
        }
        cout << nearest[n] << endl;
    }
    
}
int main(){
    int n, k;
    int u, v, w;
    cin >> n >> k;

    matrix setofedges;
    matrix W(n+1, vector<int>(n+1, INF));

    for(int i = 0; i < k; i++){
        cin >> u >> v >> w;
        W[u][v] = w;
        W[v][u] = w;
    }

    prim(W, setofedges, n);

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < 2; j++){
            cout << setofedges[i][j] << ' ';
        }
        cout << setofedges[i][2] << endl;
    }

    return 0;
}