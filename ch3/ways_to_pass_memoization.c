#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 70

int solve(int n, int t, int p, int memo[SIZE + 1][SIZE + 1]) {
  int total, m;
  if (memo[n][t] != -1)
    return memo[n][t];
  if (n == 0 && t == 0)
    return 1;
  if (n == 0)
    return 0;
  total = 0;
  for (m = p; m <= t; m++)
    total = total + solve(n - 1, t - m, p, memo);
  memo[n][t] = total;
  return memo[n][t];
}

int main(void) {
  int k, i, x, y, n, t, p;
  int memo[SIZE + 1][SIZE + 1];
  scanf("%d", &k);
  for (i = 0; i < k; i++) {
    scanf("%d%d%d", &n, &t, &p);
    for (x = 0; x <= SIZE; x++)
      for (y = 0; y <= SIZE; y++)
        memo[x][y] = -1;
    printf("%d\n", solve(n, t, p, memo));
  }
  return 0;
}
