from itertools import *

def numfactors(x):
	return 1 + len([i for i in xrange(1, (x / 2) + 1) if x % i == 0])

xs = takewhile(lambda x: numfactors(sum(xrange(x))) <= 500, count(0))
print sum(xrange(len(list(xs))))