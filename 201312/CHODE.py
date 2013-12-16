for case_num in xrange(input()):
	freq = raw_input()
	ciph = raw_input()

	num = [i for i in xrange(26)]
	for ch in ciph:
		if 'a' <= ch <= 'z':
			num[ord(ch) - ord('a')] += 100

		elif 'A' <= ch <= 'Z':
			num[ord(ch) - ord('A')] += 100

	num = sorted(num)
	res = ''
    
	for ch in ciph:
		if 'a' <= ch <= 'z':
			for xid in xrange(26):
				if num[xid] % 100 == ord(ch) - ord('a'):
					res += freq[xid]
					break

		elif 'A' <= ch <= 'Z':
			for xid in xrange(26):
				if num[xid] % 100 == ord(ch) - ord('A'):
					res += freq[xid].upper()
					break
		else:
			res += ch 
			
	print res
