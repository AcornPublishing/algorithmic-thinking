/*Not in the book, but here is a dynamic programming solution*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200
#define MAX_SCHEMES 20

double min(double v1, double v2) {
  if (v1 < v2)
    return v1;
  else
    return v2;
}

double solve(int num[], double price[], int num_schemes,
             double unit_price, int num_items) {
  int size, i;
  double best, result;
  double dp[SIZE] = {0};
  for (size = 1; size < SIZE; size++) {
    result = dp[size - 1];
    best = result + unit_price;
    for (i = 0; i < num_schemes; i++)
      if (size - num[i] >= 0) {
        result = dp[size - num[i]];
        best = min(best, result + price[i]);
      }
    dp[size] = best;
  }

  best = dp[num_items];
  for (i = num_items + 1; i < SIZE; i++)
    best = min(best, dp[i]);
  return best;
}

int get_number(int *num) {
  int ch;
  int ret = 0;
  ch = getchar();
  while (ch != ' ' && ch != '\n') {
    ret = ret * 10 + ch - '0';
    ch = getchar();
  }
  *num = ret;
  return ch == ' ';
}

int main(void) {
  int test_case, num_schemes, num_items, more, i;
  double unit_price, result;
  int num[MAX_SCHEMES];
  double price[MAX_SCHEMES];

  test_case = 0;
  while (scanf("%lf%d", &unit_price, &num_schemes) != -1) {
    test_case++;
    for (i = 0; i < num_schemes; i++)
      scanf("%d%lf", &num[i], &price[i]);
    scanf(" ");
    printf("Case %d:\n", test_case);
    more = get_number(&num_items);
    while (more) {
      result = solve(num, price, num_schemes, unit_price,
                     num_items);
      printf("Buy %d for $%.2f\n", num_items, result);
      more = get_number(&num_items);
    }
    result = solve(num, price, num_schemes, unit_price,
                   num_items);
    printf("Buy %d for $%.2f\n", num_items, result);
  }
  return 0;
}
