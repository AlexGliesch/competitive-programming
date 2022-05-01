import random

t = 1000
print str(t)
for T in xrange(t):
    n = random.randint(30, 50)
    edges = [(i + 1, j + 1) for i in xrange(n) for j in xrange(n) if i != j]
    random.shuffle(edges)
    m = min(len(edges), random.randint(100, 150))
    k = random.randint(3, 10)
    print str(n) + ' ' + str(m) + ' ' + str(k)
    for j in xrange(m):
        print str(edges[j][0]) + ' ' + str(edges[j][1])
    print ''
