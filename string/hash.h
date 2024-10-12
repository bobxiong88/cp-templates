#include <bits/stdc++.h>
using namespace std;


// preprocess O(nlogn)
// query O(1)

struct Hash {
    using ll = long long;
    string s;
    int n;
    ll p1 = 31;
    ll p2 = 480575479;
    ll mod1 = int(1e9)+7;
    ll mod2 = int(1e9)+9;
    vector<ll> hs1, hs2;
    vector<ll> ppow1, ppow2;
    vector<ll> ipow1, ipow2;

    ll binpow(ll a, ll b, ll m) {
        if (b == 0)
            return 1;
        ll res = binpow(a, b / 2, m);
        if (b % 2)
            return ((res * res)%m * a)%m;
        else
            return (res * res)%m;
    }

    // ll modInv(ll a, ll m) {
    //     return binpow(a, m-2, m);
    // }

    void precompute(const string &s, ll p, ll mod, vector<ll> &hs, vector<ll> &ppow, vector<ll> &ipow) {
        hs.assign(n, 0);
        ppow.assign(n, 1);
        ipow.assign(n, 1);
        ll pp = binpow(p, mod-2, mod);
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

    Hash(const string &s) {
        n = s.length();
        precompute(s, p1, mod1, hs1, ppow1, ipow1);
        precompute(s, p2, mod2, hs2, ppow2, ipow2);
    }

    ll query(int l, int r) {
        if (l == 0) {
            return (hs1[r] << 31) + hs2[r];
        }
       
        ll h1 = (hs1[r]-hs1[l-1]+mod1)%mod1;
        ll res1 = (h1*ipow1[l])%mod1;

        ll h2 = (hs2[r]-hs2[l-1]+mod2)%mod2;
        ll res2 = (h2*ipow2[l])%mod2;

        return (res1 << 31) + res2; 
    }
};
