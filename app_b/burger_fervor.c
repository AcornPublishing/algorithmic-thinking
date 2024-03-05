#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

void reconstruct(int m, int n, int dp[], int minutes) {
  int first, second;
  while (minutes > 0) {
    first = -1;
    second = -1;
    if (minutes >= m)
      first = dp[minutes - m];
    if (minutes >= n)
      second = dp[minutes - n];
    if (first >= second) {
      printf("Eat a %d-minute burger\n", m);
      minutes = minutes - m;
    } else {
      printf("Eat a %d-minute burger\n", n);
      minutes = minutes - n;
    }
  }
}

void solve(int m, int n, int t) {
  int result, i, first, second;
  int dp[SIZE];
  dp[0] = 0;
  for (i = 1; i <= t; i++) {
    if (i >= m)
        first = dp[i - m];
    else
      first = -1;
    if (i >= n)
      second = dp[i - n];
    else
      second = -1;
    if (first == -1 && second == -1)
      dp[i] = -1;
    else
      dp[i] = max(first, second) + 1;
  }

  result = dp[t];
  if (result >= 0) {
    printf("%d\n", result);
    reconstruct(m, n, dp, t);
  }
  else {
    i = t - 1;
    result = dp[i];
    while (result == -1) {
      i--;
      result = dp[i];
    }
    printf("%d %d\n", result, t - i);
    reconstruct(m, n, dp, i);
  }
}

int main(void) {
  int m, n, t;
  while (scanf("%d%d%d", &m, &n, &t) != -1)
    solve(m, n, t);
  return 0;
}
