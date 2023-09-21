#include <bits/stdc++.h>
using namespace std;
const int mx = int(1e5);
int t[mx*2];
void build(){
    for (int i = mx-1; i>0; --i) t[i] = t[i << 1] + t[i << 1 | 1];
}
void modify(int p, int value){
    for (t[p += n] = value; p>1; p>>=1) t[p>>1] = t[p] + t[p^1];
}
int query(int l, int r){
    r++;
    int res = 0;
    for (l += n, r += n; l<r; l>>=1, r>>=1){
        if(l&1) res += t[l++];
        if(r&1) res += t[--r];
    }
    return res;
}
int main(){
    int n, x;
    cin >> n;
    for (int i = 0; i<n; i++){
        cin >> x;
        t[n+i] = x;
    }
    build();
    // do stuff
}
