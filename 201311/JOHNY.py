for case in xrange(input()):
    n = input()
    num = map(int, raw_input().split())
    kth = num[input() - 1]
    print sorted(num).index(kth) + 1
    
