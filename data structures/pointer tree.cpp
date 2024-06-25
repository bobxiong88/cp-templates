#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mx int(4e5)+5
int a[mx];
struct porn{
    int tl, tr, sum;
    porn *lt, *rt;
};
vector<porn> t;
int build(porn *node){
    if (node->tl == node->tr){
        node->sum = a[node->tl];
        return node->sum;
        //return node;
    }
    int tm = (node->tl+node->tr)/2;
    porn *lft; lft = new porn();lft->tl = node->tl; lft->tr = tm;
    porn *rgt; rgt = new porn();rgt->tl = tm+1; rgt->tr = node->tr;
    //cout << lft.tl << " " << lft.tr << " " << rgt.tl << " " << rgt.tr << "\n";
    node->lt = rgt;
    node->rt = lft;
    return node->sum = build(node->lt)+build(node->rt);
    //return node;
}
int query(porn *node, int l, int r){
    //cout << node->tl << " " << node->tr << " " << node->sum << " " << node->lt << " " << node->rt << "\n";
    if (l > r || node->tl > r || node->tr < l) return 0;
    if (node->tl >= l && node->tr <= r) return node->sum;
    return query(node->lt, l, r) + query(node->rt, l, r);
}
void update(porn *node, int p, int v){
    porn *curr; curr = new porn();
    if (node->tl == node->tr){
        curr->sum = node->sum+v;
        return curr;
    }
    else {
        int tm = (node->tl+node->tr)/2;
        curr->tl = node->tl; curr->tr = node->tr;
        curr->lt = node->lt; curr->rt = node->rt;
        if (p <= tm){
            curr->lt = update(node->lt, p, v);
        }
        else{
            curr->rt = update(node->rt, p, v);
        }
        curr->sum = node->lt->sum+node->rt->sum;
    }
}
main(){
    int N, Q;
    cin >> N >> Q;
    int s = 0;
    for (int i = 1; i<=N; i++){cin >> a[i]; s += a[i];}
    porn *root;
    root = new porn();
    root->tl = 1;
    root->tr = N;
    root->sum = s;
    //t.pb(root);
    build(root);
    vector<porn*> roots;
    roots.pb(root);
    //cout << "ligma " << t[t[0].lt].tl << "\n";
    while (Q--){
        int q, a, b;
        cin >> q >> a >> b;
        if (q == 1){
            roots.pb(update(roots.back(), a, b));
        }
        else {
            cout << query(roots.back(), a, b) << "\n";
        }

    }
    /*
    vector<int> sex;
    map<int,int> mp;
    sex.pb(0);
    for (int i = 1; i<=N; i++){
        cin >> a[i];
        mp[a[i]] = i;
        sex.pb(a[i]);
    }
    sort(sex.begin(), sex.end());
    for (int i = 1; i<=N; i++){
        a[mp[sex[i]]] = i;
    }
    vector<int> root;
    root.pb(0);
    for (int i = 1; i<=N; i++){
        update((root.back(), a[i]));
    }
    */
}
/*
3 2
1 2 3
1 2
*/
