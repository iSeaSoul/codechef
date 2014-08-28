def fast_mod(a, k, m):
    res = 1
    while k > 0:
        if (k & 1) == 1: res = res * a % m
        a = a * a % m
        k >>= 1
    return res

mod = 10 ** 9 + 7
n = input()
for i in xrange(n):
    m = input()
    pow_num = 0
    bit_num = 0
    while m > 0:
        if (m & 1) == 1: 
            pow_num += fast_mod(10, bit_num, mod - 1)
            pow_num %= mod
        m >>= 1
        bit_num += 1
        
    pow_num += mod - 1
    print fast_mod(2, pow_num * 2, mod)
    
