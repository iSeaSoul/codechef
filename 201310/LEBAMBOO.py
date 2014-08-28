test_case = input()
for case in xrange(test_case):
    n = input()
    a = map(int, raw_input().split())
    b = map(int, raw_input().split())
    dif = [b[i] - a[i] for i in xrange(n)]
    
    if n == 1:
        print -1 if b[0] > a[0] else a[0] - b[0]
    elif n == 2:
        print -1 if a[0] + a[1] != b[0] + b[1] else abs(a[0] - b[0])
    else:
        sum_dif = sum(dif)
        if sum_dif % (n - 2) != 0:
            print -1
            continue
        ans = sum_dif / (n - 2)
        has_ans = True
        for dif_item in dif:
            if ans < dif_item or (ans - dif_item) % 2 != 0:
                has_ans = False
                
        print ans if has_ans else -1
