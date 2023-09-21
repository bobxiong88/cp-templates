// upsolve
#include <bits/stdc++.h>
using namespace std;
#define mx 100005
#define bit 19
#define pb push_back
int cnt, in[mx], out[mx], up[mx][bit], ht[mx];
vector<int> adj[mx];
// thanks thomas for less cancerous implementation
void dfs(int node, int p){
    ht[node] = ht[p]+1;
    in[node] = ++cnt; up[node][0] = p;
    for (int i = 1; i<bit; i++) up[node][i] = up[up[node][i-1]][i-1];
    for (auto n: adj[node]){
        if (n == p) continue;
        dfs(n, node);
    }
    out[node] = cnt;
}
bool check(int a, int b){
    return in[a] <= in[b] && out[a] >= out[b];
}
int lca(int a, int b){
    if (check(a, b)) return a;
    if (check(b, a)) return b;
    for (int i = bit-1; i >=0; i--){
        if (!check(up[a][i], b))
            a = up[a][i];
    }
    return up[a][0];
}
int dist(int a, int b){
    int c = lca(a,b);
    return ht[a]+ht[b]-2*ht[c];
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int N, M, a, b, c, r, u, v;
    cin >> N;
    for (int i = 0; i<N-1; i++){
        cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(1, 1);
    cin >> M;
    while(M--){
        cin >> r >> u >> v;
        a = lca(r, u);
        b = lca(r, v);
        c = lca(u, v);
        int res;
        if (a == b)
            res = c;
        else if(b == c)
            res = a;
        else
            res = b;
        cout << res << "\n";

    }
}
