def is_prime(x):
    for c in xrange(2, x):
        if c * c > x: break
        if x % c == 0: return False
    return True
 
for Case in xrange(input()):
    x, y = map(int, raw_input().split())
    ans = 1
    while not is_prime(x + y + ans):
        ans += 1
    print ans

