import sys
input = sys.stdin.readline
S = input().strip('\n')
N = len(S)
lps = [0]*N
i = 0
j = 1
while j < N:
    if S[i] == S[j]:
        lps[j] = i+1
        j += 1
        i += 1
    else:
        if i == 0:
            j += 1
        else:
            i = lps[i-1]
