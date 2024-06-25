#include <bits/stdc++.h>
using namespace std;
struct Dsu {
    vector<int> par,sz;
    Dsu(int n) {
        par.assign(n, 0);
        sz.assign(n,1);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }
    int find(int v) {
        if (v == par[v]) return v;
        return par[v] = find(par[v]);
    }

    bool join(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u,v);
        sz[u] += sz[v];
        par[v] = u;
        return true;
    }
};