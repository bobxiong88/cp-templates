#include <bits/stdc++.h>
using namespace std;
const int m = 3001;
const int n = 3001;
int lsb(int x){
    return x&(-x);
}
int bit[m][n], grid[m][n];
int query(int x, int y){
    int res = 0;
    for (int i = x; i>0; i-=lsb(i)){
        for (int j = y; j>0; j-=lsb(j))
            res += bit[i][j];
    }
    return res;
}
void update(int x, int y, int v){
    for (int i = x; i<m; i+=lsb(i)){
        for (int j = y; j<m; j+=lsb(j))
            bit[i][j] += v;
    }
}
int qa(int x1, int y1, int x2, int y2){
    return query(x2, y2)-query(x2, y1-1)-query(x1-1,y2)+query(x1-1,y1-1);
}
