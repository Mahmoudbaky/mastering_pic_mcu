/* 
 * File:   ecu_config.c
 * Author: houda
 *
 * Created on February 20, 2024, 1:02 PM
 */

#include "ecu_config.h"

pin_config_p pin = {
    .port      = PORTC_P,
    .pin       = PIN_1,
    .direction = PIC_OUTPUT,
    .logic     = PIC_LOW
};

chr_lcd_4bit_t lcd_1 = {
    .lcd_rs.port      = PORTC_P,
    .lcd_rs.pin       = PIN_0,
    .lcd_rs.direction = PIC_OUTPUT,
    .lcd_rs.logic     = PIC_LOW,
    .lcd_en.port      = PORTC_P,
    .lcd_en.pin       = PIN_1,
    .lcd_en.direction = PIC_OUTPUT,
    .lcd_en.logic     = PIC_LOW,
    .lcd_data[0].port      = PORTC_P,
    .lcd_data[0].pin       = PIN_2,
    .lcd_data[0].direction = PIC_OUTPUT,
    .lcd_data[0].logic     = PIC_LOW,
    .lcd_data[1].port      = PORTC_P,
    .lcd_data[1].pin       = PIN_3,
    .lcd_data[1].direction = PIC_OUTPUT,
    .lcd_data[1].logic     = PIC_LOW,
    .lcd_data[2].port      = PORTC_P,
    .lcd_data[2].pin       = PIN_4,
    .lcd_data[2].direction = PIC_OUTPUT,
    .lcd_data[2].logic     = PIC_LOW,
    .lcd_data[3].port      = PORTC_P,
    .lcd_data[3].pin       = PIN_5,
    .lcd_data[3].direction = PIC_OUTPUT,
    .lcd_data[3].logic     = PIC_LOW   
};



chr_lcd_8bit_t lcd_2 = {
    .lcd_rs.port      = PORTC_P,
    .lcd_rs.pin       = PIN_6,
    .lcd_rs.direction = PIC_OUTPUT,
    .lcd_rs.logic     = PIC_LOW,
    .lcd_en.port      = PORTC_P,
    .lcd_en.pin       = PIN_7,
    .lcd_en.direction = PIC_OUTPUT,
    .lcd_en.logic     = PIC_LOW,
    .lcd_data[0].port      = PORTD_P,
    .lcd_data[0].pin       = PIN_0,
    .lcd_data[0].direction = PIC_OUTPUT,
    .lcd_data[0].logic     = PIC_LOW,
    .lcd_data[1].port      = PORTD_P,
    .lcd_data[1].pin       = PIN_1,
    .lcd_data[1].direction = PIC_OUTPUT,
    .lcd_data[1].logic     = PIC_LOW,
    .lcd_data[2].port      = PORTD_P,
    .lcd_data[2].pin       = PIN_2,
    .lcd_data[2].direction = PIC_OUTPUT,
    .lcd_data[2].logic     = PIC_LOW,
    .lcd_data[3].port      = PORTD_P,
    .lcd_data[3].pin       = PIN_3,
    .lcd_data[3].direction = PIC_OUTPUT,
    .lcd_data[3].logic     = PIC_LOW,
    .lcd_data[4].port      = PORTD_P,
    .lcd_data[4].pin       = PIN_4,
    .lcd_data[4].direction = PIC_OUTPUT,
    .lcd_data[4].logic     = PIC_LOW,
    .lcd_data[5].port      = PORTD_P,
    .lcd_data[5].pin       = PIN_5,
    .lcd_data[5].direction = PIC_OUTPUT,
    .lcd_data[5].logic     = PIC_LOW,
    .lcd_data[6].port      = PORTD_P,
    .lcd_data[6].pin       = PIN_6,
    .lcd_data[6].direction = PIC_OUTPUT,
    .lcd_data[6].logic     = PIC_LOW,
    .lcd_data[7].port      = PORTD_P,
    .lcd_data[7].pin       = PIN_7,
    .lcd_data[7].direction = PIC_OUTPUT,
    .lcd_data[7].logic     = PIC_LOW   
};

button_p btn_1 = {
    .button_state         = BUTTON_RELEASED,
    .button_connection    = BUTTON_ACTIVE_HIGH,
    .button_pin.direction = PIC_INPUT,
    .button_pin.port      = PORTC_P,
    .button_pin.pin       = PIN_0,
    .button_pin.logic     = PIC_LOW
};



void ecu_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    //ret = lcd_4bit_intialize(&lcd_1);
    //ret = lcd_8bit_intialize(&lcd_2);
    ret = gpio_pin_initialization(&pin);
    ret = button_initialize (&btn_1);
}
