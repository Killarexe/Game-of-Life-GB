#ifndef SCENES_H
#define SCENES_H

typedef enum Scene {
  TITLE_SCENE,
  GRID_SCENE,
  MANUAL_SCENE,
  SETTINGS_SCENE
} Scene;

void fade_in();

void fade_out();

#endif
