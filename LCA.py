import sys
from collections import deque
def euler(u):
    global idx
    vis[u] = True
    idx+=1
    tour[idx] = u
    for v in graph[u]:
        if not vis[v]:
            euler(v)
            idx+=1
            tour[idx] = u
def build():
    for i in range(n, 0, -1):
        if t[i<<1][0] <= t[i<<1|1][0]: t[i] = t[i<<1]
        else: t[i] = t[i<<1|1]
def lca(a, b):
    l, r = sorted([first[a], first[b]])
    r+=1
    mn = heights[l]
    res = tour[l]
    l+=n
    r+=n
    while l<r:
        if l&1:
            if t[l][0] < mn: mn, res = t[l]
            l+=1
        if r&1:
            r-=1
            if t[r][0] < mn: mn, res = t[r]
        r>>=1
        l>>=1
    return res
def query(a, b):
    c = lca(a, b)
    print(dist[a]+dist[b]-dist[c]*2)
input = sys.stdin.readline
N = int(input())
r=1#r = int(input())
graph = [[] for i in range(N+1)]
for i in range(N-1):
    a, b, w = map(int,input().split())
    graph[a].append(b)
    graph[b].append(a)
vis = [False for i in range(N+1)]
tour = [0 for i in range(N*2-1)]
idx = -1
euler(r)
queue = deque([(r, 1)])
dist = [float('inf') for i in range(N+1)]
dist[r] = 1
while queue:
    node, d = queue.popleft()
    for v in graph[node]:
        if dist[v] > d+1:
            dist[v] = d+1
            queue.append((v, d+1))
heights = [dist[i] for i in tour]
first = [float('inf') for i in range(N+1)]
for i in range(len(tour)): first[tour[i]] = min(i,first[tour[i]])
print(*tour)
print(*heights)
print(*first)
n = len(tour)
t = [[float('inf'),-1] for i in range(2*n+2)]
for i in range(n): t[n+i] = [heights[i], tour[i]]
build()
'''
15
15
4 5
7 13
13 15
9 15
9 2
14 13
1 9
6 1
14 10
8 9
11 8
4 7
14 3
12 9
'''
