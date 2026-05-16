    #include <iostream>
    #include <vector>

    using namespace std;

    typedef vector<vector<int>> matrix;
    int cnt = 0;

    void mcoloring(const matrix &graph, vector<int> &vcolor, int n, int m, int i);
    bool promising(const matrix &graph, vector<int> &vcolor, int i);

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
        vector<int> vcolor(n+1,-1);
        for(int i = 1; i <= 4; i++){
            cnt = 0;
            mcoloring(graph, vcolor, n, i, 0);
            if(cnt != 0){
                cout << i << endl;
                cout << cnt;
                break;

            }
        }
    }

    void mcoloring(const matrix &graph, vector<int> &vcolor, int n, int m, int i){
        int color;
        if(promising(graph, vcolor, i)){
            if(i == n){
                cnt++;
                return;
            }
            for(color = 1; color <= m; color++){
                vcolor[i+1] = color;                      // ← i+1 설정
                mcoloring(graph, vcolor, n, m, i+1);
            }
    }
}

    bool promising(const matrix &graph, vector<int> &vcolor, int i){
        int j = 1; 
        bool flag = true;
        while(j<i && flag){
            if(graph[i][j] && vcolor[i] == vcolor[j])
                flag = false;
            j++;
        }
        return flag;
    }