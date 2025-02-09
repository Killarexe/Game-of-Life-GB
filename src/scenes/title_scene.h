#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <stdint.h>
#include "scenes.h"

void init_title_scene(void);

void update_title_scene(Scene* current_scene, uint8_t just_pressed_keys);

#endif
