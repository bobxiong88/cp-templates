#include <bits/stdc++.h>
using namespace std;
using ll = long long;


// preprocess O(nlogn)
// query O(1)

struct Hash {
    string s;
    int n;
    ll p, mod;
    vector<ll> hs;
    vector<ll> ppow;
    vector<ll> ipow;

    ll binpow(ll a, ll b, ll m) {
        if (b == 0)
            return 1;
        ll res = binpow(a, b / 2, m);
        if (b % 2)
            return ((res * res)%m * a)%m;
        else
            return (res * res)%m;
    }

    ll modInv(ll a, ll m) {
        return binpow(a, m-2, m);
    }

    Hash(string s, int p = 41, int mod = 1000000009) : s{s}, n{s.length()}, p{p}, mod{mod} 
    {
        hs.assign(n, 0);
        ppow.assign(n, 1);
        ipow.assign(n, 1);
        int pp = binpow(p, mod-2, mod);
        for (int i = 1; i < n; i++) {
            ppow[i] = (ppow[i-1]*p)%mod;
            ipow[i] = (ipow[i-1]*pp)%mod;
        }
        ll h = 0;
        for (int i = 0; i < n; i++) {
            h += (s[i]*ppow[i])%mod;
            h %= mod;
            hs[i] = h;
        }
    }

    ll query(int l, int r) {
        if (l == 0) return hs[r];
        ll h = (hs[r]-hs[l-1]+mod)%mod;
        return (h*ipow[l])%mod;
    }
};