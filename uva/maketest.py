from random import *

def make_cases(ncases, nfrom, nto, xfrom, xto):
  for i in xrange(ncases):
    n = randint(nfrom, nto)
    l = [(randint(xfrom, xto), randint(xfrom, xto)) for j in xrange(n)]
    l = list(set(l))
    print len(l)
    for (x, y) in l:
      print str(x) + ' ' + str(y)  

print 20*5 + 10*3 + 20*2 + 20 + 1

# hard cases
make_cases(1, 10**5-1, 10**5, 0, 10**9)
make_cases(20, 10**4, 10**5, 0, 10**9)

# many easy, corner (?) cases
make_cases(20, 2, 4, 0, 5)
make_cases(20, 2, 6, 0, 10)
make_cases(20, 2, 10, 0, 10)
make_cases(20, 2, 10, 0, 10**4)
make_cases(20, 10, 20, 0, 10**4)
make_cases(10, 10**2, 10**3, 0, 10**4)

# medium cases
make_cases(10, 10**2, 10**4, 0, 10**3)
make_cases(10, 10**2, 10**4, 0, 10**9)
make_cases(20, 10, 10**4, 0, 100)
make_cases(20, 10, 10**4, 0, 10**4)