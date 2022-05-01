import math

k = 600851475143
print max([x for x in range(3, int(math.sqrt(k)) + 1, 2) if k % x == 0 and 
	all([x % i for i in range(3, int(math.sqrt(x)) + 1, 2)])])

