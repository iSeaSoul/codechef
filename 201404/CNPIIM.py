import math, json

mul_mem = {}

def get_pnum(mul):
	if mul_mem.has_key(mul):
		return mul_mem[mul]
	ans = 0
	lim = int(math.sqrt(mul))
	for f1 in xrange(1, lim + 1):
		f2 = mul / f1
		ans += f2 * 2
	ans -= lim * lim
	mul_mem[mul] = ans
	return ans

def solve(x):
	ans = 0
	for c in xrange(1, x):
		ans += get_pnum(c * (x - c) - 1)
	return ans

fp = open('ans.txt', 'w')

ans = []
for n in xrange(3, 2502):
	ans.append(solve(n))
	print 'solve', n

fp.write(json.dumps(ans))

