//Too slow (uses linear search)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set_a_switch(int door, int switch_positions[],
                  int door_for_switch[], int n) {
  int i, result;
  int found = 0;

  for (i = 0; i < n; i++)
    if (door_for_switch[i] == -1)
      switch_positions[i] = 0;

  result = tryCombination(switch_positions);
  if (result != door) {
    for (i = 0; i < n; i++)
      if (door_for_switch[i] == -1)
        switch_positions[i] = 1;
  }

  i = 0;
  while (!found) {
    if (door_for_switch[i] == -1)
      switch_positions[i] = 1 - switch_positions[i];
    result = tryCombination(switch_positions);
    if (result != door)
      found = 1;
    else
      i++;
  }
  door_for_switch[i] = door;
}

void exploreCave(int n) {
  int switch_positions[n], door_for_switch[n];
  int i;
  for (i = 0; i < n; i++)
    door_for_switch[i] = -1;

  for (i = 0; i < n; i++)
    set_a_switch(i, switch_positions, door_for_switch, n);
  answer(switch_positions, door_for_switch);
}
