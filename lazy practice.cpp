#include <bits/stdc++.h>
using namespace std;
#define mx 100005
int lazy[mx*4], t[mx*4];
/*
void build(int node, int l, int r)
{
    if(l == r)
    {
        t[node] = A[l];
    }
    else
    {
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        t[node] = t[2*node] + t[2*node+1];
    }
}
*/
void lazyUpdate(int node, int l, int r){
    if (lazy[node]!=0){
        t[node] += (r-l+1)*lazy[node];
        if (l != r){
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}
void update(int node, int l, int r, int a, int b, int v){
    lazyUpdate(node, l, r);
    if (l > r || l > b || a > r) return;
    if (a <= l && r <= b){
        t[node] += (r-l+1)*v;
        if (l != r){
            lazy[node*2] += v;
            lazy[node*2+1] += v;
        }
        return;
    }
    int mid = (l+r)/2;
    update(node*2, l, mid, a, b, v);
    update(node*2+1, mid+1, r, a, b, v);
    t[node] = t[node*2]+t[node*2+1];
}
int query(int node, int l, int r, int a, int b){
    if (l > r || l > b || a > r) return 0;
    lazyUpdate(node, l, r);
    if (a <= l && r <= b) return t[node];
    int mid = (l+r)/2;
    return query(node*2, l, mid, a, b)+query(node*2+1, mid+1, r, a, b);
}
int main(){
    char t;
    int N, Q, a, b, v;
    cin >> N >> Q;
    while (Q--){
        cin >> t >> a >> b;
        if (t == 'A'){
            cin >> v;
            update(1, 0, N, a, b, v);
            for (int i = 0; i< N; i++)
                cout << query(1, 0, N-1, i, i) << " ";
            cout << "\n";
        }
        else{
            cout << query(1, 0, N-1, a, b) << "\n";
        }
    }
}
