#include <bits/stdc++.h>
using namespace std;


template <typename T>
struct SegTree {
    using Operation = std::function<T(const T&, const T&)>;

    vector<T> t;
    int n;
    T identity;
    Operation op;

    SegTree(int n, Operation op = std::plus<T>(), T identity = T()) {
        this->n = n;
        this->op = op;
        this->identity = identity;
        t.assign(2*n, identity);
    }

    SegTree(const vector<T> &a, Operation op = std::plus<T>(), T identity = T()) {
        this->n = a.size();
        this->op = op;
        this->identity = identity;
        t.assign(2*n, identity);
        for (int i = 0; i < n; i++) {
            t[n+i] = a[i];
        }
        build();
    }

    void build() {
        for (int i = n-1; i>0; --i) t[i] = op(t[i << 1], t[i << 1 | 1]);
    }
    void modify(int p, T value){
        for (t[p += n] = value; p >>= 1; p > 1) t[p] = op(t[p<<1], t[p<<1|1]);
    }

    T query(int l, int r){
        r++;
        T resl = identity;
        T resr = identity;
        for (l += n, r += n; l<r; l>>=1, r>>=1){
            if(l&1) resl = op(resl, t[l++]);
            if(r&1) resr = op(t[--r], resr);
        }
        return op(resl, resr);
    }

};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // take the min
    auto mn = [](int a, int b) {
        return min(a,b);
    };
    SegTree<int> t(a, mn, int(1e9));
    // do stuff
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k, u;
            cin >> k >> u;
            k--;
            t.modify(k, u);
        } else {
            int x,y;
            cin >> x >> y;
            --x; --y;
            cout << t.query(x,y) << "\n";
        }
    }
}
