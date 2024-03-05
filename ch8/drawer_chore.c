#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DRAWERS 300000

int find(int drawer, int parent[]) {
  int set = drawer, temp;
  while (parent[set] !=  set)
    set = parent[set];
  while (parent[drawer] != set) {
    temp = parent[drawer];
    parent[drawer] = set;
    drawer = temp;
  }
  return set;
}

void union_sets(int drawer1, int drawer2, int parent[]) {
  int set1, set2;
  set1 = find(drawer1, parent);
  set2 = find(drawer2, parent);
  parent[set1] = set2;
  if (set1 == set2)
    parent[set2] = 0;
  printf("LADICA\n");
}

int main(void) {
  static int parent[MAX_DRAWERS + 1];
  int num_items, num_drawers, i;
  int drawer_a, drawer_b;
  scanf("%d%d", &num_items, &num_drawers);
  parent[0] = 0;
  for (i = 1; i <= num_drawers; i++)
    parent[i] = i;

  for (i = 1; i <= num_items; i++) {
    scanf("%d%d", &drawer_a, &drawer_b);

    if (find(drawer_a, parent) == drawer_a)
      union_sets(drawer_a, drawer_b, parent);

    else if (find(drawer_b, parent) == drawer_b)
      union_sets(drawer_b, drawer_a, parent);

    else if (find(drawer_a, parent) > 0)
      union_sets(drawer_a, drawer_b, parent);

    else if (find(drawer_b, parent) > 0)
      union_sets(drawer_b, drawer_a, parent);

    else
      printf("SMECE\n");
  }
  return 0;
}

