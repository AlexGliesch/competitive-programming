import itertools

print max([a * b for (a, b) in itertools.combinations(range(1000), 2) 
	if str(a * b) == str(a * b)[::-1]])