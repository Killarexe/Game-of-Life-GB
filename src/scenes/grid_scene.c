#include "grid_scene.h"

#include <gb/gb.h>
#include <rand.h>
#include <stdint.h>
#include "../selector.h"
#include "../huge_driver/hUGEDriver.h"
#include "../musics/led.h"

void init_grid_scene(GridScene* grid, uint16_t random_seed) {
  grid->is_paused = 1;
  grid->current_map = grid->first_map;
  grid->alive_cells_count = 2;
  grid->born_cell_count = 3;

  initrand(random_seed);
  hUGE_init(&led_music);

  init_selector(&grid->selector);
  set_bkg_tiles(0, 0, 20, 18, grid->current_map);

  
  SHOW_SPRITES;
  SHOW_BKG;
  DISPLAY_ON;
}

uint8_t get_neighbours(uint8_t* map, uint8_t x, uint8_t y) {
  uint8_t neighbours = 0;
  const int8_t offsets[8][2] = {
    {-1, -1}, {0, -1}, {1, -1},
    {-1,  0},          {1,  0},
    {-1,  1}, {0,  1}, {1,  1}
  };
  
  for (uint8_t i = 0; i < 8; i++) {
    int16_t nx = x + offsets[i][0];
    int16_t ny = y + offsets[i][1];
    
    if (nx < 0) nx = MAP_WIDTH - 1;
    if (nx >= MAP_WIDTH) nx = 0;
    if (ny < 0) ny = MAP_HEIGHT - 1;
    if (ny >= MAP_HEIGHT) ny = 0;
    
    uint16_t neighbor_pos = ny * MAP_WIDTH + nx;
    neighbours += map[neighbor_pos];
  }
  
  return neighbours;
}

void update_map(GridScene* grid) { 
  uint8_t* next_map = (void*)0;
  if (grid->current_map == grid->first_map) {
    next_map = grid->second_map;
  } else {
    next_map = grid->first_map;
  }

  for (uint8_t y = 0; y < MAP_HEIGHT; y++) {
    for (uint8_t x = 0; x < MAP_WIDTH; x++) {
      uint16_t index = ((y << 2) * 5) + x;
      uint8_t neighbours = get_neighbours(grid->current_map, x, y);
      next_map[index] = (grid->current_map[index] && neighbours == grid->alive_cells_count) || neighbours == grid->born_cell_count;
    }
  }
  grid->current_map = next_map;
  set_bkg_tiles(0, 0, MAP_WIDTH, MAP_HEIGHT, grid->current_map);
}

void randomize_map(uint8_t* current_map) {
  for (uint16_t index = 0; index < MAP_WIDTH * MAP_HEIGHT; index++) {
    current_map[index] = rand() & 1;
  }
  set_bkg_tiles(0, 0, MAP_WIDTH, MAP_HEIGHT, current_map);
}

void empty_map(uint8_t* current_map) {
  for (uint16_t index = 0; index < MAP_WIDTH * MAP_HEIGHT; index++) {
    current_map[index] = 0;
  }
  set_bkg_tiles(0, 0, MAP_WIDTH, MAP_HEIGHT, current_map);
}

void update_grid_scene(GridScene* grid, uint8_t just_pressed_keys) {
  if (grid->is_paused == 1) {
    update_selector(&grid->selector, grid->current_map, just_pressed_keys);
    if (just_pressed_keys & J_SELECT) {
      //TODO: change to settings scene & redo state/scene management.
    } 
  } else {
    update_map(grid);
  }
  if (just_pressed_keys & J_START) {
    if (grid->is_paused == 1) {
      grid->is_paused = 0;
      HIDE_SPRITES;
    } else {
      grid->is_paused = 1;
      SHOW_SPRITES;
    }
  }
}
