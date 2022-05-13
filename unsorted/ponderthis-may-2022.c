#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 152

/*
 * We have the brute-force recurrence
 * dfs(i, sum):
 *    if i > n:
 *      --> [sum % n = 0]
 *    else
 *      --> dfs(i+1, sum + A[2i]) OR dfs(i+1, sum + A[2i-1])
 *
 *  Since the final number must be divisible by n we can take the modulo of sum
 *  before each call. This means there are only n^2 possible inputs, and so
 *  results can be cached in a dynamic programming table.
 * 
 *  Complexity: O(n^2).
 **/

int dp[NMAX][NMAX], A[NMAX * 2], n;

int dfs(int i, int sum) {
  if (i >= n) return sum == 0;
  if (dp[i][sum]) return 0;
  dp[i][sum] = 1;
  if (dfs(i + 1, (sum + A[2 * i]) % n)) {
    if (i != n - 1) printf(",");
    printf("%d", A[2 * i]);
    return 1;
  }
  if (dfs(i + 1, (sum + A[2 * i + 1]) % n)) {
    if (i != n - 1) printf(",");
    printf("%d", A[2 * i + 1]);
    return 1;
  }
  return 0;
}

int main(int argc, char** argv) {
  n = (argc - 1) / 2;
  for (int i = 1; i <= 2 * n; ++i)
    A[i - 1] = atoi(argv[i]);

  memset(dp, 0, sizeof(dp));
  dfs(0, 0);
  printf("\n");
}
