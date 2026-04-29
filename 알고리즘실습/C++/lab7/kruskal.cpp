#include <iostream>
#include <vector>
#include <queue>

#define INF 0xffff
using namespace std;

typedef vector<vector<int>> matrix;
typedef struct edge_t{
    int u,v,w;
}edge_t;

struct edge_compare{
    bool operator()(edge_t e1, edge_t e2){
        if(e1.w >  e2.w)
        return true;
        else return false;
    }
};

typedef vector<edge_t> set_of_edges;
typedef priority_queue<edge_t,vector<edge_t>,edge_compare> PriorityQueue;

vector<int> dset;
void dset_init(int n){
    dset.resize(n+1);
    for(int i = 1; i <= n; i++)
        dset[i] = i;
}
int dset_find(int i){
    while(dset[i] != i)
        i = dset[i];
    return i;
}

void dset_merge(int p, int q){
    dset[p] = q;
}
void kruskal(matrix graph, int n, set_of_edges& E, set_of_edges& F){
    int p,q;
    edge_t e;
    vector<int> set(n+1);
    PriorityQueue pq;
    for(edge_t i : E)
        pq.push(i);
    F.clear();
    dset_init(n);
    while(F.size() < n-1){
        e = pq.top(); pq.pop();
        p = dset_find(e.u);
        q = dset_find(e.v);
        if(p != q){
            dset_merge(p,q);
            F.push_back(e);
        }
    }


}

int main(){
    int n, k;
    int u, v, w;
    cin >> n >> k;


    matrix W(n+1, vector<int>(n+1, INF));
    set_of_edges E, F;

    for(int i = 0; i < k; i++){
        cin >> u >> v >> w;
        W[u][v] = w;
        W[v][u] = w;
        edge_t a;
        a.u = u;
        a.v = v;
        a.w = w;

        E.push_back(a);
    }  

    kruskal(W, n, E, F);

    for(edge_t i : F){
        cout << i.u << ' ' << i.v << ' '<< i.w << endl;
    }

    return 0;
}