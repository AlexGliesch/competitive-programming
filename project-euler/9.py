from itertools import *
from math import *

print [int(a * b * c) for a, b in combinations(xrange(1000), 2) 
	for c in [sqrt(a**2 + b**2)] if a + b + c == 1000 and a < b < c]