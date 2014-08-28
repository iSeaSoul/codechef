def is_lucky(num):
    while num:
        if num % 10 in [4, 7]:
            return True
        num /= 10
    return False

for xid in xrange(input()):
    num = input()
    
    lucky_cnt = 0
    for div in xrange(1, num):
        if num % div == 0:
            if is_lucky(div): lucky_cnt += 1
            if div * div != num and is_lucky(num / div):
                lucky_cnt += 1
        if div * div >= num:
            break
    
    print lucky_cnt
