#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//#define int ll
#define dbg(x) cout << #x << ": " << x << '\n'
#define pb push_back

// kactl stuff
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef long double ld;

ll MOD = int(1e9)+7;
ll MOD2 = 999998727899999;

// const ll MINL = -9223372036854775808;
// const ll MAXL = 9223372036854775807;
// const int MINI = -2147483648;
// const int MAXI = 2147483647;

ll binpow(ll a, ll b, ll m = MOD) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
}
