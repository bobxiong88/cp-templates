import sys
input = sys.stdin.readline
def prod(a, b, mod):
    mul = [[0 for i in range(T)] for j in range(T)] 
    for i in range(T): 
        for j in range(T): 
            for k in range(T): 
                mul[i][j] += a[i][k] * b[k][j]
                if mul[i][j] < 0: mul[i][j] = mod+mul[i][j]
                else: mul[i][j] %= mod
    for i in range(T): 
        for j in range(T): 
            a[i][j] = mul[i][j]
    return a
def binpow(a, b, mod):
    res = [[1 if i==j else 0 for i in range(T)] for j in range(T)]
    while b > 0 :
        if b&1: res = prod(res, a, mod)
        a = prod(a,a,mod)
        b >>= 1
    return res
def find(n, mod):
    F = [[0 for i in range(T)] for j in range(T)]
    #F[0][0] = 1
    #F[0][-1] = K
    F[0] = a
    for i in range(1, T): F[i][i-1] = 1
    return binpow(F, n, mod)
global T
T, N = map(int,input().split()) # T is period, N is term
a = list(map(int,input().split())) # a[1]*f(x-1)+a[2]*f(x-2)...a[n]*f(x-n)
mod = int(1e9)+7
base = [1]*T # base case
if N <= T: 
    print(1)
    sys.exit(0)
m = find(N-T, mod)
c = 0
row = m[0]
for i in range(T): c += base[i]*row[i]
print(c%mod)
