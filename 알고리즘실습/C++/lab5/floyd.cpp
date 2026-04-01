#include <iostream>
#include <vector>
#define INF 999
using namespace std;

typedef vector<vector<int>> matrix;

void printTable(int n, matrix A){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            cout << A[i][j] << ' ';
        }
        cout << A[i][n-1] << endl;
    }
}

void floyd(int n, matrix& W, matrix& D, matrix &P){
    for(int i =-1; i < n; i++){
        if(i == -1){
            for(int j = 0; j < n; j++)
                for(int k = 0; k < n; k++){
                    if(j == k)
                        D[j][k] = 0;
                    else
                        D[j][k] = W[j][k];
                    P[j][k] = 0;
                }
        }
        else{
            for(int j = 0; j < n; j++){
                for(int k = 0; k < n; k++){
                    if(D[j][k] > D[j][i] + D[i][k])
                        P[j][k] = i+1;
                    D[j][k] = min(D[j][k], D[j][i] + D[i][k]);
                }
            }
        }
    }
}

void pathMake(matrix P, int u, int v, vector<int>& p){
    int k = P[u][v];
    if(k!= 0){
        pathMake(P,u,k-1,p);
        p.push_back(k);
        pathMake(P,k-1,v,p);
    }
}

int main(){
    int n, m, k, start, dest;
    int u,v,w;

    cin >> n >> m;
    matrix W,D,P;
    vector<int> line;
    for(int i = 0; i < n; i++){
        line.push_back(INF);
    }
    for(int i = 0; i < n; i++){
        W.push_back(line);
        D.push_back(line);
        P.push_back(line);
    }
    for(int i = 0 ; i < m; i++){
        cin >> u >> v >> w;
        W[u-1][v-1] = w;
    }
    cin >> k;
    matrix path;
    for(int i = 0; i < k; i++){
        line.clear();
        cin >> start >> dest;
        line.push_back(start); line.push_back(dest);
        path.push_back(line);
    }
    floyd(n, W, D, P);
    
    printTable(n, D);
    printTable(n, P);

    for(vector<int> i : path){
        vector<int> p;
        int u = i[0];
        int v = i[1];
        if(D[u-1][v-1] >= INF)
            cout << "NONE" << endl;
        else{
            cout << u << ' ';
            pathMake(P,u-1,v-1,p);
            if(!p.empty()){
                for(int j = 0; j < p.size(); j++)
                cout << p[j] << ' ';
            }
            cout << v << endl;
        }
       
    }

}