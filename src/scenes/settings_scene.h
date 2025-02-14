#ifndef SETTINGS_SCENE_H
#define SETTINGS_SCENE_H

#include <stdint.h>
#include "grid_scene.h"
#include "scenes.h"

typedef struct SettingsScene {
  uint8_t cursor_pos;
} SettingsScene;

void init_settings_scene(SettingsScene* settings, GridScene* grid);
void update_settings_scene(SettingsScene* settings, GridScene* grid, uint8_t just_pressed_keys, Scene* current_scene);

#endif
