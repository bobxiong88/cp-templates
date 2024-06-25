import sys
input = sys.stdin.readline
def build():
    for i in range(n-1, 0, -1): t[i] = t[i<<1]+t[i<<1|1]
def update(p, value):
    p+=n
    t[p] = value
    while p>1:
        t[p>>1] = t[p] + t[p^1]
        p>>=1
def query(l, r):
    r+=1
    res = 0
    l+=n
    r+=n
    while l<r:
        if l&1:
            res += t[l]
            l+=1
        if r&1:
            r-=1
            res += t[r]
        r>>=1
        l>>=1
    return res
arr = [1, 2, 4, 1, 7, 23, 9, 2, 4]
n = len(arr)
t = [0]*(2*n+2)
for i in range(n):
    t[n+i] = arr[i]
build()
while True:
    a,b = map(int,input().split())
    print(query(a,b))
