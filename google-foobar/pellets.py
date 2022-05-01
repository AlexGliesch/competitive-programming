def solution(n):
  # looking at bit representation of the number
  # always shave off trailing zeros (divide by 2)
  # choose to increment/decrement so as to generate fewer ones 
  # 3 is an edge case
  i = int(n)
  steps = 0
  while True:
    if i == 1:
      return steps
    if not (i & 1):
      i = i / 2
    elif i & 2 and i != 3:
      i = i + 1
    else:
      i = i - 1
    steps = steps + 1
    

assert solution('15') == 5
print(solution('13'))
assert solution('13') == 5
assert solution('4') == 2
print(solution('23894732897532897583476258347659832476598324765893476598364598346583274658324675938475639847548734444444444444444444444444444444444444444444444444433333338944395832759834675893746589374658923746598273465983476598367459837466666666666666666666666666666666666622222222222222222222273738988888888886349875623'))
assert solution(str(2**300)) == 300
assert solution(str(2**300+1)) == 301
assert solution(str(2**300-1)) == 301
print(solution(str(2**300-2))) 
