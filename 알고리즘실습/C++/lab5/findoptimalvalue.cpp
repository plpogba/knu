#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> line;
typedef vector<line> matrix;


matrix optimalValue(int n, matrix triangle){
    matrix result = triangle;

    for(int i = n-1; i >= 1; i--){
        for(int j = 0; j < i; j++){
            result[i-1][j] = max(result[i][j], result[i][j+1]) + result[i-1][j];
        }
    }
    return result;
}

int main(){
    int c, n;
    int tmp;
    cin >> c;
    
    for(int i = 0; i < c; i++){
        cin >> n;
        matrix triangle(n,(vector<int>(n,-1)));
        for(int j = 0; j < n; j++){
            line a;
            for(int k = 0; k <= j; k++){
                cin >> triangle[j][k];
            }
        }
        matrix optimal = optimalValue(n, triangle);
        cout << optimal[0][0] << endl;
    }

}