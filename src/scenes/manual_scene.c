#include "manual_scene.h"

#include <gb/gb.h>
#include "../graphics/manual_map.h"
#include "grid_scene.h"
#include "scenes.h"

void init_manual_scene(void) {
  set_bkg_tiles(0, 0, 20, 18, MANUAL_MAP);
  SHOW_BKG;
  SHOW_SPRITES;
  DISPLAY_ON;
}

void update_manual_scene(Scene *current_scene, uint8_t just_pressed_keys, GridScene* grid, uint16_t* random_seed) {
  if (just_pressed_keys & J_START) {
    *current_scene = GRID_SCENE;
    fade_out();
    init_grid_scene(grid, *random_seed);
    fade_in();
  }
  (*random_seed)++;
}
