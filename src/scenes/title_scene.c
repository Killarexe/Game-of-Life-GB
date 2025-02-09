#include "title_scene.h"

#include <gb/gb.h>
#include <stdint.h>

#include "../graphics/title_screen_map.h"
#include "scenes.h"
#include "../huge_driver/hUGEDriver.h"
#include "../musics/plateau.h"
#include "manual_scene.h"

uint8_t buttons[] = {J_UP, J_UP, J_DOWN, J_DOWN, J_LEFT, J_RIGHT, J_LEFT, J_RIGHT, J_B, J_A};
uint8_t buttons_index = 0;

void init_title_scene(void) {
  set_bkg_tiles(0, 0, 20, 18, TITLE_SCREEN_MAP);
}

void update_title_scene(Scene *current_scene, uint8_t just_pressed_keys) {
  if (buttons_index == 10) {
    buttons_index++;
    hUGE_init(&plateau);
  }
  if ((just_pressed_keys & buttons[buttons_index]) && buttons_index < 10) {
    buttons_index++;
  }
  if (just_pressed_keys & J_START) {
    *current_scene = MANUAL_SCENE;
    fade_out();
    init_manual_scene();
    fade_in();
  }
}
