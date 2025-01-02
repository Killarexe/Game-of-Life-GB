#ifndef GRID_SCENE_H
#define GRID_SCENE_H

#define MAP_HEIGHT 18
#define MAP_WIDTH 20

#include <stdint.h>
#include "../selector.h"

void init_grid_scene(Selector* selector, uint8_t* current_map, uint8_t* is_paused);
void update_grid_scene(Selector* selector, uint8_t** current_map, uint8_t* first_map, uint8_t* second_map, uint8_t just_pressed_keys, uint8_t* is_paused);

#endif
