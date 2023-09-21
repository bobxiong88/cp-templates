import sys
input = sys.stdin.readline
def build(node, start, end):
    if start==end:
        tree[node] = A[start]
    else:
        mid = (start+end)//2
        build(2*node, start, mid)
        build(2*node+1, mid+1,end)
        tree[node] = tree[2*node] + tree[2*node+1]
def lazyu(node, start, end):
    if lazy[node]!= 0:
        tree[node] += (end - start +1) * lazy[node]
        if start!=end:
            lazy[node*2]+=lazy[node]
            lazy[node*2+1] += lazy[node]
        lazy[node] = 0
def update(node, start, end, l, r, val):
    lazyu(node, start, end)
    if start > end or start >r or end < l :
        return 0
    if start >= l and end <= r:
        tree[node]+=(end-start+1)*val
        if start!=end:
            lazy[node*2]+=val
            lazy[node*2+1]+=val
        return 0
    mid = (start+end)//2
    update(node*2, start, mid, l, r, val)
    update(node*2+1, mid+1, end, l, r, val)
    tree[node] = tree[node*2] + tree[node*2+1]
def query(node, start, end, l, r):
    lazyu(node, start, end)
    if start > end or start > r or end < l:
        return 0
    if start >= l and end <= r:
        return tree[node]
    mid = (start+end)//2
    p1 = query(node*2, start, mid, l, r)
    p2 = query(node*2+1, mid+1, end, l , r)
    return p1+p2
N, Q = map(int,input().split())
A = list(map(int,input().split()))
tree = [0 for i in range(4*(N+1))]
lazy = [0 for i in range(4*(N+1))]
build(1, 0, N-1)
for i in range(Q):
    q = list(map(int,input().split()))
    if q[0] == 1:
        a, b, v = q[1:]
        update(1, 0, N-1, a, b, v)
    else:
        a, b = q[1:]
        print(query(1, 0, N-1, a, b))
