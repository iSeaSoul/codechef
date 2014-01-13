def solve(strr):
    lenc = len(strr)
    for xid in xrange(lenc - 2):
        if strr[xid:xid+3] == '010' or strr[xid:xid+3] == '101':
            return True
    return False

for case_num in xrange(input()):
    print 'Good' if solve(raw_input()) else 'Bad'
