import sys
input = sys.stdin.readline
def prod(a, b, mod):
    mul = [[0 for i in range(T+1)] for j in range(T+1)] 
    for i in range(T+1): 
        for j in range(T+1): 
            for k in range(T+1): 
                mul[i][j] += a[i][k] * b[k][j]
                if mul[i][j] < 0: mul[i][j] = mod+mul[i][j]
                else: mul[i][j] %= mod
    for i in range(T+1): 
        for j in range(T+1): 
            a[i][j] = mul[i][j]
    return a
def binpow(a, b, mod):
    res = [[1 if i==j else 0 for i in range(T+1)] for j in range(T+1)]
    while b > 0 :
        if b&1: res = prod(res, a, mod)
        a = prod(a,a,mod)
        b >>= 1
    return res
def find(n, mod):
    F = [[0 for i in range(T+1)] for j in range(T+1)]
    F[0][0] = 1
    F[0][-1] = K
    for i in range(1, T+1): F[i][i-1] = 1
    return binpow(F, n, mod)
global T
global K
N, K, T, C = map(int,input().split())
mod = int(1e9)+7
base = [C for i in range(T)] + [0]
if N <= T:
    print((sum(base[:N-1])*K+C*2)%mod)
    sys.exit(0)
m = find(N-T, mod)
row = m[0]
c = 0
b = 0
for i in range(T+1): c += base[i]*row[i]
for row in m[1:]:
    for i in range(T+1):
        b += base[i]*row[i]
print((c*2+b*K)%mod)

