parent, size = []*2
def find(v):
    if parent[v] == v: return v
    parent[v] = find(parent[v])
    return parent[v]
def union(a,b):
    a, b = find(a), find(b)
    if a==b: continue
    if size[a] < size[b]: a, b = b, a
    size[a]+=size[b]
    parent[b] = parent[a]
def build(n):
    parent = [i for i in range(n+1)]
    size = [1 for i in range(n+1)]
