/* 
 * File:   app.c
 * Author: houda
 *
 * Created on February 18, 2024, 3:42 PM
 */

#include "app.h"

//button_state_p btn_status =  BUTTON_RELEASED;
Std_ReturnType ret = E_NOT_OK;

pin_config_p PIN_C0 = {
    .direction = PIC_OUTPUT,
    .logic     = PIC_LOW,
    .pin       = PIN_0,
    .port      = PORTC_P
};

pin_config_p PIN_C1 = {
    .direction = PIC_OUTPUT,
    .logic     = PIC_LOW,
    .pin       = PIN_1,
    .port      = PORTC_P
};

pin_config_p PIN_C2 = {
    .direction = PIC_OUTPUT,
    .logic     = PIC_LOW,
    .pin       = PIN_2,
    .port      = PORTC_P
};


void ISR0 (void){
   gpio_pin_toggle_logic(&PIN_C0);
}

void ISR1 (void){
   gpio_pin_toggle_logic(&PIN_C1);
}

void ISR2 (void){
   gpio_pin_toggle_logic(&PIN_C2);
}

interrupt_INTx_t INT_0 = {
    .EXT_InterruptHandler = ISR0,
    .edge                 = INTERRUPT_RISING_EDGE,
    .priority             = INTERRUPT_HIGH_PRIORITY,
    .source               = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.direction    = PIC_INPUT,
    .mcu_pin.pin          = PORTB_P,
    .mcu_pin.pin          = PIN_0
};

interrupt_INTx_t INT_1 = {
    .EXT_InterruptHandler = ISR1,
    .edge                 = INTERRUPT_FALLING_EDGE,
    .priority             = INTERRUPT_HIGH_PRIORITY,
    .source               = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.direction    = PIC_INPUT,
    .mcu_pin.pin          = PORTB_P,
    .mcu_pin.pin          = PIN_1
};

interrupt_INTx_t INT_2 = {
    .EXT_InterruptHandler = ISR2,
    .edge                 = INTERRUPT_RISING_EDGE,
    .priority             = INTERRUPT_HIGH_PRIORITY,
    .source               = INTERRUPT_EXTERNAL_INT2,
    .mcu_pin.direction    = PIC_INPUT,
    .mcu_pin.pin          = PORTB_P,
    .mcu_pin.pin          = PIN_2
};


int main() {
    //app_intialize();
    
    ret = Interrupt_INTx_Init(&INT_0);
    ret = Interrupt_INTx_Init(&INT_1);
    ret = Interrupt_INTx_Init(&INT_2);
    
    ret = gpio_pin_initialization(&PIN_C0);
    ret = gpio_pin_initialization(&PIN_C1);
    ret = gpio_pin_initialization(&PIN_C2);
    
    while(1){
        
        
    }
    return (EXIT_SUCCESS);
}


void app_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_intialize();
}