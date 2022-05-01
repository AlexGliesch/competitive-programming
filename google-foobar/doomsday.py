from fractions import Fraction
from fractions import gcd


def solution(m):
  n = len(m)
  T = []  # list of terminals

  # preprocess matrix into floats
  F = [range(n) for i in range(n)]
  for j in xrange(n):
    s = sum(m[j])
    if s > 0:
      for i in xrange(n):
        F[j][i] = float(m[j][i]) / s
    else:
      F[j] = [0.0] * n
      F[j][j] = 1.0
      T.append(j)

  P = [0.0] * n  # probabilities of each state
  Q = [0.0] * n  # temporary
  P[0] = 1.0

  # propagate probabilities
  max_iterations = 10000  # set maximum iterations in case of numerical instability
  for _ in xrange(max_iterations):
    # print(P)
    for i in xrange(n):
      Q[i] = 0.0
      for j in xrange(n):
        Q[i] += P[j] * F[j][i]
    if P == Q:  # reached steady state
      break
    P, Q = Q, P

  # turn into fractions
  P = map(Fraction, P)
  lc = 1
  for i in xrange(n):
    P[i] = P[i].limit_denominator()
    lc = abs(lc * P[i].denominator) / gcd(lc, P[i].denominator)

  # make result vector
  R = [P[t].numerator * lc / P[t].denominator for t in T] + [lc]
  return R


print(solution([[0, 1, 0, 0, 0, 1],
                [4, 0, 0, 3, 2, 0],
                [0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0, 0]]))

print(solution([[0, 2, 1, 0, 0],
                [0, 0, 0, 3, 4],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0]]))
