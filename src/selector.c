#include "selector.h"
#include "selector_sprite.h"

#include <stdint.h>
#include <gb/gb.h>

void init_selector(Selector *selector) {
  set_sprite_data(0, 2, selector_sprite);
  set_sprite_tile(0, 0);
  move_sprite(0, 88, 88);
  selector->tile_x = 9;
  selector->tile_y = 8;
  selector->x = 88;
  selector->y = 88;
  NR52_REG = 0x80;
  NR50_REG = 0x77;
  NR51_REG = 0xFF;
}

void update_selector_position(Selector* selector) {
  int8_t diff_x = (selector->tile_x << 3) + 8 - selector->x;
  int8_t diff_y = (selector->tile_y << 3) + 16 - selector->y;
  if (diff_x < 0) {
    selector->x -= 1;
  } else if (diff_x > 0) {
    selector->x += 1;
  }
  if (diff_y < 0) {
    selector->y -= 1;
  } else if (diff_y > 0) {
    selector->y += 1;
  }
  move_sprite(0, selector->x, selector->y);
}

void play_move_sfx() {
  NR10_REG = 0x16;
  NR11_REG = 0x40;
  NR12_REG = 0x71;
  NR13_REG = 0xFF;
  NR14_REG = 0xE3;
}

void play_place_sfx() {
  NR10_REG = 0x1E;
  NR11_REG = 0x40;
  NR12_REG = 0x71;
  NR13_REG = 0x00;
  NR14_REG = 0xC3;
}

void update_selector(Selector *selector, uint8_t* map, uint8_t keys) {
  if (keys & J_LEFT && selector->tile_x != 0) {
    selector->tile_x -= 1;
    play_move_sfx();
  } else if (keys & J_RIGHT && selector->tile_x != 19) {
    selector->tile_x += 1;
    play_move_sfx();
  } else if (keys & J_UP && selector->tile_y != 0) {
    selector->tile_y -= 1;
    play_move_sfx();
  } else if (keys & J_DOWN && selector->tile_y != 17) {
    selector->tile_y += 1;
    play_move_sfx();
  }
  uint16_t index = selector->tile_y * 20 + selector->tile_x;
  if (map[index]) {
    set_sprite_tile(0, 0);
  } else {
    set_sprite_tile(0, 1);
  }
  if (keys & J_A) {
    if (map[index]) {
      map[index] = 0;
    } else {
      map[index] = 1;
    }
    set_bkg_tiles(0, 0, 20, 18, map);
    play_place_sfx();
  }
  update_selector_position(selector);
}
