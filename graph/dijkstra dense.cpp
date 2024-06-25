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
 
vector<ll> dijkstra(vector<vector<pii>> g, int s) {
    int n = g.size();
    vector<ll> d(n, INF);
    vector<ll> d(n, -1);
    vector<bool> u(n, false);
    vector<ll> p(n, -1);

    d[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        u[v] = true;
        for (auto edge : g[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n+1);
    for (int i = 0; i < m; i++) {
        int a,b,c;
        cin >> a >> b >> c;
        g[a].pb({b,c});
    }
    auto dist = dijkstra(g, 1);
    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }cout << "\n";
}
