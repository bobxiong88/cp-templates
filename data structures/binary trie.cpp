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

template <typename T>
void read(vector<T> &a, int n) {
    for (int i = 0; i < n; i++) cin >> a[i];
}

struct TrieNode {
    TrieNode *l;
    TrieNode *r;
    TrieNode *p = nullptr;
    int cnt = 0;
    TrieNode() : l{nullptr}, r{nullptr} {};
    TrieNode(TrieNode *p) : p{p} {};
    TrieNode(TrieNode *l, TrieNode *r) : l{l}, r{r} {};
    TrieNode(TrieNode *l, TrieNode *r, int cnt) : l{l}, r{r}, cnt{cnt} {};
};

struct BinaryTrie{
    int sz = 30;
    BinaryTrie(){};

    BinaryTrie(int sz) : sz{sz} {};
    
    TrieNode *root = new TrieNode(nullptr, nullptr);

    void insert(int x) {
        TrieNode *curr = root;
        for (int i = sz-1; i >= -1; i--) {
            if (i == -1) {
                curr->cnt++;
            } else {
                if ((x>>i)&1) {
                    if(curr->r == nullptr) curr->r = new TrieNode(curr);
                    curr = curr->r;
                } else {
                    if (curr->l = nullptr) curr->l = new TrieNode(curr);
                    curr = curr->l;
                }
            }
        }
    }

    void erase(int x) {
        TrieNode *curr = root;
        for (int i = sz-1; i >= -1; i--) {
            if (i == -1) {
                curr->cnt--;
            } else {
                if ((x>>i)&1) {
                    curr = curr->r;
                } else {
                    curr = curr->l;
                }
            }
        }
        if (curr->cnt == 0) {
            if (curr->p->l == curr) curr->p->l = nullptr;
            else curr->p->r = nullptr;
            curr = curr->p;
        }
        while (curr != root) {
            if (curr->l == nullptr && curr->r == nullptr) {
                if (curr->p->l == curr) curr->p->l = nullptr;
                else curr->p->r = nullptr;
            }
            curr = curr->p;
        }
    }

    int max(int x) {
        TrieNode *curr = root;
        int ans = 0;
        for (int i = sz-1; i >= 0; i--) {
            if ((x>>i)&1) {
                if (curr->l) {
                    ans |= 1<<i;
                    curr = curr->l;
                } else {
                    curr = curr->r;
                }
            } else {
                if (curr->r) {
                    ans |= 1<<i;
                    curr = curr->r;
                } else {
                    curr = curr->l;
                }
            }
        }
        return ans;
    }
};

vector<vector<pii>> adj;

vi d, len;

void dfs(int u, int p, int x, int h) {
    d[u] = x;
    len[u] = h;
    for (auto [v, w] : adj[u]) {
        if (v== p) continue;
        dfs(v, u, x^w, h+1);
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        adj.assign(n+1, vector<pii>());
        d.assign(n+1, 0);
        for (int i = 0; i < n-1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].pb({v,w});
            adj[v].pb({u,w});
        }
        dfs(1,1, 0, 0);
        BinaryTrie t(30);
        for (int i = 1; i <= n; i++) {
            t.insert(d[i]);
        }
        int s = 0;
        while (m--) {
            char c;
            cin >> c;
            if (c == '^') {
                int y;
                cin >> y;
                s ^= y;
            } else {
                int  v, x;
                cin >> v >> x;
                int ans;
                for ()
            }
        }
    }
}
