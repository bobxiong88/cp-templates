#"inspired" by https://cp-algorithms.com/graph/strongly-connected-components.html
import sys
input = sys.stdin.readline
sys.setrecursionlimit(20005)
def dfs1(v):
    vis[v] = True
    for u in graph[v]:
        if not vis[u]:
            dfs1(u)
    order.append(v)
def dfs2(v):
    vis[v] = True
    comp.append(v)
    for u in rev[v]:
        if not vis[u]:
            dfs2(u)
N, M = map(int,input().split())
graph = [[] for i in range(N+1)]
rev = [[] for i in range(N+1)]
for i in range(M):
    a,b = map(int,input().split())
    graph[a].append(b)
    rev[b].append(a)
vis = [False]*(N+1)
order = []
for node in range(1,N+1):
    if not vis[node]:
        dfs1(node)
vis = [False]*(N+1)
comp = []
ans = []
for node in order[::-1]:
    if not vis[node]:
        dfs2(node)
        ans.append(sorted(comp))
        comp = []
print(len(ans))
for i in sorted(ans):
    print(*i)
    
