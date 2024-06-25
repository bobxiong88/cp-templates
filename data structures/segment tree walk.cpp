// finds first element strictly smaller than k in range [l, r]



//heavily inspired by cp algorithms: https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-8
#include <bits/stdc++.h>
using namespace std;
#define n 1000005
int t[n*4];
int arr[n];
void build(int l, int r, int node) {
	if (l == r)
        t[node] = arr[l];
	else {
		int mid = (l + r) / 2;
		build(l, mid, node * 2);
		build(mid + 1, r, node * 2 + 1);
		t[node] = min(t[node * 2], t[node * 2 + 1]);
	}
}
int query(int tl, int tr, int l, int r, int node, int k) {
	if (tl > r || tr < l) return -1;
    if (t[node] < k) return -1;
    if (tl == tr) return tl;
	int mid = tl+(tr-tl)/2;
	int res = query(tl, mid, l, r, 2*node, k);
	if (res != -1) return res;
    return query(mid+1, tr, l, r, 2*node+1, k);
}
void update(int l, int r, int node, int p, int x) {
    if (l == r) {
        t[node] = x;
    } else {
        int m = (l + r) / 2;
        if (p <= m)
            update(l, m, node*2, p, x);
        else
            update(m+1, r, node*2+1, p, x);
        t[node] = min(t[node*2], t[node*2+1]);
    }
}
int main(){
    int N, Q, type, p, x, l, r, k;
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> N >> Q;
    for (int i = 1; i<=N; i++)
        cin >> arr[i];
    build(1, N, 1);
    int ans = 0;
    while (Q--){
        cin >> type;
        if (type == 1){
            cin >> p >> x;
            update(1, N, 1, p, x);
        }
        else{
            cin >> l >> r >> k;
            ans = query(1, N, l, r, 1, k);
            cout << ans << "\n";
        }
    }
}
