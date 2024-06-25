#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define pb push_back
#define mod int(1e9)+7
vector<int> n;
int T, N;
int mul[10][10];
vector<vector<int>> prod(vector<vector<int>> a, vector<vector<int>> b){
    for (int i = 0; i<T; i++){
        for (int j = 0; j<T; j++)
            mul[i][j] = 0;
    }
    for (int i = 0; i<T; i++){
        for (int j = 0; j<T; j++){
            for (int k = 0; k<T; k++){
                mul[i][j] += a[i][k]*b[k][j];
                mul[i][j] %= mod;
            }
        }
    }
    for (int i = 0; i<T; i++){
        for (int j = 0; j<T; j++)
            a[i][j] = mul[i][j];
    }
    return a;
}
vector<vector<int>> binpow(vector<vector<int>> a, int b){
    vector<vector<int>> res (T, vector<int> (T, 0));
    for (int i = 0; i<T; i++){
        for (int j = 0; j<T; j++)
            res[i][j] = int(i==j);
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
        res %= mod;
    }
    cout << res << "\n";
}
