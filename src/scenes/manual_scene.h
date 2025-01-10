#ifndef MANUAL_SCENE_H 
#define MANUAL_SCENE_H

#include <stdint.h>
#include "scenes.h"

void init_manual_scene(void);

uint8_t update_manual_scene(Scene* current_scene, uint8_t just_pressed_keys);

#endif
