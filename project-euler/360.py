from math import *

R = float(10**10)
result = []

for n in xrange(1, int(ceil(sqrt(R)))):
	m = sqrt(R - n**2)
 	if m > 0 and m.is_integer():
 		a = m**2 - n**2
 		b = 2 * m * n
 		result.append((min(a, b), max(a, b)))

print int(sum([a + b for (a, b) in set(result)]))
