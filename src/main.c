#include <gb/gb.h>
#include <stdint.h>

#include "huge_driver/hUGEDriver.h"
#include "musics/plateau.h"

#include "graphics/tiles.h"

#include "selector.h"

#include "scenes/grid_scene.h"
#include "scenes/title_scene.h"
#include "scenes/scenes.h"

void fadeout(void) {
  for (uint8_t i = 0; i < 4; i++) {
    switch(i){
      case 0:
        // 11 10 01 00
        BGP_REG = 0xE4;
        break;
      case 1:
        // 11 11 10 01
        BGP_REG = 0xF9;
        break;
      case 2:
        // 11 11 11 10
        BGP_REG = 0xFE;
        break;
      case 3:
        // 11 11 11 11
        BGP_REG = 0xFF;	
        break;						
    }
    delay(110);
  }
}

void fadein(void) {
  for (uint8_t i=0; i<4; i++) {
    switch(i){
      case 0:
        // 11 11 11 11
        BGP_REG = 0xFF;	
        break;
      case 1:
        // 11 11 11 10
        BGP_REG = 0xFE;
        break;
      case 2:
        // 11 11 10 01
        BGP_REG = 0xF9;
        break;
      case 3:
        // 11 10 01 00
        BGP_REG = 0xE4;
        break;					
    }
    delay(110);
  }
}

void init_sound_driver(void) {
  NR52_REG = 0x80;
  NR51_REG = 0xFF;
  NR50_REG = 0x77;
  hUGE_init(&plateau);
  add_VBL(hUGE_dosound);
}

int main(void) {
  Selector selector;
  uint8_t first_map[360];
  uint8_t second_map[360];
  uint8_t* current_map = first_map;
  uint8_t is_paused = 1;

  init_sound_driver();

  set_bkg_data(0, 14, TILES);

  Scene current_scene = TITLE_SCENE;
  init_title_scene();
  fadein();

  uint8_t previous_keys = 0;

  while (1) {
    uint8_t current_keys = joypad();
    uint8_t just_pressed_keys = (current_keys ^ previous_keys) & current_keys;

    if (current_scene == TITLE_SCENE) {
      if (update_title_scene(&current_scene, just_pressed_keys)) {
        fadeout();
        init_grid_scene(&selector, current_map, &is_paused);
        fadein();
      }
    } else {
      update_grid_scene(&selector, &current_map, first_map, second_map, just_pressed_keys, &is_paused);
    }

    previous_keys = current_keys;
    wait_vbl_done();
  }
  return 0;
}
