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


struct Sieve {
    vi sieve;
    int n;
    vi primes;
    Sieve(int n) : n{n} {
        sieve.assign(n+1, 1);
        sieve[0] = 0;
        sieve[1] = 0;
        for (int i = 2; i < n+1; i++) {
            if (sieve[i]) {
                for (int j = i*2; j < n+1; j += i) {
                    sieve[j] = 0;
                }
                primes.pb(i);
            }
        }            
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
}
