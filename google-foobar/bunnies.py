import Queue as queue


def solution(map):
  h = len(map)
  w = len(map[0])
  dr, dc = [-1, 1, 0, 0], [0, 0, -1, 1]  # helpers to move over positions

  # bfs with state (col, row, knocked-down-wall?)
  q = queue.Queue()
  v = dict()
  p = (0, 0, 0)  # initial position
  q.put(p)
  v[p] = 1
  while not q.empty():
    p = q.get()
    dist = v[p]
    if p[0] == h - 1 and p[1] == w - 1:
      # print(dist)
      return dist
    for i in xrange(4):  # up down left right
      tc = p[0] + dc[i]
      tr = p[1] + dr[i]
      if not 0 <= tc <= h - 1 or not 0 <= tr <= w - 1:  # out of bounds
        continue
      if map[tc][tr] == 1 and p[2] == 0 and (tc, tr, 1) not in v:  # knock down wall?
        q.put((tc, tr, 1))
        v[(tc, tr, 1)] = dist + 1
      if map[tc][tr] == 0 and (tc, tr, p[2]) not in v:  # just move
        q.put((tc, tr, p[2]))
        v[(tc, tr, p[2])] = dist + 1


assert solution([[0, 1, 1, 0], [0, 0, 0, 1], [1, 1, 0, 0], [1, 1, 1, 0]]) == 7

assert solution([[0, 0, 0, 0, 0, 0], [1, 1, 1, 1, 1, 0], [0, 0, 0, 0, 0, 0], [
  0, 1, 1, 1, 1, 1], [0, 1, 1, 1, 1, 1], [0, 0, 0, 0, 0, 0]]) == 11
