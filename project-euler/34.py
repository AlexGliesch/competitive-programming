import math

print sum([x for x in xrange(3, 1000000) 
	if x == sum([math.factorial(int(y)) for y in str(x)])])