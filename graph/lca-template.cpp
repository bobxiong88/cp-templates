#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int bit = 25;
    vector<vector<int>> adj, up;
    vector<int> in, out, ht;
    int cnt;
    int n;

    void dfs(int node, int p) {
        ht[node] = ht[p] + 1;
        in[node] = ++cnt;
        up[node][0] = p;
        for (int i = 1; i < bit; i++) {
            up[node][i] = up[up[node][i-1]][i-1];
        }
        for (auto n : adj[node]) {
            if (n != p) {
                dfs(n, node);
            }
        }
        out[node] = cnt;
    }
    bool check(int a, int b) {
        return in[a] <= in[b] && out[a] >= out[b];
    }

    int lca(int a, int b) {
        if (check(a, b)) return a;
        if (check(b, a)) return b;
        for (int i = bit-1; i >= 0; i--) {
            if (!check(up[a][i], b)) {
                a = up[a][i];
            }
        }
        return up[a][0];
    }

    LCA(int n, vector<vector<int>> adj) : n{n}, adj{adj} {
        cnt = 0;
        in.assign(n, 0);
        out.assign(n, 0);
        ht.assign(n, 0);
        up.assign(n, vector<int>(bit, 0));
        dfs(0, 0);
    }
};