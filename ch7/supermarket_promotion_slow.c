//Too slow (uses linear search)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECEIPTS 1000000
#define MAX_COST 1000000

typedef struct receipt {
  int cost;
  int used;
} receipt;

int extract_max(receipt receipts[], int num_receipts) {
  int max, max_index, i;
  max = -1;
  for (i = 0; i < num_receipts; i++)
    if (!receipts[i].used && receipts[i].cost > max) {
      max_index = i;
      max = receipts[i].cost;
    }
  receipts[max_index].used = 1;
  return max;
}

int extract_min(receipt receipts[], int num_receipts) {
  int min, min_index, i;
  min = MAX_COST + 1;
  for (i = 0; i < num_receipts; i++)
    if (!receipts[i].used && receipts[i].cost < min) {
      min_index = i;
      min = receipts[i].cost;
    }
  receipts[min_index].used = 1;
  return min;
}

int main(void) {
  static struct receipt receipts[MAX_RECEIPTS];
  int num_days, num_receipts_today;
  int num_receipts = 0;
  long long total_prizes = 0;
  int i, j, max, min;
  scanf("%d", &num_days);

  for (i = 0; i < num_days; i++) {
    scanf("%d", &num_receipts_today);
    for (j = 0; j < num_receipts_today; j++) {
      scanf("%d", &receipts[num_receipts].cost);
      receipts[num_receipts].used = 0;
      num_receipts++;
    }
    max = extract_max(receipts, num_receipts);
    min = extract_min(receipts, num_receipts);
    total_prizes += max - min;
  }
  printf("%lld\n", total_prizes);
  return 0;
}
