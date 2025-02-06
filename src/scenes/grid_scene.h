#ifndef GRID_SCENE_H
#define GRID_SCENE_H

#define MAP_HEIGHT 18
#define MAP_WIDTH 20

#include <stdint.h>
#include "../selector.h"

typedef struct GridScene {
  Selector selector;
  uint8_t first_map[360];
  uint8_t second_map[360];
  uint8_t* current_map;
  uint8_t is_paused;
  uint8_t born_cell_count;
  uint8_t alive_cells_count;
} GridScene;

void init_grid_scene(GridScene* grid, uint16_t random_seed);
void update_grid_scene(GridScene* grid, uint8_t just_pressed_keys);

#endif
