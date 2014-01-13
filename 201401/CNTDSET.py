mod = 10 ** 9 + 7

def fast_mod(a, p, m):
    res = 1
    while (p > 0):
        if ((p & 1) == 1): res = res * a % m
        a = a * a % m
        p >>= 1
    return res

def fix(x, m):
    return (x % m + m) % m

com = []

com.append([])
for x in xrange(1, 1111):
    com.append([])
    com[x].append(1)
    for y in xrange(1, x):
        com[x].append(fix(com[x - 1][y] + com[x - 1][y - 1], mod))
    com[x].append(1)

def cal(n, p):
    if n == 0: return 1
    
    res = 0
    for T in xrange(p + 1):
        pow = fast_mod(n, T, mod - 1)
        other = fix(fast_mod(n + 1, p - T, mod - 1) - fast_mod(n, p - T, mod - 1), mod - 1)
        num = fix(com[p][T] * fast_mod(2, fix(pow * other, mod - 1), mod), mod)
        if T % 2 == 1:
            num = fix(-num, mod)
        
        res = fix(res + num, mod)
    
    return fix(res * fast_mod(2, fast_mod(n, p, mod - 1), mod), mod)

def solve(n, p):
    return fix(cal(n, p) - cal(n - 1, p), mod)

for case_num in xrange(input()):
    p, n = map(int, raw_input().split())
    print solve(n, p)

