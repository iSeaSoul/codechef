def solve2(arr):
    idx = 0
    len_arr = len(arr)
    while idx < len_arr and arr[idx] < 5:
        idx += 1
    return len_arr - idx

def count(arr, count_num):
    num_cnt = 0
    for num in arr:
        if num == count_num:
            num_cnt += 1
    return num_cnt

case_num = input()
for case in xrange(case_num):
    n = input()
    a = sorted(map(int, raw_input().split()))
    b = sorted(map(int, raw_input().split()))

    ans = 0.0
    ans_2 = solve2(b)
    ans_3_part = count(b, 2)
    ans_all_part = count(b, 1)

    idx_b = 0
    len_b = len(b)
    for num in a:
        if num == 2: ans += ans_2
        elif num == 3: ans += ans_3_part
        
        if num >= 2:
            ans += ans_all_part
            
        if num >= 3:
            while idx_b < len_b and b[idx_b] <= num:
                idx_b += 1
            ans += len_b - idx_b

    print ans / n
