def judge(frac):
    max_non_zero_bit_flag = 0
    for i in xrange(45, 0, -1):
        flag = 1 if frac[i] >= 0 else -1
        frac[i - 1] += flag * (abs(frac[i]) / 2)
        frac[i] = flag * (abs(frac[i]) % 2)
        
        if frac[i] != 0:
            max_non_zero_bit_flag = frac[i]
            
    if frac[0] == 0:
        return max_non_zero_bit_flag
    return 1 if frac[0] > 0 else -1
    
case_num = input()
for case_cnt in xrange(case_num):
    k = input()
    
    res = 0
    pow_cnt = [0 for i in xrange(50)]
    
    for k_group in xrange(k):
        raw_a = map(int, raw_input().split())
        n = raw_a[0]
        num = sorted(raw_a[1:])
        
        cur = 0
        off = 1 if (num[0] & 1) == 1 else -1
        id = 0
        while id < n and (num[id] & 1) == (num[0] & 1):
            cur += off
            id += 1
            
        pow_id = 1
        while id < n:
            pow_cnt[pow_id] += 1 if (num[id] & 1) == 1 else -1
            id += 1
            pow_id += 1
        
        res += cur
    
    pow_cnt[0] = res
    res = judge(pow_cnt)
    
    if res == 0:
        print 'DON\'T PLAY'
    else:
        print 'ODD' if res > 0 else 'EVEN'
