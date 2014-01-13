for case_num in xrange(input()):
    n = input()
    num = map(int, raw_input().split())
    A, B, C = map(int, raw_input().split())
    op = raw_input()
    
    Acnt = num_front = 0
    num_end = n - 1
    mul_num = 1
    add_num = 0
    
    for xid in xrange(n):
        if op[xid] == 'R':
            Acnt += 1
        elif op[xid] == 'A':
            add_num += A
        elif op[xid] == 'M':
            mul_num *= B
            add_num *= B
        
        add_num %= C
        mul_num %= C
        
        if Acnt % 2 == 0: 
            cur_num = num[num_front]
            num_front += 1
        else:
            cur_num = num[num_end]
            num_end -= 1
        
        cur_num = (cur_num * mul_num + add_num) % C
        
        if xid == n - 1:
            print cur_num
        else:
            print cur_num,
