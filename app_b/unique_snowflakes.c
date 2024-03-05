#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100000

int code(int snowflake[]) {
  return (snowflake[0] + snowflake[1] + snowflake[2]
          + snowflake[3] + snowflake[4] + snowflake[5]) % SIZE;
}

int identical_right(int snow1[], int snow2[],
                    int start) {
  int offset, snow2_index;
  for (offset =0; offset < 6; offset++) {
    snow2_index = start + offset;
    if (snow2_index >= 6)
      snow2_index = snow2_index - 6;
        if (snow1[offset] != snow2[snow2_index])
      return 0;
  }
  return 1;
}

int identical_left(int snow1[], int snow2[], int start) {
  int offset, snow2_index;
  for (offset =0; offset < 6; offset++) {
    snow2_index = start - offset;
    if (snow2_index < 0)
      snow2_index = snow2_index + 6;
    if (snow1[offset] != snow2[snow2_index])
      return 0;
  }
  return 1;
}

int are_identical(int snow1[], int snow2[]) {
  int start;
  for (start = 0; start < 6; start++) {
    if (identical_right(snow1, snow2, start))
      return 1;
    if (identical_left(snow1, snow2, start))
      return 1;
  }
  return 0;
}

void identify_identical(int snowflakes[][6], int heads[],
                        int nodes[]) {
  int i, node1, node2;
  for (i = 0; i < SIZE; i++) {
    node1 = heads[i];
    while (node1 != -1) {
      node2 = nodes[node1];
      while (node2 != -1) {
        if (are_identical(snowflakes[node1], snowflakes[node2])) {
          printf("Twin snowflakes found.\n");
          return;
        }
        node2 = nodes[node2];
      }
      node1 = nodes[node1];
    }
  }
  printf("No two snowflakes are alike.\n");
}

int main(void) {
  static int snowflakes[SIZE][6];
  static int heads[SIZE];
  static int nodes[SIZE];
  int n;
  int i, j, snowflake_code;
  for (i = 0; i < SIZE; i++) {
    heads[i] = -1;
    nodes[i] = -1;
  }
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    for (j = 0; j < 6; j++)
      scanf("%d", &snowflakes[i][j]);
    snowflake_code = code(snowflakes[i]);
    nodes[i] = heads[snowflake_code];
    heads[snowflake_code] = i;
  }
  identify_identical(snowflakes, heads, nodes);
  return 0;
}
