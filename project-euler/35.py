import sympy

print len([x for x in sympy.primerange(0, 1000000) 
	if all(sympy.isprime(int(s[i:] + s[:i])) 
		for s in [str(x)] for i in xrange(len(s)))])