/* 
 * File:   app.c
 * Author: houda
 *
 * Created on February 18, 2024, 3:42 PM
 */

#include "app.h"

const uint8 customChar[] = {
  0x0E,
  0x0A,
  0x11,
  0x11,
  0x11,
  0x11,
  0x1F,
  0x00
};

button_state_p btn_status =  BUTTON_RELEASED;
Std_ReturnType ret = E_NOT_OK;

int main() {
    app_intialize();
    
    while(1){
    }
    return (EXIT_SUCCESS);
}


void app_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_intialize();
}