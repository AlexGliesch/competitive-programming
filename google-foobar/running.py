def solution(times, time_limit):
  n = len(times)
  M = times[:]  # all pairs shortest paths

  # compute distances to bulkhead
  for k in xrange(n):
    for i in xrange(n):
      for j in xrange(n):
        if M[i][j] > M[i][k] + M[k][j]:
          M[i][j] = M[i][k] + M[k][j]

  for i in xrange(n):
    if M[i][i] < 0:
      return range(n - 2)  # has negative cost cycle, save all bunnies

  DP = [[-(2 ** 100)] * 2 ** (n - 2) for _ in xrange(n)]
  sol = [[]]

  def recurse(pos, bunnies, time):
    if DP[pos][bunnies] >= time:
      return
    DP[pos][bunnies] = time
    if pos == n - 1:  # at bulkhead; update best solution so far
      s = [i for i in xrange(n - 2) if bunnies & (1 << i)]
      if len(s) > len(sol[0]) or len(s) == len(sol[0]) and s < sol[0]:
        sol[0] = s
    if M[pos][n - 1] <= time:  # if can still go back to bulkhead
      for p2 in xrange(n):
        if p2 != pos:  # move somewhere else
          bunny = (1 << (p2 - 1)) if 0 < p2 < n - 1 else 0
          recurse(p2, bunnies | bunny, time - times[pos][p2])

  recurse(0, 0, time_limit)

  return sol[0]


print solution([[0, 2, 2, 2, -1], [9, 0, 2, 2, -1], [9, 3, 0, 2, -1], [9, 3, 2, 0, -1],
                [9, 3, 2, 2, 0]], 1)
print solution([[0, 1, 1, 1, 1],
                [1, 0, 1, 1, 1],
                [1, 1, 0, 1, 1],
                [1, 1, 1, 0, 1],
                [1, 1, 1, 1, 0]], 3)
