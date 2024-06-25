import sys
sys.setrecursionlimit(3000000)
input = sys.stdin.readline
def fast(a, b, m):
    if b==0:
        return 1
    res = fast(a, b//2, m)
    if b%2:
        return (res*res*a)%m
    else:
        return (res*res)%m
a,b = map(int,input().split())
m = int(1e9)+7
import time
start = time.time()
fast(a,b,m)
print(time.time()-start)
start = time.time()
pow(a,b,m)
print(time.time()-start)
