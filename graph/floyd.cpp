#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int ll
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define pil pair<int, ll>
#define vi vector<int>
#define vvi vector<vector<int>> 

ll INF = 1e18;
 
vector<vector<ll>> floyd(vector<vector<pii>> g) {
    int n = g.size();
    vector<vector<ll>> dist(n, vector<ll> (n, INF));
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : g[u]) {
            dist[u][v] = min(dist[u][v], (ll)w);
        }
        dist[u][u] = 0;
    }
    for (int k = 0; k < n; k++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (dist[u][v] > dist[u][k] + dist[k][v]) {
                    dist[u][v] = dist[u][k] + dist[k][v];
                }
            }
        }
    }
    return dist;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    //freopen("kms.txt", "r", stdin);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<pii>> g(n+1);
    for (int i = 0; i < m; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        g[a].pb({b,c});
        g[b].pb({a,c});
    }
    auto dist = floyd(g);
    
    while (q--) {
        int a,b;
        cin >> a >> b;
        ll ans = dist[a][b];
        if (ans == INF) ans = -1;
        cout << ans << "\n";
    }
}
