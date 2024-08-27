#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define pb push_back
const int MOD = int(1e9)+7;


vector<vector<int>> prod(vector<vector<int>> a, vector<vector<int>> b, int mod = MOD){
    int n = a.size();
    vector<vector<int>> mul(n, vector<int>(n, 0));
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            for (int k = 0; k<n; k++){
                mul[i][j] += a[i][k]*b[k][j];
                mul[i][j] %= mod;
            }
        }
    }
    return mul;
}
vector<vector<int>> binpow(vector<vector<int>> a, int b, int mod = MOD){
    int n = a.size();
    vector<vector<int>> res (n, vector<int> (n, 0));
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++)
            res[i][j] = int(i==j);
    }
    while (b > 0){
        if (b & 1) res = prod(res, a, mod);
        a = prod(a, a, mod);
        b >>= 1;
    }
    return res;
}

