#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
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

int root(int k, int p) {
    int l = 1;
    int r = k;
    int ans = 1;
    while (l <= r) {
        int m = (l+r)/2;
        if (binpow(m, p) <= k) {
            ans = m;
            l = m+1;
        } else {
            r = m-1;
        }
    }
    return ans;
}

struct Psa {
    vi psa;
    Psa(vi a) {
        if (!a.empty()) psa.pb(a[0]);
        for (int i = 1; i < a.size(); i++) {
            psa.pb(psa[i-1]+a[i]);
        }
    }
    ll sum(int l, int r) {
        if (l > r) return 0;
        if (l == 0) return psa[r];
        return psa[r]-psa[l-1];
    }
};

template <typename T>
struct SegTree {
    using Operation = std::function<T(const T&, const T&)>;

    vector<T> t;
    int n;
    T identity;
    Operation op;

    SegTree() {};
    SegTree(int n, Operation op = std::plus<T>(), T identity = T()) {
        this->n = n;
        this->op = op;
        this->identity = identity;
        t.assign(2*n, identity);
    }

    SegTree(const vector<T> &a, Operation op = std::plus<T>(), T identity = T()) {
        this->n = a.size();
        this->op = op;
        this->identity = identity;
        t.assign(2*n, identity);
        for (int i = 0; i < n; i++) {
            t[n+i] = a[i];
        }
        build();
    }

    void build() {
        for (int i = n-1; i>0; --i) t[i] = op(t[i << 1], t[i << 1 | 1]);
    }
    void modify(int p, T value){
        for (t[p += n] = value; p >>= 1; p > 1) t[p] = op(t[p<<1], t[p<<1|1]);
    }

    T query(int l, int r){
        r++;
        T resl = identity;
        T resr = identity;
        for (l += n, r += n; l<r; l>>=1, r>>=1){
            if(l&1) resl = op(resl, t[l++]);
            if(r&1) resr = op(t[--r], resr);
        }
        return op(resl, resr);
    }

};

template <typename T>
struct HLD {
    using Operation = std::function<T(const T&, const T&)>;

    vi ord, par, pp, ind;
    int n;
    vvi adj;
    vector<T> val;
    SegTree<T> t;
    T identity;
    Operation op;
    int dfs(int i, int p = -1, int j = 0) {
        ord[i] = j;
        j += 1;
        for (auto t : adj[i]) {
            if (t != p) j = dfs(t, i, j);
        }
        return j;
    }

	HLD(int n, const vvi &adj, vector<T> &val, Operation op = std::plus<T>(), T identity = T()) 
        : n{n}, adj{adj}, val{val}, op{op}, identity{identity} 
    {
        par.assign(n, -1);
        pp.assign(n, -1);
        ind.assign(n, -1);
        ord.assign(n, 0);

        dfs(0);

        for (int i = 0; i < n; ++i) {
            for (auto t : adj[i]) {
                if (ord[t] < ord[i]) par[ord[i]] = ord[t];
            }
        }
		vector<int> siz(n, 1);
		for (int i = n-1; i > 0; --i) siz[par[i]] += siz[i];

		vector<int> pc(n, -1);
		for (int i = n-1; i > 0; --i) {
			if (2*siz[i] >= siz[par[i]]) pc[par[i]] = i;
		}
		int cur = 0;
		for (int i = 0; i < n; ++i) {
			if (ind[i] != -1) continue;
			for (int j = i; j != -1; j = pc[j], ++cur) {
				ind[j] = cur;
				pp[j] = i;
			}
		}
        vector<T> shifted(n);
        for (int i = 0; i < n; i++) {
            shifted[ind[ord[i]]] = val[i];
        }
        t = SegTree<T>(shifted, op, identity);
	}
	vector<pair<int, int>> get(int a, int b) {
		vector<pair<int, int>> res;
		while(true) {
			if (ind[b] < ind[a]) swap(a, b);
			if (ind[pp[b]] <= ind[a]) {
				res.push_back({ind[a], ind[b]});
				return res;
			} else {
				res.push_back({ind[pp[b]], ind[b]});
				b = par[pp[b]];
			}
		}
	}
    int lca(int a, int b) {
            while(true) {
                    if (ind[b] < ind[a]) swap(a, b);
                    if (ind[pp[b]] <= ind[a]) return a;
                    else b = par[pp[b]];
            }
    }
    void update(int u, T x) {
        t.modify(ind[ord[u]], x);
    }
    T query(int a, int b) {
        a = ord[a];
        b = ord[b];
        T ans = identity;
        vector<pii> res = get(a,b);
        for (auto p : get(a, b)) {
            ans = op(ans, t.query(p.first, p.second));
        }
        return ans;
    }
};

main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int a, b, n, Q, q, i, v;
    cin >> n >> Q;
    vi val(n);
    vvi adj(n, vi());
    for (int i = 0; i < n; i++){
        cin >> val[i];
    }
    for (int i = 0; i < n-1; i++){
        cin >> a >> b;
        --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    auto op = [](int a, int b) {
        return max(a, b);
    };
    HLD<int> hld(n, adj, val, op, 0);
    for (int i = 0; i < Q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int s, x;
            cin >> s >> x;
            --s;
            hld.update(s, x);
        } else {
            int a, b;
            cin >> a >> b;
            --a; --b;
            cout << hld.query(a, b) << " ";
        }
    }
}
