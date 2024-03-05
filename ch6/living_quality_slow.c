#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 3001
#define MAX_COLS 3001

typedef int board[MAX_ROWS][MAX_COLS];

int can_make_quality(int quality, int r, int c, int h, int w, board q) {
  static int zero_one[MAX_ROWS][MAX_COLS];
  int i, j;
  int top_row, left_col, bottom_row, right_col;
  int total;

  for (i = 0; i < r; i++)
    for (j = 0; j < c; j++)
      if (q[i][j] <= quality)
        zero_one[i][j] = -1;
      else
        zero_one[i][j] = 1;

  for (top_row = 0; top_row < r - h + 1; top_row++)
    for (left_col = 0; left_col < c - w + 1; left_col++) {
      bottom_row = top_row + h - 1;
      right_col = left_col + w - 1;
      total = 0;
      for (i = top_row; i <= bottom_row; i++)
        for (j = left_col; j <= right_col; j++)
          total = total + zero_one[i][j];
      if (total <= 0)
        return 1;
    }
  return 0;
}

int rectangle(int r, int c, int h, int w, board q) {
  int low, high, mid;
  low = 0;
  high = r * c + 1;
  while (high - low > 1) {
    mid = (low + high) / 2;
    if (can_make_quality(mid, r, c, h, w, q))
      high = mid;
    else
      low = mid;
  }
  return high;
}
