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
 
struct Node {
    int node; ll d;
    friend bool operator < (const Node &a, const Node &b) {
        return a.d > b.d;
    }
};
 
vector<ll> dijkstra(const vector<vector<pii>> &g, int s) {
    priority_queue<Node> q;
    q.push({s, 0});
    vector<ll> dist(g.size(), INF);
    dist[s] = 0;
    while (!q.empty()) {
        auto [u, d] = q.top(); q.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > d+w) {
                dist[v] = d+w;
                q.push({v, dist[v]});
            }
        }
    }
    return dist;
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
