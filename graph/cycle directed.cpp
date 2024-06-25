#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> adj;
vector<int> c;
vector<int> par;

int ce, cs;

void cycleInit(int n) {
    adj.assign(n, vector<int>());
    c.assign(n, 0);
    par.assign(n, -1);
    cs = -1;
}

bool cycle(int v) {
    c[v] = 1;
    for (int u : adj[v]) {
        if (c[u] == 0) {
            par[u] = v;
            if (cycle(u))
                return true;
        } else if (c[u] == 1) {
            ce = v;
            cs = u;
            return true;
        }
    }
    c[v] = 2;
    return false;
}

int main() {
    
}