#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
vector<int> adj[N];

bool cycle(int u, vector<bool> &vis, vector<bool> &stack) {
    vis[u] = true;
    stack[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (cycle(v, vis, stack)) return true;
        } else if (stack[v]) return true;
    }
    stack[u] = false;
}

int main() {

}