#include <bits/stdc++.h>
using namespace std;
const int mx = int(2e5)+5;
int t[mx*4], A[mx];
void build(int node, int tl, int tr){
    if (tl == tr){
        t[node] = A[tl];
    }
    else{
        int tm = (tl+tr)/2;
        build(node*2, tl, tm);
        build(node*2+1, tm+1, tr);
        t[node] = t[node*2] + t[node*2+1];
    }
}
void update(int node, int tl, int tr, int p, int x){
    if (tl == tr){
        t[node] = x;
    }
    else{
        int tm = (tl+tr)/2;
        if (p <= tm) update(node*2, tl, tm, p, x);
        else update(node*2+1, tm+1, tr, p, x);
        t[node] = t[node*2]+t[node*2+1];
    }
}
int query(int node, int tl, int tr, int l, int r){
    if (tl > tr || tl > r || l > tr) return 0;
    if (l <= tl && tr <= r) return t[node];
    int tm = (tl+tr)/2;
    return query(node*2, tl, tm, l, r)+query(node*2+1, tm+1, tr, l, r);
}
int main(){
}
