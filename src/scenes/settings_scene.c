#include "settings_scene.h"

#include <gb/gb.h>
#include "../graphics/settings_map.h"
#include "../huge_driver/hUGEDriver.h"
#include "../musics/spot.h"
#include "grid_scene.h"

void update_background(uint8_t born_cell_count, uint8_t alive_cells_count, uint8_t cursor_pos) {
  set_bkg_tiles(0, 0, 20, 18, SETTINGS_MAP);
  const uint8_t cursor_y_poses[] = {5, 7, 9, 11};
  uint8_t born_tile = born_cell_count + 0x1B;
  uint8_t live_tile = alive_cells_count + 0x1B;
  set_bkg_tiles(3, cursor_y_poses[cursor_pos], 1, 1, &cursor_pos);
  set_bkg_tiles(15, 5, 1, 1, &born_tile);
  set_bkg_tiles(15, 7, 1, 1, &alive_cells_count);
}

void init_settings_scene(SettingsScene* settings, GridScene* grid) {
  settings->cursor_pos = 0;
  update_background(grid->born_cell_count, grid->alive_cells_count, 0);
  hUGE_init(&spot_music);
  HIDE_SPRITES;
}

uint8_t clamp(uint8_t value, uint8_t min, uint8_t max) {
  return value > max ? max : value < min ? min : value;
}

void update_settings_scene(SettingsScene* settings, GridScene* grid, uint8_t just_pressed_keys) {
  if (just_pressed_keys & J_UP && settings->cursor_pos != 0) {
    settings->cursor_pos++;
    update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
  } else if (just_pressed_keys & J_DOWN && settings->cursor_pos <= 3) {
    settings->cursor_pos--;
    update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
  } else if (just_pressed_keys & J_A) {
    if (settings->cursor_pos == 2) {
      empty_map(grid);
    } else if (settings->cursor_pos == 3) {
      randomize_map(grid);
    }
  } else if (just_pressed_keys & J_LEFT) {
    if (settings->cursor_pos == 0) {
      grid->born_cell_count = clamp(grid->born_cell_count + 1, 1, 8);
      update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
    } else if (settings->cursor_pos == 1) {
      grid->alive_cells_count = clamp(grid->alive_cells_count + 1, 1, 8);
      update_background(grid->born_cell_count, grid->alive_cells_count, settings->cursor_pos);
    }
  } else if (just_pressed_keys & (J_B | J_SELECT)) {
    hUGE_init(&led_music);
    init_selector(&grid->selector);
    set_bkg_tiles(0, 0, 20, 18, grid->current_map);
    SHOW_SPRITES;
  }
}
