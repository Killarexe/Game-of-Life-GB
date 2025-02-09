#include "scenes.h"

#include <gb/gb.h>
#include <stdint.h>

void fade_out() {
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

void fade_in() {
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
