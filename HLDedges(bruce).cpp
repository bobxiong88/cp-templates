#include <bits/stdc++.h>
using namespace std;

struct DSU{
	vector<int> p, sz;
	int nsets;
	DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(),0); nsets = n; }
	int find(int u) { return u == p[u] ? u : p[u] = find(p[u]); }
	void join(int u, int v){
		u = find(u); v = find(v);
		if(u == v) return;
		if(sz[u] > sz[v]) swap(u,v);
		sz[v] += sz[u];
		p[u] = v;
		nsets--;
	}
	int get_size(int u) { return sz[find(u)]; }
	bool same_set(int u, int v) { return find(u) == find(v); }
	int num_sets() { return nsets; }
};

const int MM = 1e5+5;
int n,m;
vector<int> adj[MM];
struct edge{
    int u,v,w;
};vector<edge> el,extra,in;

// HLD BEGIN
int t[2*MM],tot,dep[MM],w[MM],fa[MM],top[MM],son[MM],sz[MM];

void upd(int x, int v){
    for(t[x+=tot]=v; x > 1; x>>=1) t[x>>1]=max(t[x],t[x^1]);
}

int query(int l, int r){
    int res = 0; r++;
    for(l+=n,r+=n; l < r; l >>= 1, r >>= 1){
        if(l&1) res = max(res,t[l++]);
        if(r&1) res = max(res,t[--r]);
    }
    return res;
}

void dfs(int u){
    sz[u] = 1;
    for(int& v : adj[u]){
        if(v == fa[u]) continue;
        fa[v] = u; dep[v] = dep[u]+1;
        dfs(v); if(sz[v] > sz[son[u]]) son[u] = v;
        sz[u] += sz[v];
    }
}

void build(int u, int tp){
    top[u] = tp; w[u] = ++tot;
    if(son[u] != 0) build(son[u],top[u]);
    for(int& v : adj[u]){
        if(v != son[u] && v != fa[u])
            build(v,v);
    }
}

int query1(int u, int v){
    int f1 = top[u], f2 = top[v],ans = 0;
    while(f1 != f2){
        if(dep[f1]<dep[f2]){swap(f1,f2); swap(u,v); }
        ans = max(ans,query(w[f1],w[u])); u = fa[f1]; f1 = top[u];
    }
    if(u == v) return ans;
    if(dep[u] > dep[v]) swap(u,v);
    return max(ans,query(w[son[u]], w[v]));
}

int main(){
    cin >> n >> m;
    DSU d(n+1);
    for(int i = 0; i < m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        el.push_back({a,b,c});
    }
    sort(el.begin(), el.end(),[](edge& a, edge& b){return a.w < b.w; });
    int ans = 0;
    int cnt = 0;
    for(int i = 0; i < m; i++){
        if(d.same_set(el[i].u,el[i].v)){
            extra.push_back(el[i]);
            continue;
        }
        d.join(el[i].u,el[i].v);
        ans += el[i].w;
        adj[el[i].u].push_back(el[i].v);
        adj[el[i].v].push_back(el[i].u);
        in.push_back(el[i]); cnt++;
    }
    if(cnt < n-1){
        cout << "-1"; return 0;
    }
    dfs(1);
    build(1,1);
    // update original edges
    for(edge& e : in){
        if(dep[e.u] > dep[e.v]) swap(e.u,e.v);
        upd(w[e.v],e.w);
    }
    int INF = 2000000000;
    int res = INF;
    for(edge& e : extra){
        int cur = query1(e.u,e.v);
        if(e.w > cur){res = min(res,ans - cur + e.w); }
    }
    if (res == INF)
        cout << -1;
    else
        cout << res;
}
