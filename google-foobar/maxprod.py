def solution(xs):
  # if all zeros, output zero
  # if even number of negatives, take product of all non-zeros
  # if odd number of negatives, take product of all non-zeros except the largest negative
  # some edge cases when there's only one non-zero negative element
  num_neg = 0
  big_neg = 0
  prod = 1
  num_nonzeros = 0
  for x in xs:    
    if x != 0:
      prod = prod * x
      num_nonzeros += 1    
    if x < 0:
      num_neg += 1
      if big_neg == 0 or x > big_neg:
        big_neg = x
  
  if num_nonzeros == 0 or num_nonzeros == 1 and num_neg > 0 and len(xs) > num_nonzeros:
    prod = 0
  elif num_neg % 2 == 1 and len(xs) > 1:
    prod = prod / big_neg

  return str(prod)

assert solution([-2, -3, 4, -5]) == "60"
assert solution([2, 0, 2, 2, 0]) == "8"
assert solution([0]) == "0"
assert solution([-2]) == "-2"
assert solution([2]) == "2"
assert solution([2, 0]) == "2"
assert solution([-2, -2]) == "4"
assert solution([-2, -2, -2]) == "4"
assert solution([0, 0, 0]) == "0"
assert solution([-2, 0]) == "0"
assert solution([-2, -2, 0]) == "4"
assert solution([-2, 2, 0]) == "2"
assert solution([-2, 2]) == "2"
assert solution([-2, 2, 1]) == "2"
print(solution([-1248, 4897, -2187, 41278, 123, 1, 0, -2, 23, 214, 42, -412]))
assert solution([1248, -1, -2187]) == str(2187*1248)
assert solution([-1, -1, 0]) == "1"
assert solution([-1, 1]) == "1"
assert solution([-1]) == "-1"
assert solution([-1, -1, 1]) == "1"
assert solution([-1, -1, 1, 0]) == "1"
assert solution([-1, 0]) == "0"

assert solution([-2, 1, -3, 4, -5]) == "60"
assert solution([2, 0, 1, 2, 2, 0]) == "8"
assert solution([0, 1]) == "1"
assert solution([-2, 1, 1]) == "1"
assert solution([-2, 1, -1]) == "2"
assert solution([2, 1]) == "2"
assert solution([2, 0, 1]) == "2"
assert solution([-2, -2, 1]) == "4"
assert solution([-2, -2, -2, 1]) == "4"
assert solution([0, 0, 0, 1]) == "1"
assert solution([-2, 0, 1]) == "1"
assert solution([-2, -2, 0, 1]) == "4"
assert solution([-2, 2, 0, 1]) == "2"
assert solution([-2, 2, 1]) == "2"
assert solution([-2, 2, 1]) == "2"
assert solution([-1, -1, 1, 1, 1, -1]) == "1"
assert solution([-1]) == "-1"
assert solution([-1, 0]) == "0"
assert solution([-1, -1]) == "1"
assert solution([-1, -1, 0]) == "1"
assert solution([-1, -1, 0, 500]) == "500"
