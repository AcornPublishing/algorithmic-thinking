#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROCKS 50000

int can_make_min_distance(int distance, int rocks[], int num_rocks,
                          int num_remove, int length) {
  int i;
  int removed = 0, prev_rock_location = 0, cur_rock_location;
  if (length < distance)
    return 0;
  for (i = 0; i < num_rocks; i++) {
    cur_rock_location = rocks[i];
    if (cur_rock_location - prev_rock_location < distance)
      removed++;
    else
      prev_rock_location = cur_rock_location;
  }
  if (length - prev_rock_location < distance)
    removed++;
  return removed <= num_remove;
}

void solve(int rocks[], int num_rocks,
           int num_remove, int length) {
  int low, high, mid;
  low = 0;
  high = length + 1;
  while (high - low > 1) {
    mid = (low + high) / 2;
    if (can_make_min_distance(mid, rocks, num_rocks, num_remove, length))
      low = mid;
    else
      high = mid;
  }
  printf("%d\n", low);
}

int compare(const void *v1, const void *v2) {
  int num1 = *(const int *)v1;
  int num2 = *(const int *)v2;
  return num1 - num2;
}

int main(void) {
  static int rocks[MAX_ROCKS];
  int length, num_rocks, num_remove, i;
  scanf("%d%d%d", &length, &num_rocks, &num_remove);
  for (i = 0; i < num_rocks; i++)
    scanf("%d", &rocks[i]);
  qsort(rocks, num_rocks, sizeof(int), compare);
  solve(rocks, num_rocks, num_remove, length);
  return 0;
}
