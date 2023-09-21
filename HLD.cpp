// USACO cowland, supports xor
// mango_lassi's implementation: https://codeforces.com/blog/entry/67149
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define mx 200005
vector<vector<int>> adj(mx);
int val[mx];
int ord[mx];
int t[mx*2] = {0};
void update(int p, int value, int n){
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p]^t[p^1];
}
int query(int l, int r, int n){
    r++;
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l&1) res ^= t[l++];
        if (r&1) res ^= t[--r];
    }
    return res;
}
struct HLD {
	vector<int> par;
	vector<int> pp;
	vector<int> ind;
	HLD(const vector<int>& p) : par(p), pp(p.size()), ind(p.size(), -1) {
		int n = p.size();
		vector<int> siz(n, 1);
		for (int i = n-1; i > 0; --i) siz[par[i]] += siz[i];

		vector<int> pc(n, -1);
		for (int i = n-1; i > 0; --i) {
			if (2*siz[i] >= siz[par[i]]) pc[par[i]] = i;
		}
		int cur = 0;
		for (int i = 0; i < n; ++i) {
			if (ind[i] != -1) continue;
			for (int j = i; j != -1; j = pc[j], ++cur) {
				ind[j] = cur;
				pp[j] = i;
			}
		}
	}
	vector<pair<int, int>> get(int a, int b) {
		vector<pair<int, int>> res;
		while(true) {
			if (ind[b] < ind[a]) swap(a, b);
			if (ind[pp[b]] <= ind[a]) {
				res.push_back({ind[a], ind[b]});
				return res;
			} else {
				res.push_back({ind[pp[b]], ind[b]});
				b = par[pp[b]];
			}
		}
	}
    int lca(int a, int b) {
            while(true) {
                    if (ind[b] < ind[a]) swap(a, b);
                    if (ind[pp[b]] <= ind[a]) return a;
                    else b = par[pp[b]];
            }
    }
};
int dfs(int i, int p = -1, int j = 0) {
	ord[i] = j;
	j += 1;
	for (auto t : adj[i]) {
		if (t != p) j = dfs(t, i, j);
	}
	return j;
}
main(){
    //freopen("cowland.in", "r", stdin);
    //freopen("cowland.out", "w", stdout);
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int a, b, n, Q, q, i, v;
    cin >> n >> Q;
    for (int i = 1; i <= n; i++){
        cin >> val[i];
    }
    for (int i = 0; i < n-1; i++){
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
	dfs(0);
	vector<int> par(n, -1);
	for (int i = 0; i < n; ++i) {
		for (auto t : adj[i]) {
			if (ord[t] < ord[i]) par[ord[i]] = ord[t];
		}
	}
    HLD hld(par);
    for (int i = 1; i<=n; i++){
        update(hld.ind[ord[i-1]], val[i], n);
    }
    while(Q--){
        cin >> q;
        if (q == 1){
            cin >> i >> v;
            i--;
            i = ord[i];
            update(hld.ind[i], v, n);
        }
        else{
            cin >> a >> b;
            a--; b--;
            a = ord[a];
            b = ord[b];
            int ans = 0;
            for (auto p : hld.get(a, b)){
                ans ^= query(p.first, p.second, n);
            }
            cout << ans << "\n";
        }
    }
}
