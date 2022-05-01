import Queue as queue


def solution(entrances, exits, path):
  # Edmonds-Karp maximum flow algorithm

  n = len(path) + 2
  U = 2 ** 30  # upper bound on flow

  # add source and sink nodes and connect to entrances/exits
  source = n - 2
  sink = n - 1
  path = [p + [0, 0] for p in path] + [[0] * n, [0] * n]
  for i in entrances:
    path[source][i] = U
  for i in exits:
    path[i][sink] = U

  g = [[] for _ in xrange(n)]
  s = [0] * 2 * n * n  # edge source
  t = s[:]  # edge target
  cap = s[:]  # edge capacity
  flow = s[:]  # edge flow
  m = 0  # num edges

  for u in xrange(n):  # add edges
    for v in xrange(n):
      if u != v and path[u][v] > 0:
        cap[m] = path[u][v]
        s[m] = t[m + 1] = u
        s[m + 1] = t[m] = v
        g[u].append(m)
        g[v].append(m + 1)
        m += 2

  total_flow = 0  # result

  while True:  # find augmenting path
    pred = [-1] * n
    q = queue.Queue()
    q.put(source)
    while not q.empty():
      v = q.get()
      for e in g[v]:
        u = t[e]
        if pred[u] == -1 and u != source and cap[e] > flow[e]:
          pred[u] = e
          q.put(u)

    if pred[sink] == -1:
      break  # stop: no more flow can reach sink

    # get min flow in augmenting path
    f = U
    e = pred[sink]
    while e != -1:
      f = min(f, cap[e] - flow[e])
      e = pred[s[e]]

    # update flow in edges
    e = pred[sink]
    while e != -1:
      flow[e] += f
      flow[e ^ 1] -= f
      e = pred[s[e]]

    total_flow += f

  return total_flow


print(solution([0], [3], [[0, 7, 0, 0], [0, 0, 6, 0], [0, 0, 0, 8], [9, 0, 0, 0]]))
print(solution([0, 1], [4, 5],
               [[0, 0, 4, 6, 0, 0], [0, 0, 5, 2, 0, 0], [0, 0, 0, 0, 4, 4],
                [0, 0, 0, 0, 6, 6], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]))
