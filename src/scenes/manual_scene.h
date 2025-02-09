#ifndef MANUAL_SCENE_H 
#define MANUAL_SCENE_H

#include <stdint.h>
#include "grid_scene.h"
#include "scenes.h"

void init_manual_scene(void);

void update_manual_scene(Scene* current_scene, uint8_t just_pressed_keys, GridScene* grid, uint16_t* random_seed);

#endif
