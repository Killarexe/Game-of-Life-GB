#include "grid_scene.h"

#include <gb/gb.h>
#include <rand.h>
#include <stdint.h>
#include "../selector.h"
#include "../huge_driver/hUGEDriver.h"
#include "../musics/led.h"
#include "../musics/spot.h"

void init_grid_scene(GridScene* grid, uint16_t random_seed) {
  grid->is_paused = 1;
  grid->current_map = grid->first_map;

  initrand(random_seed);
  uint8_t music = rand() & 1;
  if (music == 0) {
    hUGE_init(&led_music);
  } else {
    hUGE_init(&spot_music);
  }

  init_selector(&grid->selector);
  set_bkg_tiles(0, 0, 20, 18, grid->current_map);

  
  SHOW_SPRITES;
  SHOW_BKG;
  DISPLAY_ON;
}

uint8_t warp_index(int8_t index, uint8_t max) {
  if (index < 0) {
    return max - 1;
  }
  if (index >= max) {
    return 0;
  }
  return index;
}

uint8_t get_neighbours(uint8_t* map, uint8_t x, uint8_t y) {
  uint8_t neighbours = 0;
  for (int8_t y_offset = -1; y_offset < 2; y_offset++) {
    uint8_t y_pos = warp_index(y + y_offset, MAP_HEIGHT);
    for (int8_t x_offset = -1; x_offset < 2; x_offset++) {
      if (x_offset == 0 && y_offset == 0) {
        continue;
      }
      uint8_t x_pos = warp_index(x + x_offset, MAP_WIDTH);
      if (map[y_pos * MAP_WIDTH + x_pos] == 1) {
        neighbours++;
      }
    }
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
      uint16_t index = y * MAP_WIDTH + x;
      uint8_t neighbours = get_neighbours(grid->current_map, x, y);
      if (grid->current_map[index] == 1 && (neighbours == 2 || neighbours == 3)) {
        next_map[index] = 1;
      } else if (neighbours == 3) {
        next_map[index] = 1;
      } else {
        next_map[index] = 0;
      }
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
      randomize_map(grid->current_map);
    } else if (just_pressed_keys & J_B) {
      empty_map(grid->current_map);
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
