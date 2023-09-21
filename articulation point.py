# https://cp-algorithms.com/graph/cutpoints.html
import sys
input = sys.stdin.readline
def dfs(v, p):
    global cnt
    vis[v] = True
    tin[v] = low[v] = cnt
    cnt += 1
    children = 0
    for n in graph[v]:
        if n == p: continue
        if vis[n]:
            low[v] = min(low[v], tin[n])
        else:
            dfs(n, v)
            low[v] = min(low[v], low[n])
            if low[n] >= tin[v] and p != -1:
                cut[v] = True
            children += 1
    if p == -1 and children > 1:
        cut[v] = True
N, M = map(int,input().split())
graph = [[] for i in range(N+1)]
for i in range(M):
    a,b = map(int,input().split())
    graph[a].append(b)
    graph[b].append(a)
cnt = 0
cut = [False]*(N+1)
vis = [False]*(N+1)
tin = [-1]*(N+1)
low = [-1]*(N+1)
for i in range(1, N+1):
    if not vis[i]:
        dfs(i, -1)
print(cut.count(True))
for i in range(1,N+1):
    if cut[i]: print(i)
