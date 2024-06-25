#include <bits/stdc++.h>
using namespace std;

vector<int> vis;
vector<int> par;
vector<vector<int>> adj;

int cs, ce;

void cycleInit(int n) {
    vis.assign(n, 0);
    par.assign(n, -1);
    adj.assign(n, vector<int>());
}

bool cycle(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (v == par[u]) continue;
        if (vis[v]) {
            cs = v;
            ce = u;
            return true;
        } 
        par[v] = u;
        if (cycle(v)) return true;
    }
    return false;
}


int main() {

}