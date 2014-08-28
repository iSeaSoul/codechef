def fast_mod(a, k, m):
    res = 1
    while k > 0:
        if (k & 1) == 1: res = res * a % m
        a = a * a % m
        k >>= 1
    return res

mod = 10 ** 9 + 7
for case in xrange(input()):
    print (fast_mod(2, input(), mod) + mod - 1) % mod
