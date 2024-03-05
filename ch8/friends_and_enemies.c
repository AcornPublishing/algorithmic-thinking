#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 9999

int find(int person, int parent[]) {
  int set = person, temp;
  while (parent[set] !=  set)
    set = parent[set];
  while (parent[person] != set) {
    temp = parent[person];
    parent[person] = set;
    person = temp;
  }
  return set;
}

int union_sets(int person1, int person2, int parent[],
               int size[]) {
  int set1, set2, temp;
  set1 = find(person1, parent);
  set2 = find(person2, parent);
  if (set1 != set2) {
    if (size[set1] > size[set2]) {
      temp = set1;
      set1 = set2;
      set2 = temp;
    }
    parent[set1] = set2;
    size[set2] = size[set2] + size[set1];
  }
  return set2;
}

void set_friends(int person1, int person2, int parent[],
                 int size[], int enemy_of[]) {
  int set1, set2, bigger_set, other_set;
  set1 = find(person1, parent);
  set2 = find(person2, parent);
  bigger_set = union_sets(person1, person2, parent, size);
  if (enemy_of[set1] != -1 && enemy_of[set2] != -1)
    union_sets(enemy_of[set1], enemy_of[set2], parent, size);
  if (bigger_set == set1)
    other_set = set2;
  else
    other_set = set1;
  if (enemy_of[bigger_set] == -1)
    enemy_of[bigger_set] = enemy_of[other_set];
}

void set_enemies(int person1, int person2, int parent[],
                 int size[], int enemy_of[]) {
  int set1, set2, enemy;
  set1 = find(person1, parent);
  set2 = find(person2, parent);
  enemy = enemy_of[set1];
  if (enemy == -1)
    enemy_of[set1] = person2;
  else
    union_sets(enemy, person2, parent, size);
  enemy = enemy_of[set2];
  if (enemy == -1)
    enemy_of[set2] = person1;
  else
    union_sets(enemy, person1, parent, size);
}

int are_friends(int person1, int person2, int parent[]) {
  return find(person1, parent) == find(person2, parent);
}

int are_enemies(int person1, int person2, int parent[],
                int enemy_of[]) {
  int set1, enemy;
  set1 = find(person1, parent);
  enemy = enemy_of[set1];
  return (enemy != -1) &&
         (find(enemy, parent) == find(person2, parent));
}

int main(void) {
  static int parent[MAX_PEOPLE], size[MAX_PEOPLE];
  static int enemy_of[MAX_PEOPLE];
  int num_people, i;
  int op, person1, person2;
  scanf("%d", &num_people);
  for (i = 0; i < num_people; i++) {
    parent[i] = i;
    size[i] = 1;
    enemy_of[i] = -1;
  }
  scanf("%d%d%d", &op, &person1, &person2);

  while (op != 0) {
    if (op == 1)
      if (are_enemies(person1, person2, parent, enemy_of))
        printf("-1\n");
      else
        set_friends(person1, person2, parent, size, enemy_of);

    else if (op == 2)
      if (are_friends(person1, person2, parent))
        printf("-1\n");
      else
        set_enemies(person1, person2, parent, size, enemy_of);

    else if (op == 3)
      if (are_friends(person1, person2, parent))
        printf("1\n");
      else
        printf("0\n");

    else if (op == 4)
      if (are_enemies(person1, person2, parent, enemy_of))
        printf("1\n");
      else
        printf("0\n");

    scanf("%d%d%d", &op, &person1, &person2);
  }
  return 0;
}
