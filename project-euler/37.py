import sympy

print sum([p for p in sympy.primerange(11, 1000000) 
	if all((sympy.isprime(int(s[i:])) and sympy.isprime(int(s[:i]))
		for s in [str(p)] for i in xrange(1, len(s))))])