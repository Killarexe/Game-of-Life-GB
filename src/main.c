#include <gb/gb.h>
#include <stdint.h>

#include "huge_driver/hUGEDriver.h"
#include "musics/title.h"

#include "graphics/tiles.h"

#include "scenes/intro_scene.h"
#include "scenes/grid_scene.h"
#include "scenes/manual_scene.h"
#include "scenes/title_scene.h"
#include "scenes/settings_scene.h"
#include "scenes/scenes.h"

void init_sound_driver(void) {
  NR52_REG = 0x80;
  NR51_REG = 0xFF;
  NR50_REG = 0x77;
  hUGE_init(&title_screen_music);
  add_VBL(hUGE_dosound);
}

int main(void) {
  Scene current_scene = TITLE_SCENE;
  uint8_t previous_keys = 0;
  uint16_t random_seed = 0;
  GridScene grid;
  SettingsScene settings;

  init_sound_driver();
  set_bkg_data(0, 36, TILES);
  start_intro_scene();

  while (1) {
    uint8_t current_keys = joypad();
    uint8_t just_pressed_keys = (current_keys ^ previous_keys) & current_keys;

    if (current_scene == TITLE_SCENE) {
      update_title_scene(&current_scene, just_pressed_keys);
    } else if (current_scene == MANUAL_SCENE) {
      update_manual_scene(&current_scene, just_pressed_keys, &grid, &random_seed);
    } else if (current_scene == SETTINGS_SCENE) {
      update_settings_scene(&settings, &grid, just_pressed_keys);
    } else {
      update_grid_scene(&grid, just_pressed_keys);
    }

    previous_keys = current_keys;
    wait_vbl_done();
  }
  return 0;
}
