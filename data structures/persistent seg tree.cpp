// heavily inspired by cp algorithms
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mx int(2e5)+5
int a[mx];
struct porn{
    porn *lt, *rt;
    int sum;
    porn(porn *lt, porn *rt, int x) : lt(lt), rt(rt), sum(x){if (lt) sum += lt->sum; if (rt) sum += rt->sum;}
};
porn* build(int tl, int tr){
    if (tl == tr) return new porn(nullptr, nullptr, a[tl]);
    int tm = (tl+tr)/2;
    return new porn(build(tl, tm), build(tm+1, tr), 0);
}
porn* update(porn *node, int tl, int tr, int p){
    if (tl == tr) return new porn(nullptr, nullptr, node->sum+1);
    int tm = (tl+tr)/2;
    if (p <= tm) return new porn(update(node->lt, tl, tm, p), node->rt, 0);
    else return new porn(node->lt, update(node->rt, tm+1, tr, p), 0);
}
int query(porn *node, int tl, int tr, int l, int r){
    if (l > r || tl > r || tr < l) return 0;
    if (tl >= l && tr <= r) return node->sum;
    int tm = (tl+tr)/2;
    return query(node->lt, tl, tm, l, r) + query(node->rt, tm+1, tr, l, r);
}
int qry(porn *s, porn *e, int tl, int tr, int k){
    if (tl == tr) return tl; // found!
    int tm = (tl+tr)/2;
    int left = e->lt->sum-s->lt->sum;
    if (left >= k) return qry(s->lt, e->lt, tl, tm, k);
    return qry(s->rt, e->rt, tm+1, tr, k-left);
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int N, Q, l, r, k;
    cin >> N >> Q;
    vector<int> sex; map<int,int> mp; set<int> used;
    vector<porn*> roots;
    roots.pb(build(1, N)); sex.pb(0);
    for (int i = 1; i<=N; i++){
        cin >> a[i];
        if (!used.count(a[i])){
            sex.pb(a[i]);
            used.insert(a[i]);
        }
    }
    sort(sex.begin(), sex.end());
    for (int i = 0; i<=N; i++) mp[sex[i]] = i;
    for (int i = 1; i<=N; i++) a[i] = mp[a[i]];
    for (int i = 1; i<=N; i++) roots.pb(update(roots.back(), 1, N, a[i]));
    int ans = 0;
    while (Q--){
        cin >> l >> r >> k; l^=ans; r^=ans; k^=ans;
        cout <<  (ans = sex[qry(roots[l-1], roots[r], 1, N, k)]) << "\n";
    }
}
