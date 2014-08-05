read = lambda: map(int, raw_input().split())

for T in xrange(input()):
	n, k = read()
	esum = n - sum([x & 1 for x in read()])

	if k == 0:
		print 'YES' if esum != n else 'NO'
	else:
		print 'YES' if esum >= k else 'NO'
