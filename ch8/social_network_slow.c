//Too slow (inefficient union-find)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PEOPLE 100000

int find(int person, int community_of[]) {
  return community_of[person];
}

void union_communities(int person1, int person2, int community_of[],
                       int size[], int num_community, int num_people) {
  int community1, community2, i;
  community1 = find(person1, community_of);
  community2 = find(person2, community_of);
  if (community1 == community2)
    return;
  if (size[community1] + size[community2] > num_community)
    return;

  for (i = 1; i <= num_people; i++)
    if (community_of[i] == community1) {
      community_of[i] = community2;
      size[community2]++;
    }
}

int main(void) {
  static int community_of[MAX_PEOPLE + 1], size[MAX_PEOPLE + 1];
  int num_people, num_community, num_ops, i;
  char op;
  int person1, person2;
  scanf("%d%d", &num_people, &num_community);
  for (i = 1; i <= num_people; i++) {
    community_of[i] = i;
    size[i] = 1;
  }
  scanf("%d", &num_ops);

  for (i = 0; i < num_ops; i++) {
    scanf(" %c", &op);

    if (op == 'A') {
      scanf("%d%d", &person1, &person2);
      union_communities(person1, person2, community_of, size, num_community,
                        num_people);
    }

    else if (op == 'E') {
      scanf("%d%d", &person1, &person2);
      if (find(person1, community_of) == find(person2, community_of))
        printf("Yes\n");
      else
        printf("No\n");
    }

    else {
      scanf("%d", &person1);
      printf("%d\n", size[find(person1, community_of)]);
    }
  }
  return 0;
}
