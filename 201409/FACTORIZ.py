import time

CASE_TM = 0.05

class time_node( object ):
    def __init__(self):
        #self.begin_tms = time.time()
        pass
    
    def init(self):
        self.begin_tms = time.time()
    
    def valid(self):
        return time.time() - self.begin_tms <= CASE_TM
    
    def show(self):
        print 'USED TIME = ', time.time() - self.begin_tms
        
tm = time_node()

from math import floor, sqrt

# from wiki: http://rosettacode.org/wiki/Prime_decomposition#Python
def fac_small(n):
    if not tm.valid():
        return [n]
    step = lambda x: 1 + (x<<2) - ((x>>1)<<1)
    maxq = long(floor(sqrt(n)))
    d = 1
    q = n % 2 == 0 and 2 or 3 
    while q <= maxq and n % q != 0:
        if not tm.valid():
            return [n]
        q = step(d)
        d += 1
    return q <= maxq and [q] + fac_small(n//q) or [n]

def print_ans(arr):
    print len(arr)
    for num in arr:
        print num

import random

def get_random(L, R):
	return int(random.random() * (R - L + 1)) + L

def fac_big(X):
    return [X]
  
def fac(X):
    tm.init()
    if X < 10**20: ans = fac_small(X) 
    else: ans = fac_big(X)
    print_ans(ans)
    #tm.show()

for T in xrange(input()):
    fac(input())

#tm.show()
