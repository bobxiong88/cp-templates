#include <bits/stdc++.h>
using namespace std;
#define mx 100005
struct node{
    int sum, la, lb;
};
vector<node> t(4*mx);
vector<int> A(mx);
node poo;

node comb(node a, node b){
    node temp;
    temp.sum = a.sum+b.sum;
    temp.la = 0;
    temp.lb = 0;
    return temp;
}

void build(int node, int l, int r)
{
    if(l == r)
    {
        t[node] = {A[l], 0, 0};
    }
    else
    {
        int mid = (l + r) / 2;
        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
        t[node] = comb(t[2*node], t[2*node+1]);
    }
}

void lazyUpdate(int n, int l, int r){
    if (t[n].la){
        t[n].sum += (r-l+1)*t[n].la;
        if (l != r){
            t[2*n].la += t[n].la;
            t[2*n+1].la += t[n].la;
        }
        t[n].la = 0;
    }
    if (t[n].lb){
        int mid = (l+r)/2;
        t[n].sum += ((r-l+1)*(r-l+1)/2)*t[n].lb;
        if (l != r){
            t[2*n].lb += t[n].lb;
            t[2*n+1].lb += t[n].lb;
            t[2*n+1].la += t[n].lb*(mid-l+1);
        }
        t[n].lb = 0;
    }
}

void update(int n, int l, int r, int a, int b, int v, int k){
    lazyUpdate(n, l, r);
    if (l > r || l > b || a > r) return;
    if (a <= l && r <= b){
        t[n].la += v+(l-a)*k;
        t[n].lb += k;
        lazyUpdate(n, l, r);
        return;
    }
    int mid = (l+r)/2;
    update(n*2, l, mid, a, b, v, k);
    update(n*2+1,mid+1,r,a,b, v, k);
    t[n] = comb(t[2*n],t[2*n+1]);
}
node query(int n, int l, int r, int a, int b){
    lazyUpdate(n, l, r);
    if (l > r || l > b || a > r) return {0,0,0};
    if (a <= l && r <= b) return t[n];
    int mid = (l+r)/2;
    return comb(query(n*2, l, mid, a, b), query(n*2+1,mid+1,r,a,b));
}
int main(){
    // v -- starting pos
    // k -- increment
    int N, Q, a, b, v, k;
    char t;
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> A[i];
    build(1,1,N);
    while (Q--){
        cin >> t;
        if (t == 'A'){
            cin >> a >> b >> v >> k;
            update(1, 1, N, a, b, v, k);
            for (int i = 1; i<=N; i++) cout << query(1,1,N,i,i).sum << " ";
            cout << "\n";
        }
        else{
            cin >> a >> b;
            cout << query(1, 1, N, a, b).sum << "\n";
        }
    }
}
