x = y = 1
i = 2
while len(str(x)) < 1000:
	x, y, i = x + y, x, i + 1
print i