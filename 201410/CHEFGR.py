read = lambda: map(int, raw_input().split())

for Case in xrange(input()):
	n, k = read()
	a = read()
	left = k + sum(a) - max(a) * n
	print 'Yes' if left >= 0 and left % n == 0 else 'No'