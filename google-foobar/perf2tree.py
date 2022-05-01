def solution(h, q):
  ans = []
  for target in q:
    m = 1
    i = 2**h - 1
    parent = -1
    while True:
      if i == target:
        ans.append(parent)
        break
      parent = i
      if target < (i + m) / 2:  # go left
        i = (i + m) / 2 - 1 
      else:  # go right
        m = (i + m) / 2
        i = i - 1 
        
  return ans

print(solution(3, [1, 4, 7]))

print(solution(4, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]))
