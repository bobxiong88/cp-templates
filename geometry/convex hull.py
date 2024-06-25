import sys
input = sys.stdin.readline
def convex(points):
    def pd(o, a, b):
        return (a[0]-o[0])*(b[1]-o[1])-(a[1]-o[1])*(b[0]-o[0])
    N = int(input())
    cock = [tuple(map(int,input().split())) for i in range(N)]
    cock = sorted(list(set(cock)))
    lower = []
    for p in cock:
        while len(lower) >= 2 and pd(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)
    upper = []
    for p in reversed(cock):
        while len(upper) >= 2 and pd(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)
    return lower[:-1]+upper[-1:]

#thanks wikipedia
