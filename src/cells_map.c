#include "cells_map.h"

#include <gb/gb.h>
#include <stdint.h>

uint8_t get_neighbours(uint8_t* map, uint8_t x, uint8_t y) {
  uint8_t neighbours = 0;
  for (int8_t y_offset = -1; y_offset < 2; y_offset++) {
    uint16_t y_pos = y + y_offset;
    for (int8_t x_offset = -1; x_offset < 2; x_offset++) {
      uint16_t x_pos = x + x_offset;
      uint16_t cell_index = y_pos * 20 + x_pos; 
      if ((x_offset != y_offset || x_offset != 0) && map[cell_index] == 1) {
        neighbours++;
      }
    }
  }
  return neighbours;
}

void update_map(uint8_t** current_map, uint8_t* first_map, uint8_t* second_map) { 
  uint8_t* next_map = (void*)0;
  if (*current_map == first_map) {
    next_map = second_map;
  } else {
    next_map = first_map;
  }
  for (uint8_t y = 0; y < 18; y++) {
    for (uint8_t x = 0; x < 20; x++) {
      uint16_t index = y * 20 + x;
      uint8_t neighbours = get_neighbours(*current_map, x, y);
      if ((*current_map)[index] == 1 && (neighbours == 2 || neighbours == 3)) {
        next_map[index] = 1;
      } else if (neighbours == 3) {
        next_map[index] = 1;
      } else {
        next_map[index] = 0;
      }
    }
  }
  *current_map = next_map;
  set_bkg_tiles(0, 0, 20, 18, *current_map);
}
