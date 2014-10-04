read = lambda: map(int, raw_input().split())

for Case in xrange(input()):
	R, G, B, M = read()
	R = max(read())
	G = max(read())
	B = max(read())

	max3 = lambda x, y, z: max(max(x, y), z)
	oneMove = lambda x, y, z: (x / 2, y + 1, z + 1)
	ret = max3(R, G, B)

	for tryTm in xrange(M):
		cmax = max3(R, G, B)
		if cmax == R:
			R, G, B = oneMove(R, G, B)
		elif cmax == G:
			R, G, B = oneMove(G, R, B)
		else:
			R, G, B = oneMove(B, R, G)
		ret = min(ret, max3(R, G, B))

	print ret
