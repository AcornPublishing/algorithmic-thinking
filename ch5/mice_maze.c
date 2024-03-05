#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CELLS 100

typedef struct edge {
  int to_cell, length;
  struct edge *next;
} edge;

void find_times(edge *adj_list[], int num_cells,
               int from_cell, int min_times[]) {
  static int done[MAX_CELLS + 1];
  int i, j, found;
  int min_time, min_time_index, old_time;
  edge *e;
  for (i = 1; i <= num_cells; i++) {
    done[i] = 0;
    min_times[i] = -1;
  }
  min_times[from_cell] = 0;

  for (i = 0; i < num_cells; i++) {
    min_time = -1;
    found = 0;
    for (j = 1; j <= num_cells; j++) {
      if (!done[j] && min_times[j] >= 0) {
        if (min_time == -1 || min_times[j] < min_time) {
          min_time = min_times[j];
          min_time_index = j;
          found = 1;
        }
      }
    }
    if (!found)
      break;
    done[min_time_index] = 1;

    e = adj_list[min_time_index];
    while (e) {
      old_time = min_times[e->to_cell];
      if (old_time == -1 || old_time > min_time + e->length)
        min_times[e->to_cell] = min_time + e->length;
      e = e->next;
    }
  }
}

int main(void) {
  static edge *adj_list[MAX_CELLS + 1];
  int num_cases, case_num, i;
  int num_cells, exit_cell, time_limit, num_edges;
  int from_cell, to_cell, length;
  int total, min_time;
  edge *e;
  static int min_times[MAX_CELLS + 1];

  scanf("%d", &num_cases);
  for (case_num = 1; case_num <= num_cases; case_num++) {
    scanf("%d%d%d", &num_cells, &exit_cell, &time_limit);
    scanf("%d", &num_edges);
    for (i = 1; i <= num_cells; i++)
      adj_list[i] = NULL;
    for (i = 0; i < num_edges; i++) {
      scanf("%d%d%d", &from_cell, &to_cell, &length);
      e = malloc(sizeof(edge));
      if (e == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
      }
      e->to_cell = from_cell;
      e->length = length;
      e->next = adj_list[to_cell];
      adj_list[to_cell] = e;
    }

    find_times(adj_list, num_cells, exit_cell, min_times);
    total = 0;
    for (i = 1; i <= num_cells; i++) {
      min_time = min_times[i];
      if (min_time >= 0 && min_time <= time_limit)
        total++;
    }
    printf("%d\n", total);
    if (case_num < num_cases)
      printf("\n");
  }
  return 0;
}
