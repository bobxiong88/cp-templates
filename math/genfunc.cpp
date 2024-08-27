#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define pb push_back
ll MOD = int(1e9)+7;
vector<vector<int>> prod(const vector<vector<int>>&a,  const vector<vector<int>>&b, int mod = MOD){
    int n = a.size();
    vector<vector<int>> mul(n, vector<int>(n));
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            for (int k = 0; k<n; k++){
                mul[i][j] = (a[i][k]*b[k][j] + mul[i][j])%mod;
            }
        }
    }
    return mul;
}
vector<vector<int>> binpow(vector<vector<int>> &a, int b, int mod = MOD){
    int n = a.size();
    vector<vector<int>> res (n, vector<int> (n));
    for (int i = 0; i<n; i++){
        res[i][i] = 1;
    }
    while (b > 0){
        if (b & 1) res = prod(res, a);
        a = prod(a, a);
        b >>= 1;
    }
    return res;
}
main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T, N;
    cin >> T >> N;
    N--;
    vector<vector<int>> base(T, vector<int>(T, 0));
    vector<vector<int>> ans(T, vector<int>(T, 0));
    for (int i = 0; i<T; i++){
        cin >> base[0][i];
    }
    for (int i = 1; i<T; i++){
        base[i][i-1] = 1;
    }
    for (int i = 0; i<T; i++){
        ans[i][i] = 1;
    }
    ans = prod(ans, binpow(base, N));
    int res = 0;
    for (int i = 0; i<T; i++){
        res += ans[T-1][i];
        res %= MOD;
    }
    cout << res << "\n";
}
