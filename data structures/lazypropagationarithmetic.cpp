#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define mx 200005
int tree[mx*4];
int lazy[mx*4];
int A[mx];
void build(int node, int start, int endd)
{
    if(start == endd)
    {
        tree[node] = A[start];
    }
    else
    {
        int mid = (start + endd) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, endd);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}
void lazyUpdate(int node, int start, int endd){
    if(lazy[node] != 0)
    {
        int k = endd - start + 1;
        tree[node] += k * lazy[node];
        if(start != endd)
        {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}
void updateRange(int node, int start, int endd, int l, int r, int val) {
    lazyUpdate(node, start, endd);
    if(start > endd || start > r || endd < l)
        return;
    if(start >= l && endd <= r)
    {
        // Segment is fully within range
        tree[node] += (endd - start + 1) * val;
        if(start != endd)
        {
            // Not leaf node
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + endd) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, endd, l, r, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int queryRange(int node, int start, int endd, int l, int r)
{
    if(start > endd || start > r || endd < l)
        return 0;
    lazyUpdate(node, start, endd);
    if(start >= l && endd <= r)
        return tree[node];
    int mid = (start + endd) / 2;
    int p1 = queryRange(node*2, start, mid, l, r);
    int p2 = queryRange(node*2 + 1, mid + 1, endd, l, r);
    return (p1 + p2);
}
main(){
    //ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, Q, q, l, r, x;
    cin >> N >> Q;
    for(int i = 1; i<=N; i++)
        cin >> A[i];
    build(1, 1, N);
    for(int i = 0; i<Q; i++){
        cin >> q;
        if(q==1){
            cin >> l >> r >> x;
            updateRange(1, 1, N, l, r, x);
        }
        else{
            cin >> l >> r;
            cout << queryRange(1, 1, N, l, r) << "\n";
        }
    }
    return 0;
}
