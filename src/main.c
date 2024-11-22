#include <gb/gb.h>
#include <stdint.h>
#include "selector.h"
#include "tiles.h"
#include "cells_map.h"

int main() {
  uint8_t first_map[360];
  uint8_t second_map[360];
  uint8_t* current_map = first_map;

  set_bkg_data(0, 2, TILES);
  set_bkg_tiles(0, 0, 20, 18, current_map);

  Selector selector;
  init_selector(&selector);

  SHOW_SPRITES;
  SHOW_BKG;
  DISPLAY_ON;

  uint8_t previous_keys = 0;
  uint8_t is_paused = 1;

  while (1) {
    uint8_t current_keys = joypad();
    uint8_t just_pressed_keys = (current_keys ^ previous_keys) & current_keys;
    if (is_paused) {
      update_selector(&selector, current_map, just_pressed_keys); 
    } else {
      update_map(&current_map, first_map, second_map);
    }
    if (just_pressed_keys & J_START) {
      if (is_paused == 1) {
        is_paused = 0;
        HIDE_SPRITES;
      } else {
        is_paused = 1;
        SHOW_SPRITES;
      }
    }
    previous_keys = current_keys;
    wait_vbl_done();
  }
  return 0;
}
