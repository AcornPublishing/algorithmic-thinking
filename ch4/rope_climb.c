#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000000

typedef struct position {
  int height, state;
} position;

typedef int board[SIZE * 2][2];
typedef position positions[SIZE * 4];

void add_position_up(int from_height, int to_height, int max_height,
                     positions pos, int *num_pos,
                     int itching[], board min_moves) {
  int distance = 1 + min_moves[from_height][0];
  if (to_height <= max_height && itching[to_height] == 0 &&
      (min_moves[to_height][0] == -1 ||
       min_moves[to_height][0] > distance)) {
    min_moves[to_height][0] = distance;
    pos[*num_pos] = (position){to_height, 0};
    (*num_pos)++;
  }
}

void add_position_down(int from_height, int to_height,
                       positions pos, int *num_pos,
                       board min_moves) {
  int distance = min_moves[from_height][1];
  if (to_height >= 0 &&
      (min_moves[to_height][1] == -1 ||
       min_moves[to_height][1] > distance)) {
    min_moves[to_height][1] = distance;
    pos[*num_pos] = (position){to_height, 1};
    (*num_pos)++;
  }
}

void add_position_01(int from_height,
                     positions pos, int *num_pos,
                     board min_moves) {
  int distance = 1 + min_moves[from_height][0];
  if (min_moves[from_height][1] == -1 ||
      min_moves[from_height][1] > distance) {
    min_moves[from_height][1] = distance;
    pos[*num_pos] = (position){from_height, 1};
    (*num_pos)++;
  }
}

void add_position_10(int from_height,
                     positions pos, int *num_pos,
                     int itching[], board min_moves) {
  int distance = min_moves[from_height][1];
  if (itching[from_height] == 0 &&
      (min_moves[from_height][0] == -1 ||
       min_moves[from_height][0] > distance)) {
    min_moves[from_height][0] = distance;
    pos[*num_pos] = (position){from_height, 0};
    (*num_pos)++;
  }
}

void find_distances(int target_height, int jump_distance,
                    int itching[], board min_moves) {
  static positions cur_positions, new_positions;
  int num_cur_positions, num_new_positions;
  int i, j, from_height, from_state;
  for (i = 0; i < target_height * 2; i++)
    for (j = 0; j < 2; j++)
      min_moves[i][j] = -1;
  min_moves[0][0] = 0;
  cur_positions[0] = (position){0, 0};
  num_cur_positions = 1;

  while (num_cur_positions > 0) {
    num_new_positions = 0;
    for (i = 0; i < num_cur_positions; i++) {
      from_height = cur_positions[i].height;
      from_state = cur_positions[i].state;

      if (from_state == 0) {
        add_position_up(from_height, from_height + jump_distance,
                        target_height * 2 - 1,
                        new_positions, &num_new_positions,
                        itching, min_moves);
        add_position_01(from_height, new_positions, &num_new_positions,
                        min_moves);
      } else {
        add_position_down(from_height, from_height - 1,
                          cur_positions, &num_cur_positions, min_moves);
        add_position_10(from_height,
                        cur_positions, &num_cur_positions,
                        itching, min_moves);
      }
    }

    num_cur_positions = num_new_positions;
    for (i = 0; i < num_cur_positions; i++)
      cur_positions[i] = new_positions[i];
  }
}

void solve(int target_height, board min_moves) {
  int best = -1;
  int i;
  for (i = target_height; i < target_height * 2; i++)
    if (min_moves[i][0] != -1 && (best == -1 || min_moves[i][0] < best))
      best = min_moves[i][0];
  printf("%d\n", best);
}

int main(void) {
  int target_height, jump_distance, num_itching_sections;
  static int itching[SIZE * 2] = {0};
  static board min_moves;
  int i, j, itch_start, itch_end;
  scanf("%d%d%d", &target_height, &jump_distance, &num_itching_sections);
  for (i = 0; i < num_itching_sections; i++) {
    scanf("%d%d", &itch_start, &itch_end);
    for (j = itch_start; j <= itch_end; j++)
      itching[j] = 1;
  }
  find_distances(target_height, jump_distance, itching, min_moves);
  solve(target_height, min_moves);
  return 0;
}

