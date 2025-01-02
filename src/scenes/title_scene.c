#include "title_scene.h"

#include <gb/gb.h>
#include "../graphics/title_screen_map.h"
#include "scenes.h"

void init_title_scene(void) {
  set_bkg_tiles(0, 0, 20, 18, TITLE_SCREEN_MAP);
  SHOW_BKG;
  SHOW_SPRITES;
  DISPLAY_ON;
}

uint8_t update_title_scene(Scene *current_scene, uint8_t just_pressed_keys) {
  if (just_pressed_keys & J_START) {
    *current_scene = GRID_SCENE;
    return 1;
  }
  return 0;
}
