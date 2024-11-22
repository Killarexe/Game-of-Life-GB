#ifndef SELECTOR_H
#define SELECTOR_H

#include <stdint.h>

typedef struct Selector {
  uint8_t tile_x, tile_y;
  uint8_t x, y;
} Selector;

void init_selector(Selector* selector);

void update_selector(Selector* selector, uint8_t* map, uint8_t keys);

#endif
