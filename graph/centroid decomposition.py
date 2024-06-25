import sys
input = sys.stdin.readline
def dfs(node, p):
    for n in graph[node]:
        if n == p: continue
        dfs(n, node)
        sub[node] += sub[n]
def cent(node, p, sz):
    for n in graph[node]:
        if n != p and sub[n] > sz/2: return cent(n, node, sz)
    return node
def build(node, p):
    sz = dfs(node, p)
    c = cent(node, p, sz)
    pa[c] = p
    for n in graph[node]:
        graph[n].remove(c)
        graph[c].remove(n)
        build(v, c)
N = int(input()) 
graph = [[] for i in range(N+1)]
for i in range(N-1):
    a,b = map(int,input().split())
    graph[a].add(b)
    graph[b].add(a)
sub = [1]*(N+1)
vis = [False]*(N+1)
par = [i for i in range(N+1)]
build(1, 1)


