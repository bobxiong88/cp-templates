import sys
input = sys.stdin.readline
def prod(a, b, mod): 
    mul = [[0 for i in range(3)] for j in range(3)] 
    for i in range(3): 
        for j in range(3): 
            for k in range(3): 
                mul[i][j] += a[i][k] * b[k][j]
                if mul[i][j] < 0:
                    mul[i][j] = mod+mul[i][j]
                else:
                    mul[i][j] %= mod
    for i in range(3): 
        for j in range(3): 
            a[i][j] = mul[i][j]
    return a
def fast(a, b, mod):
    if b==0:
        return [[1,0,0],[0,1,0],[0,0,1]]
    res = fast(a, b//2, mod)
    if b%2:
        return prod(prod(res,res,mod),a,mod)
    else:
        return prod(res,res,mod)
def find(n, mod):
    F = [[2, 0, -1], [1, 0, 0], [0, 1, 0]] # a b c
    return fast(F, n, mod)
n = int(input())
mod = int(1e9)+7
base = [2,1,0] # base case
m = find(n, mod)
curr = []
ans = 0
row = m[2]
for i in range(3): ans += base[i]*row[i]
if ans<0:
    ans = mod+ans
else:
    ans = ans%mod
print(ans)
