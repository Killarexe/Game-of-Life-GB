#include "title_scene.h"

#include <gb/gb.h>
#include <stdint.h>
#include "../graphics/title_screen_map.h"
#include "scenes.h"
#include "../huge_driver/hUGEDriver.h"
#include "../musics/plateau.h"

uint8_t buttons[] = {J_UP, J_UP, J_DOWN, J_DOWN, J_LEFT, J_RIGHT, J_LEFT, J_RIGHT, J_A, J_B};
uint8_t buttons_index = 0;

void init_title_scene(void) {
  set_bkg_tiles(0, 0, 20, 18, TITLE_SCREEN_MAP);
}

uint8_t update_title_scene(Scene *current_scene, uint16_t* random_seed, uint8_t just_pressed_keys) {
  (*random_seed)++;
  if (buttons_index == 10) {
    buttons_index++;
    hUGE_init(&plateau);
  }
  if ((just_pressed_keys & buttons[buttons_index]) && buttons_index < 10) {
    buttons_index++;
  }
  if (just_pressed_keys & J_START) {
    *current_scene = MANUAL_SCENE;
    return 1;
  }
  return 0;
}
