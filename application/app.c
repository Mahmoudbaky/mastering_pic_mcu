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

pin_config_p PIN_C3 = {
    .direction = PIC_OUTPUT,
    .logic     = PIC_LOW,
    .pin       = PIN_3,
    .port      = PORTC_P
};


void ISR0 (void){
   gpio_pin_toggle_logic(&PIN_C0);
   __delay_ms(250);
}

void ISR1 (void){
   gpio_pin_toggle_logic(&PIN_C1);
   __delay_ms(250);
}

void ISR2 (void){
   gpio_pin_toggle_logic(&PIN_C2);
   __delay_ms(250);
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
    .priority             = INTERRUPT_LOW_PRIORITY,
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


void RBX_4_HIGH(void){
    gpio_pin_write_logic(&PIN_C0 , PIC_HIGH);
}

void RBX_4_LOW(void){
    gpio_pin_write_logic(&PIN_C0 , PIC_HIGH);
}

void RBX_5_HIGH (void){
    gpio_pin_write_logic(&PIN_C1 , PIC_HIGH);
}
void RBX_5_LOW (void){
    gpio_pin_write_logic(&PIN_C1 , PIC_HIGH);
}
        
void RBX_6_HIGH (void){
    gpio_pin_write_logic(&PIN_C2 , PIC_HIGH);
}
void RBX_6_LOW (void){
    gpio_pin_write_logic(&PIN_C2 , PIC_HIGH);
}

void RBX_7_HIGH (void){
    gpio_pin_write_logic(&PIN_C3 , PIC_HIGH);
}
void RBX_7_LOW (void){
    gpio_pin_write_logic(&PIN_C3 , PIC_HIGH);
}

interrupt_RBx_t RBX_4 = {
    .EXT_InterruptHandler_HIGH = RBX_4_HIGH,
    .EXT_InterruptHandler_LOW  = RBX_4_LOW,
    .priority                  = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction         = PIC_INPUT,
    .mcu_pin.pin               = PIN_4,
    .mcu_pin.port              = PORTB_P  
};

interrupt_RBx_t RBX_5 = {
    .EXT_InterruptHandler_HIGH = RBX_5_HIGH,
    .EXT_InterruptHandler_LOW  = RBX_5_LOW,
    .priority                  = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction         = PIC_INPUT,
    .mcu_pin.pin               = PIN_5,
    .mcu_pin.port              = PORTB_P  
};

interrupt_RBx_t RBX_6 = {
    .EXT_InterruptHandler_HIGH = RBX_6_HIGH,
    .EXT_InterruptHandler_LOW  = RBX_6_LOW,
    .priority                  = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction         = PIC_INPUT,
    .mcu_pin.pin               = PIN_6,
    .mcu_pin.port              = PORTB_P  
};

interrupt_RBx_t RBX_7 = {
    .EXT_InterruptHandler_HIGH = RBX_7_HIGH,
    .EXT_InterruptHandler_LOW  = RBX_7_LOW,
    .priority                  = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.direction         = PIC_INPUT,
    .mcu_pin.pin               = PIN_7,
    .mcu_pin.port              = PORTB_P  
};


int main() {
    //app_intialize();
    
    ret = Interrupt_INTx_Init(&INT_0);
    ret = Interrupt_INTx_Init(&INT_1);
    ret = Interrupt_INTx_Init(&INT_2);
    
    ret = Interrupt_RBx_Init(&RBX_4);
    ret = Interrupt_RBx_Init(&RBX_5);
    ret = Interrupt_RBx_Init(&RBX_6);
    ret = Interrupt_RBx_Init(&RBX_7);
    
    ret = gpio_pin_initialization(&PIN_C0);
    ret = gpio_pin_initialization(&PIN_C1);
    ret = gpio_pin_initialization(&PIN_C2);
    ret = gpio_pin_initialization(&PIN_C3);
    while(1){
        
        
    }
    return (EXIT_SUCCESS);
}


void app_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ecu_intialize();
}