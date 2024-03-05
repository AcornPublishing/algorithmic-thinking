#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CELLS 100

typedef struct edge {
  int to_cell, length;
  struct edge *next;
} edge;

typedef struct heap_element {
  int cell;
  int time;
} heap_element;

void min_heap_insert(heap_element heap[], int *num_heap,
                     int receipt_index, int cost) {
  int i;
  heap_element temp;
  (*num_heap)++;
  heap[*num_heap] = (heap_element){receipt_index, cost};
  i = *num_heap;
  while (i > 1 && heap[i].time < heap[i / 2].time) {
    temp = heap[i];
    heap[i] = heap[i / 2];
    heap[i / 2] = temp;
    i = i / 2;
  }
}

heap_element min_heap_extract(heap_element heap[], int *num_heap) {
  heap_element remove, temp;
  int i, child;
  remove = heap[1];
  heap[1] = heap[*num_heap];
  (*num_heap)--;
  i = 1;
  while (i * 2 <= *num_heap) {
    child = i * 2;
    if (child < *num_heap && heap[child + 1].time < heap[child].time)
      child++;
    if (heap[child].time < heap[i].time) {
      temp = heap[i];
      heap[i] = heap[child];
      heap[child] = temp;
      i = child;
    } else
      break;
  }
  return remove;
}

int find_time(edge *adj_list[], int num_cells,
              int from_cell, int exit_cell) {
  static int done[MAX_CELLS + 1];
  static int min_times[MAX_CELLS + 1];
  static heap_element min_heap[MAX_CELLS * MAX_CELLS + 1];
  int i;
  int min_time, min_time_index, old_time;
  edge *e;
  int num_min_heap = 0;
  for (i = 1; i <= num_cells; i++) {
    done[i] = 0;
    min_times[i] = -1;
  }
  min_times[from_cell] = 0;
  min_heap_insert(min_heap, &num_min_heap, from_cell, 0);

  while (num_min_heap > 0) {
    min_time_index = min_heap_extract(min_heap, &num_min_heap).cell;
    if (done[min_time_index])
      continue;
    min_time = min_times[min_time_index];
    done[min_time_index] = 1;

    e = adj_list[min_time_index];
    while (e) {
      old_time = min_times[e->to_cell];
      if (old_time == -1 || old_time> min_time + e->length) {
        min_times[e->to_cell] = min_time + e->length;
        min_heap_insert(min_heap, &num_min_heap,
                e->to_cell, min_time + e->length);
      }
      e = e->next;
    }
  }
  return min_times[exit_cell];
}

int main(void) {
  static edge *adj_list[MAX_CELLS + 1];
  int num_cases, case_num, i;
  int num_cells, exit_cell, time_limit, num_edges;
  int from_cell, to_cell, length;
  int total, min_time;
  edge *e;

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
      e->to_cell = to_cell;
      e->length = length;
      e->next = adj_list[from_cell];
      adj_list[from_cell] = e;
    }

    total = 0;
    for (i = 1; i <= num_cells; i++) {
      min_time = find_time(adj_list, num_cells, i, exit_cell);
      if (min_time >= 0 && min_time <= time_limit)
        total++;
    }
    printf("%d\n", total);
    if (case_num < num_cases)
      printf("\n");
  }
  return 0;
}
