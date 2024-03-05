/*Not in the book, but here is a dynamic programming solution*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 70

int solve(int n, int t, int p) {
  int m, i, j;
  int dp[SIZE + 1][SIZE + 1];

  dp[0][0] = 1;
  for (i = 1; i <= t; i++)
    dp[0][i] = 0;

  for (i = 1; i <= n; i++)
    for (j = 0; j <= t; j++) {
      dp[i][j] = 0;
      for (m = p; m <= j; m++)
        dp[i][j] += dp[i - 1][j - m];
    }
  return dp[n][t];
}

int main(void) {
  int k, i, n, t, p;
  scanf("%d", &k);
  for (i = 0; i < k; i++) {
    scanf("%d%d%d", &n, &t, &p);
    printf("%d\n", solve(n, t, p));
  }
  return 0;
}
