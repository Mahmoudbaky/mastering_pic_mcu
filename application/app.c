/* 
 * File:   app.h
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