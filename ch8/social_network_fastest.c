//ZOOM! Fastest one, with union-find optimizations

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100000

int find(int person, int parent[]) {
  int community = person, temp;
  while (parent[community] !=  community)
    community = parent[community];
  while (parent[person] != community) {
    temp = parent[person];
    parent[person] = community;
    person = temp;
  }
  return community;
}

void union_communities(int person1, int person2, int parent[],
                       int size[], int num_community) {
  int community1, community2, temp;
  community1 = find(person1, parent);
  community2 = find(person2, parent);
  if (community1 != community2 &&
      size[community1] + size[community2] <= num_community) {
    if (size[community1] > size[community2]) {
      temp = community1;
      community1 = community2;
      community2 = temp;
    }
    parent[community1] = community2;
    size[community2] = size[community2] + size[community1];
  }
}

int main(void) {
  static int parent[MAX_PEOPLE + 1], size[MAX_PEOPLE + 1];
  int num_people, num_community, num_ops, i;
  char op;
  int person1, person2;
  scanf("%d%d", &num_people, &num_community);
  for (i = 1; i <= num_people; i++) {
    parent[i] = i;
    size[i] = 1;
  }
  scanf("%d", &num_ops);

  for (i = 0; i < num_ops; i++) {
    scanf(" %c", &op);

    if (op == 'A') {
      scanf("%d%d", &person1, &person2);
      union_communities(person1, person2, parent, size, num_community);
    }

    else if (op == 'E') {
      scanf("%d%d", &person1, &person2);
      if (find(person1, parent) == find(person2, parent))
        printf("Yes\n");
      else
        printf("No\n");
    }

    else {
      scanf("%d", &person1);
      printf("%d\n", size[find(person1, parent)]);
    }
  }
  return 0;
}
