def build(node, tl, tr):
    if tl == tr:
        t[node] = a[tl]
    else:
        m = (tl+tr)//2
        build(node*2, tl, m)
        build(node*2+1, m+1, tr)
        t[node] = t[node*2]+t[node*2+1]
def query(node, tl, tr, l, r):
    if l > r:
        return 0
    if l == tl and r == tr:
        return t[node]
    m = (tl+tr)//2
    return query(node*2, tl, m, l, min(r, m))+\
    query(node*2+1, m+1, tr, max(l, m+1), r)
def update(node, tl, tr, pos, v):
    if tl == tr:
        t[node] = v
    else:
        m = (tl+tr)//2
        if pos <= m:
            update(node*2, tl, m, pos, v)
        else:
            update(node*2+1, m+1, tr, pos, v)
        t[node] = t[node*2]+t[node*2+1]
a = [2, 5, 1, 2, 7, 8, 2, 3]
N = len(a)
t = [0]*(2*N)
build(1, 0, N-1)
# >>> query(1, 0, N-1, 0, 2)
# <<< 8
# >>> query(1, 0, N-1, 3, 4)
# <<< 9
# >>> update(1, 0, N-1, 1, 3)
# >>> query(1, 0, N-1, 0, 2)
# <<< 6



