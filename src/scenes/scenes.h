#ifndef SCENES_H
#define SCENES_H

typedef enum Scene {
  TITLE_SCENE,
  GRID_SCENE,
  MANUAL_SCENE,
  SETTINGS_SCENE
} Scene;

void fade_in(void);

void fade_out(void);

#endif
