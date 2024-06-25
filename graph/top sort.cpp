#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<bool> vis;
vector<bool> stk;
vector<int> order;

void cycleInit(int n) {
    adj.assign(n, vector<int>());
    vis.assign(n, false);
    stk.assign(n, false);
}

bool cycle(int u) {
    vis[u] = true;
    stk[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (cycle(v)) return true;
        } else if (stk[v]) return true;
    }
    stk[u] = false;
    order.pb(u);
    return false;
}