n = int(input())
print(n, (n*(n-1))//2)
for i in range(1, n+1):
    for j in range(i+1, n+1):
        print(i,j)
