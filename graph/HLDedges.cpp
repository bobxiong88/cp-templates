// stupid QTREE problem
// codeforces Black.n.White's implementation

#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define mp make_pair

const int N = 20000;

int n, heavy[N], root[N], p[N];
int pos[N], num[N], depth[N], t[4*N], a[N], b[N], vtx[N];
vector<pair<int, pair<int, int> > > g[N];
int dfs(int v = 0, int prnt = -1, int d = 0)
{
	int size = 1, maxsize = 0;
	depth[v] = d;
	p[v] = prnt;
	for(int i=0;i<g[v].size();++i)
	{
		int u = g[v][i].X;
		int c = g[v][i].Y.X , idx = g[v][i].Y.Y;
		if(u != prnt)
		{
			int subsize = dfs(u, v, d + 1);
			if(subsize > maxsize)
			{
				maxsize = subsize;
				heavy[v] = u;
			}
			vtx[idx] = u;
			size += subsize;
			a[u] = c;
		}
	}
	return size;
}
void hld()
{
	for(int i=0, currpos = 0; i < n; ++i)
		if(p[i] == -1 || heavy[p[i]] != i)
			for(int j = i; j != -1; j = heavy[j])
			{
				root[j] = i;
				num[j] = currpos; b[currpos] = a[j];
				currpos++;
			}
}
void update(int p, int value){
    p+=n;
    t[p] = value;
    for (; p > 1; p >>= 1) t[p>>1] = max(t[p], t[p^1]);
}
int query(int l, int r){
    r++;
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1){
        if (l&1) res = max(res,t[l++]);
        if (r&1) res = max(res,t[--r]);
    }
    return res;
}
int find(int a, int b)
{
	int res = 0;
	while(root[a] != root[b])
	{
		if(depth[root[a]] < depth[root[b]])
			swap(a, b);
		res = max(res, query(num[root[a]], num[a]));
		a = p[root[a]];
	}
	if(depth[a] > depth[b])
		swap(a, b);
	res = max(res, query(num[a] + 1, num[b]));
	return res;
}
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i=0;i<n -1;++i)
    {
        int a, b, c;
        cin >> a >> b >> c; a--; b--;
        g[a].push_back(mp(b, mp(c, i) ) );
        g[b].push_back(mp(a, mp(c, i) ) );
    }
    for(int i=0;i<n;++i)
        heavy[i] = -1;
    a[0] = 0;
    dfs(0); hld();
    for (int i = 0; i<n-1; i++)
        update(num[vtx[i]],b[num[vtx[i]]]);
    while(1)
    {
        char s[10];
        cin >> s;
        if(s[0] == 'D')break;
        else if(s[0] == 'C')
        {
            int i, ti;
            cin >> i >> ti; i--;
            update(num[vtx[i]], ti);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--; b--;
            cout << find(a,b) << "\n";
        }
    }
	return 0;
}
