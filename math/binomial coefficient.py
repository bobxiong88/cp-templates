import sys
input = sys.stdin.readline
def gcd(a, b):
    if a == 0: return b
    return gcd(b%a, a)
def inv(a):
    g = gcd(a, m)
    if g != 1: return -1
    return pow(a, m-2, m)
def div(a, b):
    a %= m
    pog = inv(b)
    if pog == -1: print("bosnian burping scissors")
    return (pog*a)%m
def cr(N, K):
    return div(tb[N],tb[K]*tb[N-K])
m = int(1e4)+7
mx = 53
tb = [1]*mx
for i in range(1,mx):
    tb[i] = (tb[i-1]*i)%m
