//Finds shortest path distance, but not number of shortest paths

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOWNS 700

typedef struct edge {
  int to_town, length;
  struct edge *next;
} edge;

void solve(edge *adj_list[], int num_towns, int store[]) {
  static int done[MAX_TOWNS + 1][2];
  static int min_distances[MAX_TOWNS + 1][2];
  int i, j, state, found;
  int min_distance, min_town_index, min_state_index, old_distance;
  edge *e;

  for (state = 0; state <= 1; state++)
    for (i = 1; i <= num_towns; i++) {
      done[i][state] = 0;
      min_distances[i][state] = -1;
    }
  min_distances[1][0] = 0;

  for (i = 0; i < num_towns * 2; i++) {
    min_distance = -1;
    found = 0;
    for (state = 0; state <= 1; state++)
      for (j = 1; j <= num_towns; j++) {
        if (!done[j][state] && min_distances[j][state] >= 0) {
          if (min_distance == -1 || min_distances[j][state] < min_distance) {
            min_distance = min_distances[j][state];
            min_town_index = j;
            min_state_index = state;
            found = 1;
          }
        }
      }
    if (!found)
      break;
    done[min_town_index][min_state_index] = 1;

    if (min_state_index == 0 && store[min_town_index]) {
      old_distance = min_distances[min_town_index][1];
      if (old_distance == -1 || old_distance > min_distance)
        min_distances[min_town_index][1] = min_distance;
    } else {
      e = adj_list[min_town_index];
      while (e) {
        old_distance = min_distances[e->to_town][min_state_index];
        if (old_distance == -1 || old_distance > min_distance + e->length)
          min_distances[e->to_town][min_state_index] = min_distance +
                                                       e->length;
        e = e->next;
      }
    }
  }
  printf("%d\n", min_distances[num_towns][1]);
}

int main(void) {
  static edge *adj_list[MAX_TOWNS + 1] = {NULL};
  int i, num_towns, from_town, to_town, length;
  int num_stores, store_num;
  static int store[MAX_TOWNS + 1] = {0};
  edge *e;

  scanf("%d", &num_towns);
  for (from_town = 1; from_town <= num_towns; from_town++)
    for (to_town = 1; to_town <= num_towns; to_town++) {
      scanf("%d", &length);
      if (from_town != to_town) {
        e = malloc(sizeof(edge));
        if (e == NULL) {
          fprintf(stderr, "malloc error\n");
          exit(1);
        }
        e->to_town = to_town;
        e->length = length;
        e->next = adj_list[from_town];
        adj_list[from_town] = e;
      }
    }

  scanf("%d", &num_stores);
  for (i = 1; i <= num_stores; i++) {
    scanf("%d", &store_num);
    store[store_num] = 1;
  }
  solve(adj_list, num_towns, store);
  return 0;
}
