
using namespace std;
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int ll
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>> 

// has to be 1-indexed
struct Bit2{
    vvi grid;
    vvi bit;
    int n,m;

    int LSB(int x){
        return x & (-x);
    }

    int query(int x, int y){
        if (x < 0 || y < 0) return 0;
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
        for (int xi = x; xi < n; xi += LSB(xi)){
            for (int yi = y; yi < m; yi += LSB(yi)){
                bit[xi][yi] += value;
            }
        }
    }
    void build(){
        for (int i = 1; i < n; ++i){
            for (int j = 1; j < m; ++j){
                update(i, j, grid[i][j]);
            }
        }
    }

    Bit2(vvi grid) : grid{grid} {
        n = grid.size();
        m = grid[0].size();
        bit.assign(n, vi(m, 0));
        build();
    }
};