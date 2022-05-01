from sympy import *
from itertools import *

# Unsolved: time out

def cntprimes(a, b):
	return len(list(takewhile(lambda n: isprime(n * n + a * n + b), count(0))))

print max([(cntprimes(a, b), a * b) 
	for a in xrange(-1000, 1000) for b in xrange(-1000, 1000)])
		