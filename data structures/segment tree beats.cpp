#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define mx 200005
struct node{
    int m1, m2, sum;
};
vector<node> t(mx*4);
vector<node> lazy(mx*4);
void tag(int v, int tl, int tr, int x){
    if(lazy[v] != 0)
    {
        t[v] +=
        t[v] += (tr - tl + 1) * lazy[v];
        if(tl != tr)
        {
            lazy[v*2] += lazy[v];
            lazy[v*2+1] += lazy[v];
        }
        lazy[v] = 0;
    }
}
void push(int v) {

}

void update(int v, int tl, int tr, int l, int r, int x) {
    if (tl > r || tr < l || t[v].m1 <= x)
        return;
    if (tl >= l && tr <= r && t[v].m2 < x) {
        // do funny
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    update(v*2, tl, tm, l, min(r, tm), addend);
    update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
    t[v] = max(t[v*2], t[v*2+1]);
}
int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return -2e9;
    if (l <= tl && tr <= r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v*2, tl, tm, l, min(r, tm)),
               query(v*2+1, tm+1, tr, max(l, tm+1), r));
}
main(){
    //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int M, N, Q, q, l, r, x;
    cin >> M >> N >> Q;
    for(int i = 0; i<Q; i++){
        cin >> q;
        if(q==1){
            cin >> l >> r >> x;
            updateRange(1, 1, N, l, r, x);
        }
        else{
            cin >> l >> r;
            cout << queryRange(1, 1, N, l, r) << "\n";
        }
    }
    return 0;
}
