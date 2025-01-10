#include "manual_scene.h"

#include <gb/gb.h>
#include "../graphics/manual_map.h"
#include "scenes.h"

void init_manual_scene(void) {
  set_bkg_tiles(0, 0, 20, 18, MANUAL_MAP);
  SHOW_BKG;
  SHOW_SPRITES;
  DISPLAY_ON;
}

uint8_t update_manual_scene(Scene *current_scene, uint8_t just_pressed_keys) {
  if (just_pressed_keys & J_START) {
    *current_scene = GRID_SCENE;
    return 1;
  }
  return 0;
}
