def solve(L, D, S, C):
    while D >= 2:
        S *= (C + 1)
        if S >= L: 
            return True
        D -= 1
        
    return S >= L

for case_num in xrange(input()):
    L, D, S, C = map(int, raw_input().split())
    print 'ALIVE AND KICKING' if solve(L, D, S, C) else 'DEAD AND ROTTING'
