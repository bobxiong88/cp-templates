
#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#define int ll
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>> 

ll MOD = int(1e9)+7;
ll MOD2 = 999998727899999;

ll MINL = -ll(1e18);
ll MAXL = ll(1e18);
int MINI = -int(2e9);
int MAXI = int(2e9);

vector<pii> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

struct piii{
    int x,y,z;
};

bool piiiComp(const piii & a, const piii & b) {
    return a.x < b.x; 
}

template <typename T>
T sum(vector<T> &v) {
    T s = 0;
    for (int i = 0; i < v.size(); i++) s += v[i];
    return s;
}

template <typename T>
T max(vector<T> &v) {
    T s = v[0];
    for (int i = 0; i < v.size(); i++) s = max(s, v[i]);
    return s;
}

template <typename T>
T min(vector<T> &v) {
    T s = v[0];
    for (int i = 0; i < v.size(); i++) s = min(s, v[i]);
    return s;
}

template <typename T>
void print(vector<T> &v, string sep = " ", int l = 0, int r = MOD2) {
    for (int i = max((int)0, l); i <= min((int)v.size()-1, r); i++) {
        cout << v[i] << sep;
    } cout << "\n";
}

ll binpow(ll a, ll b, ll m = MOD) {
    if (b == 0)
        return 1;
    ll res = binpow(a, b / 2, m);
    if (b % 2)
        return ((res * res)%m * a)%m;
    else
        return (res * res)%m;
}

ll mod(ll a, ll b = MOD) {
    return (b + (a % b)) % b;
}

ll modInv(ll a, ll m = MOD) {
    return binpow(a, m-2, m);
}

ll div(ll a, ll b, ll m = MOD) {
    return a*modInv(b, m)%m;
} 

ll fact(ll x, ll m = MOD) {
    ll res = 1;
    for (int i = 1; i <= x; i++) res = (res*i)%m;
    return res;
}

ll choose(ll n, ll k, ll m = MOD) {
    return (((fact(n)*modInv(fact(k)))%m)*modInv(fact(n-k)))%m;
}

ll permute(ll n, ll k, ll m = MOD) {
    return fact(n)*modInv(fact(n-k))%m; 
}

bool in_range(ll n, ll x) {
    return 0 <= x && x < n;
}

struct V {
	vector<pii> outs; // (dest, edge index)
	int nins = 0;
};

vector<int> eulerianWalk(int V, const vector<pair<int, int>> &edges,
                         bool directed, bool circuit, int s = -1) {
  if (V == 0) return vector<int>();
  else if (edges.empty()) return vector<int>{0};
  vector<int> st(V + 1, 0), d(V, 0), walk; walk.reserve(edges.size() + 1);
  vector<int> to(edges.size() * (directed ? 1 : 2)), eInd(to.size());
  for (auto &&e : edges) {
    st[e.first]++; d[e.second]++;
    if (!directed) { st[e.second]++; d[e.first]++; }
  }
  if (s == -1) {
    s = edges[0].first; if (circuit) {}
    else if (directed) { for (int v = 0; v < V; v++) if (st[v] > d[v]) s = v; }
    else { for (int v = 0; v < V; v++) if (d[v] % 2 == 1) s = v; }
  }
  partial_sum(st.begin(), st.end(), st.begin()); fill(d.begin(), d.end(), 0);
  for (int i = 0, v, w; i < int(edges.size()); i++) {
    tie(v, w) = edges[i]; to[--st[v]] = w; eInd[st[v]] = i;
    if (!directed) { to[--st[w]] = v; eInd[st[w]] = i; }
  }
  vector<int> cur = st, stk(edges.size() + 1);
  vector<bool> vis(edges.size(), false);
  int top = 0; d[stk[top++] = s]++; while (top > 0) {
    int v = stk[top - 1];
    if (cur[v] == st[v + 1]) { walk.push_back(v); --top; continue; }
    int w = to[cur[v]], e = eInd[cur[v]++];
    if (!vis[e]) { d[v]--; d[stk[top++] = w]++; vis[e] = true; }
  }
  if ((circuit && walk[0] != walk.back())
      || walk.size() != edges.size() + 1) return vector<int>();
  for (int di : d) if (di < 0) return vector<int>();
  reverse(walk.begin(), walk.end()); return walk;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        edges.pb({a,b});
    }
    auto res = eulerianWalk(n+1, edges, 0, 1, 1);
    if (res.empty()) {
        cout << "IMPOSSIBLE" << "\n";
    } else {
        print(res);
    }
    
}