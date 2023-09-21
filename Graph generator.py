import sys
from random import *
#input = sys.stdin.readline
def find(v):
    if parent[v] == v: return v
    parent[v] = find(parent[v])
    return parent[v]
def union(u,v):
    a,b = find(u), find(v)
    if a == b: return
    edges.append((u,v))
    if size[a]<size[b]: a,b = b,a
    parent[b] = a
    size[a] += size[b]
l,r = 0,0
edges = set()
f =open('data.txt', 'w')
IO = eval(input('std or file(True/False)'))
N = int(input('V: '))
one = eval(input('One or zero indexed(True/False)'))
weight = eval(input('Weighted or unweighted(True/False)'))
if weight: l, r = int(input('lower:')),int(input('upper:'))
tree = eval(input('Tree or no(True/False)'))
for i in range(1,N):
    if i == 1:
        edges.add((1, randint(2, N)))
    else:
        edges.add(tuple(sorted((i, choice([randint(i+1,N)])))))
if not tree:
    M = int(input('E: '))
    while len(edges) < M:
        a, b = randint(1, N), randint(1, N)
        if a == b: continue
        if tuple(sorted((a,b))) in edges: continue
        edges.add(tuple(sorted((a,b))))
    new = []
    for edge in edges:
        if len(new) == M: break
        new.append(edge)
    edges = new[:]
t = [N]
if not tree: t.append(M)
if IO:
    print(*t)
else:
    f.write(' '.join(list(map(str, t)))+'\n')
for a, b in edges:
    out = [a+one-1,b+one-1]
    if r!=0: out.append(randint(l,r))
    if IO: print(*out)
    else: f.write(' '.join(list(map(str, out)))+'\n')
f.close()
