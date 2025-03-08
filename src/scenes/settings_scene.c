#include "settings_scene.h"

#include <gb/gb.h>
#include "../graphics/settings_map.h"
#include "../huge_driver/hUGEDriver.h"
#include "../musics/spot.h"
#include "../musics/led.h"
#include "grid_scene.h"
#include "scenes.h"

void update_background(uint8_t born_cell_count, uint8_t alive_cells_count, uint8_t cursor_pos) {
  const uint8_t cursor_y_poses[] = {5, 7, 9, 11};
  const uint8_t arrow_tile = 27; 
  const uint8_t none_tile = 1;
  uint8_t born_tile = born_cell_count + arrow_tile;
  uint8_t live_tile = alive_cells_count + arrow_tile;
  for (uint8_t i = 0; i < 4; i++) {
    set_bkg_tiles(3, cursor_y_poses[i], 1, 1, i == cursor_pos ? &arrow_tile : &none_tile);
  }
  set_bkg_tiles(15, 5, 1, 1, &born_tile);
  set_bkg_tiles(15, 7, 1, 1, &live_tile);
}

void init_settings_scene(SettingsScene* settings, GridScene* grid) {
  settings->cursor_pos = 0;
  set_bkg_tiles(0, 0, 20, 18, SETTINGS_MAP);
  update_background(grid->born_cell_count, grid->alive_cells_count, 0);
  hUGE_init(&spot_music);
  HIDE_SPRITES;
}

uint8_t clamp(uint8_t value, uint8_t min, uint8_t max) {
  return value > max ? max : value < min ? min : value;
}


void play_select_sfx(void) {
  NR10_REG = 0x16;
  NR11_REG = 0x00;
  NR12_REG = 0xF1;
  NR13_REG = 0xFF;
  NR14_REG = 0xE4;
}

void play_pressed_sfx(void) {
  NR10_REG = 0x13;
  NR11_REG = 0xC0;
  NR12_REG = 0xF1;
  NR13_REG = 0xF0;
  NR14_REG = 0xE4;
}

void play_exit_sfx(void) {
  NR10_REG = 0x1D;
  NR11_REG = 0x80;
  NR12_REG = 0xF1;
  NR13_REG = 0xFF;
  NR14_REG = 0xE5;
}

void update_settings_scene(SettingsScene* settings, GridScene* grid, uint8_t just_pressed_keys, Scene* current_scene) {
  if (just_pressed_keys & J_DOWN && settings->cursor_pos < 3) {
    settings->cursor_pos++;
    update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
    play_select_sfx();
  } else if (just_pressed_keys & J_UP && settings->cursor_pos != 0) {
    settings->cursor_pos--;
    update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
    play_select_sfx();
  } else if (just_pressed_keys & J_A) {
    if (settings->cursor_pos == 2) {
      play_pressed_sfx();
      empty_map(grid);
    } else if (settings->cursor_pos == 3) {
      play_pressed_sfx();
      randomize_map(grid);
    } else {
      play_exit_sfx();
    }
  } else if (just_pressed_keys & J_RIGHT) {
    if (settings->cursor_pos == 0) {
      play_pressed_sfx();
      grid->born_cell_count = clamp(grid->born_cell_count + 1, 1, 8);
    } else if (settings->cursor_pos == 1) {
      play_pressed_sfx();
      grid->alive_cells_count = clamp(grid->alive_cells_count + 1, 1, 8);
    } else {
      play_exit_sfx();
    }
    update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
  } else if (just_pressed_keys & J_LEFT) {
    if (settings->cursor_pos == 0) {
      play_pressed_sfx();
      grid->born_cell_count = clamp(grid->born_cell_count - 1, 1, 8);
    } else if (settings->cursor_pos == 1) {
      play_pressed_sfx();
      grid->alive_cells_count = clamp(grid->alive_cells_count - 1, 1, 8);
    } else {
      play_exit_sfx();
    }
    update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
  } else if (just_pressed_keys & (J_B | J_SELECT)) {
    play_exit_sfx();
    *current_scene = GRID_SCENE;
    fade_out();
    hUGE_init(&led_music);
    init_selector(&grid->selector);
    set_bkg_tiles(0, 0, 20, 18, grid->current_map);
    fade_in();
    SHOW_SPRITES;
  }
}
