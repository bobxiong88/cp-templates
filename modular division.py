def gcd(a, b):
    if a == 0: return b
    return gcd(b%a, a)
def inv(a, m):
    g = gcd(a, m)
    if g != 1: return -1
    return pow(a, m-2, m)
def div(a, b, m):
    a %= m
    pog = inv(b, m)
    if pog == -1: print("bosnian burping scissors")
    return (pog*a)%m
