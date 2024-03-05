#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 255
#define TEST_CASES 5

typedef struct node {
  int candy;
  struct node *left, *right;
} node;

int tree_candy(node *tree) {
  if (!tree->left && !tree->right)
    return tree->candy;
  return tree_candy(tree->left) + tree_candy(tree->right);
}

int tree_streets(node *tree) {
  if (!tree->left && !tree->right)
    return 0;
  return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  else
    return v2;
}

int tree_height(node *tree) {
  if (!tree->left && !tree->right)
    return 0;
  return 1 + max(tree_height(tree->left), tree_height(tree->right));
}

void tree_solve(node *tree) {
  int candy = tree_candy(tree);
  int height = tree_height(tree);
  int num_streets = tree_streets(tree) - height;
  printf("%d %d\n", num_streets, candy);
}

node *read_tree_helper(char *line, int *pos) {
  node *tree;
  tree = malloc(sizeof(node));
  if (tree == NULL) {
    fprintf(stderr, "malloc error\n");
    exit(1);
  }
  if (line[*pos] == '(') {
    (*pos)++;
    tree->left = read_tree_helper(line, pos);
    (*pos)++;
    tree->right = read_tree_helper(line, pos);
    (*pos)++;
    return tree;
  } else {
    tree->left = NULL;
    tree->right = NULL;
    tree->candy = line[*pos] - '0';
    (*pos)++;
    if (line[*pos] != ')' && line[*pos] != ' ' &&
        line[*pos] != '\0') {
      tree->candy = tree->candy * 10 + line[*pos] - '0';
      (*pos)++;
    }
    return tree;
  }
}

node *read_tree(char *line) {
  int pos = 0;
  return read_tree_helper(line, &pos);
}

int main(void) {
  int i;
  char line[SIZE + 1];
  node *tree;
  for (i = 0; i < TEST_CASES; i++) {
    gets(line);
    tree = read_tree(line);
    tree_solve(tree);
  }
  return 0;
}
