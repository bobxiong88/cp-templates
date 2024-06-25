#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int,int> 
#define pb push_back

struct Bridge{
    int n; 
    vector<vector<int>> adj; 

    vector<bool> visited;
    vector<int> tin, low;

    map<pii, int> mp;
    vi bridge;

    int timer;
    Bridge(int n, vector<pii> edges) {
        adj.assign(n, vi());
        bridge.assign(edges.size(), 0);
        this->n = n;
        for (int i = 0; i < edges.size(); i++) {
            auto [u, v] = edges[i];
            if (u > v) swap(u, v);
            mp[edges[i]] = i;
            adj[u].pb(v);
            adj[v].pb(u);
        }
    }

    void IS_BRIDGE(int v,int to) {
        if (v > to) swap(v, to);
        bridge[mp[{v, to}]] = 1;
    }

    void dfs(int v, int p = -1) {
        visited[v] = true;
        tin[v] = low[v] = timer++;
        bool parent_skipped = false;
        for (int to : adj[v]) {
            if (to == p && !parent_skipped) {
                parent_skipped = true;
                continue;
            }
            if (visited[to]) {
                low[v] = min(low[v], tin[to]);
            } else {
                dfs(to, v);
                low[v] = min(low[v], low[to]);
                if (low[to] > tin[v])
                    IS_BRIDGE(v, to);
            }
        }
    }

    void find_bridges() {
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
    }
};