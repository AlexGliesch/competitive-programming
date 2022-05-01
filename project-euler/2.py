x = y = 1
r = 0
while x < 4000000:
	r += x if (x % 2 == 0) else 0
	x, y = x + y, x	
print r