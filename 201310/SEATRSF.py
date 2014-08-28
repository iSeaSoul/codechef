MOD = 10**9 + 7

def fast_mod(a, p, m):
    res = 1
    while p > 0:
        if (p & 1) == 1: res = res * a % m
        a = a * a % m
        p >>= 1
        
    return res

case_num = input()
for case in xrange(case_num):
    n, m, dif, tms = map(int, raw_input().split())
    res = (fast_mod(dif + 1, n, MOD) + fast_mod(dif - 1, n, MOD)) % MOD
    res = (res - 2 * fast_mod(dif, n, MOD)) % MOD
    res = res * (m - dif) % MOD
    res = (res + MOD) % MOD
    
    print 0 if m - 1 < dif or n < 2 else res
