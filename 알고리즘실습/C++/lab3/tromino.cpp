#include <iostream>
#include <vector>


using namespace std;
typedef vector<vector<int>> matrix;

int cnt = 1;
matrix A;

int whichside(int size, int hole_row, int hole_col, int from_row, int from_col){
    if(from_row <= hole_row && hole_row < from_row + size/2){//1,3사분면
        if(from_col <= hole_col && hole_col < from_col + size/2)//1사분면   
            return 1;
        else 
            return 2;
    }
    else{
         if(from_col <= hole_col && hole_col < from_col + size/2)
            return 3;
        else 
            return 4;
    }
       
}

void tromino(int size, int hole_row, int hole_col, int from_row, int from_col){
    int middle_row = from_row + size/2;
    int middle_col = from_col + size/2;
    if (size == 2){
        vector<int> tmp;
        for(int i = from_row; i < from_row + size; i++){
            for(int j = from_col; j < from_col + size; j++){
                if(i==hole_row && j == hole_col)
                    continue;
                else
                    A[i][j] = cnt;
            }
        }
        cnt++;
        return;
    }

    int hole_pos = whichside(size, hole_row, hole_col, from_row, from_col);
    
    if(hole_pos == 1){
        A[middle_row][middle_col] = cnt;
        A[middle_row][middle_col-1] = cnt;
        A[middle_row-1][middle_col] = cnt;
    }
    else if(hole_pos == 2){
        A[middle_row][middle_col] = cnt;
        A[middle_row-1][middle_col-1] = cnt;
        A[middle_row][middle_col-1] = cnt;
        
    }
    else if(hole_pos == 3){
        A[middle_row][middle_col] = cnt;
        A[middle_row-1][middle_col-1] = cnt;
        A[middle_row-1][middle_col] = cnt;
    }
    else{
        A[middle_row][middle_col-1] = cnt;
        A[middle_row-1][middle_col-1] = cnt;
        A[middle_row-1][middle_col] = cnt;
    }
    cnt++;
    if(hole_pos == 1){
        tromino(size/2, hole_row, hole_col, from_row, from_col);//1사분면
        tromino(size/2, middle_row-1, middle_col, from_row, middle_col);//2사분면
        tromino(size/2, middle_row, middle_col-1, middle_row, from_col);//3사분면
        tromino(size/2, middle_row, middle_col, middle_row, middle_col);//4사분면

    }
    else if(hole_pos == 2){
        tromino(size/2, middle_row-1, middle_col-1, from_row, from_col);//1사분면
        tromino(size/2, hole_row, hole_col, from_row, middle_col);//2사분면
        tromino(size/2, middle_row, middle_col-1, middle_row, from_col);//3사분면
        tromino(size/2, middle_row, middle_col, middle_row, middle_col);//4사분면

    }
    else if(hole_pos == 3){
        tromino(size/2, middle_row-1, middle_col-1, from_row, from_col);//1사분면
        tromino(size/2, middle_row-1, middle_col, from_row, middle_col);//2사분면
        tromino(size/2, hole_row, hole_col, middle_row, from_col);//3사분면
        tromino(size/2, middle_row, middle_col, middle_row, middle_col);//4사분면

    }
    else if(hole_pos == 4){
        tromino(size/2, middle_row-1, middle_col-1, from_row, from_col);//1사분면
        tromino(size/2, middle_row-1, middle_col, from_row, middle_col);//2사분면
        tromino(size/2, middle_row, middle_col-1, middle_row, from_col);//3사분면
        tromino(size/2, hole_row, hole_col, middle_row, middle_col);//4사분면

    }
   
}
int main(){
    int size, row, col;

    cin >> size >> row >> col;
   
    vector<int> tmp;
    for(int i = 0; i < size; i++){
        tmp.push_back(0);
    }
    for(int i = 0; i < size; i++)
        A.push_back(tmp);
    
    
    tromino(size, row, col, 0, 0);
    for(int i = 0; i < size; i++){
        for (int j = 0; j < size-1; j++){
            cout << A[i][j] << ' ';
        }
        cout << A[i][size-1] << endl;
    }
    
}
