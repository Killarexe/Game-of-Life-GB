#include "intro_scene.h"

#include <gb/gb.h>
#include "scenes.h"
#include "title_scene.h"
#include "../graphics/start_message_map.h"

void start_intro_scene(void) {
  set_bkg_tiles(0, 0, 20, 18, START_MESSAGE_MAP);
  SHOW_BKG;
  SHOW_SPRITES;
  DISPLAY_ON;
  fade_in();
  delay(4000);
  fade_out();
  init_title_scene();
  fade_in();
}
