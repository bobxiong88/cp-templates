#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
template <typename T> 
struct LazySegTree{
    using Operation = std::function<T(const T&, const T&)>;

};

struct BadLazy{
    vector<int> lazy, t, a;
    int n; 
private:
    void build(int node, int l, int r)
    {
        if(l == r)
        {
            t[node] = a[l];
        }
        else
        {
            int mid = (l + r) / 2;
            build(2*node, l, mid);
            build(2*node+1, mid+1, r);
            t[node] = t[2*node] + t[2*node+1];
        }
    }

    void lazyUpdate(int node, int l, int r) {
        if (lazy[node]!=0){
            t[node] += (r-l+1)*lazy[node];
            if (l != r){
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int l, int r, int a, int b, int v){
        lazyUpdate(node, l, r);
        if (l > r || l > b || a > r) return;
        if (a <= l && r <= b){
            t[node] += (r-l+1)*v;
            if (l != r){
                lazy[node*2] += v;
                lazy[node*2+1] += v;
            }
            return;
        }
        int mid = (l+r)/2;
        update(node*2, l, mid, a, b, v);
        update(node*2+1, mid+1, r, a, b, v);
        t[node] = t[node*2]+t[node*2+1];
    }

    int query(int node, int l, int r, int a, int b){
        if (l > r || l > b || a > r) return 0;
        lazyUpdate(node, l, r);
        if (a <= l && r <= b) return t[node];
        int mid = (l+r)/2;
        return query(node*2, l, mid, a, b)+query(node*2+1, mid+1, r, a, b);
    }
public:
    BadLazy(int n) {
        this->n = n+1; 
        t.assign(this->n*4, 0);
        lazy.assign(this->n*4, 0);
    }
    BadLazy(vector<int> &a) {
        this->n = a.size()+1;
        t.assign(this->n*4, 0);
        lazy.assign(this->n*4, 0);
        this->a.assign(a.size()+1, 0);
        for (int i = 0; i < a.size(); i++) this->a[i+1] = a[i];
        build(1, 1, this->n-1);
    }

    void update(int l, int r, int v) {
        update(1, 1, n-1, l+1, r+1, v);
    }

    int query(int l, int r) {
        return query(1, 1, n-1, l+1, r+1);
    }
};

main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    BadLazy t(a);
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, u;
            cin >> l >> r >> u;
            --l; --r;
            t.update(l, r, u);
        } else {
            int k;
            cin >>k;
            k--;
            cout << t.query(k, k) << "\n";
        }
    }
}