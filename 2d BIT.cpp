#include <bits/stdc++.h>
using namespace std;
#define m 3001
#define n 3001
int M, N, R, C, X, R1, C1, R2, C2, q;
int LSB(int x){
    return x & (-x);
}
int grid[m][n];
int bit[m][n];
int query(int x, int y){
    int sum = 0;
    for (int xi = x; xi > 0; xi -= LSB(xi)){
        for (int yi = y; yi > 0; yi -= LSB(yi)){
            sum += bit[xi][yi];
        }
    }
    return sum;
}
int qa(int x1, int y1, int x2, int y2){
    return (query(x2, y2) - query(x1-1, y2) - query(x2, y1-1) + query(x1 - 1, y1 - 1));
}
void update(int x, int y, int value){
    for (int xi = x; xi < m; xi += LSB(xi)){
        for (int yi = y; yi < n; yi += LSB(yi)){
            bit[xi][yi] += value;
        }
    }
}
void build(){
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j){
            update(i + 1, j+1, grid[i][j]);
        }
    }
}
int main(){
     for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            grid[i][j] = 0;
            bit[i][j] = 0;
        }
     }

}
