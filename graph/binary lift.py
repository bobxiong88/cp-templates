import sys
input = sys.stdin.readline
from math import *
def lift(node, p, h):
    ht[node] = h
    if h:
        for i in range(floor(log(h,2))+1):
            if not i:
                up[node][i] = p
                continue
            res = node
            up[node][i] = up[up[node][i-1]][i-1]
    else:
        up[node][0] = node
    for n in graph[node]:
        if n == p: continue
        lift(n, node, h+1)
def ans(node, k):
    b = bin(k)[2:]
    b = list(map(int,list(b[::-1])))
    res = node
    for i, x in enumerate(b):
        if x: res = up[res][i]
    return res
def check(a, b):
    if ht[a]<ht[b]:
        k = ht[b]-ht[a]
        if ans(b, k) == a:
            return True
        return False
    else:
        return False
def lca(a, b):
    if a == b: return a
    if check(a,b):
        return a
    if check(b,a):
        return b
    for i in range(l, -1, -1):
        if not check(up[a][i], b):
            a = up[a][i]
    return up[a][0]
N = int(input())
l = ceil(log(N,2))
graph = [[] for i in range(N+1)]
par = [i for i in range(N+1)]
up = [[1 for i in range(l+1)] for j in range(N+1)]
ht = [0]*(N+1)
for i in range(N-1):
    a,b = map(int,input().split())
    graph[a].append(b)
    graph[b].append(a)
lift(1, 1, 0)

