/* 
 * File:   app.c
 * Author: houda
 *
 * Created on February 18, 2024, 3:42 PM
 */

#include "app.h"

void timer_isr_fun(void);

pin_config_p pin_1 = {
    .pin       = PIN_0,
    .port      = PORTC_P,
    .direction = PIC_OUTPUT,
    .logic     = PIC_LOW
};

timer1_config_t timer1_obj = {
    .timer1_callback = timer_isr_fun,
    .clock_source  = TIMER1_INTERNAL_CLOCK,
    .timer1_osc_en = TIMER1_OSC_DISABLE,
    .preloaded_value = 3036,
    .prescaler = TIMER1_PRESCALER_8
    //.read_write_mode = TIMER1_16BIT_READ_WRITE  
};

/*
timer_0_config_t timer2_obj = {
    .preloaded_value         = 3036,
    .prescaler_enable        = TIMER_0_PRESCALER_ENABLE_CFG,
    .prescaler_value         = TIMER_0_PRESCALER_32,
    .Timer0_InterruptHandler = timer_isr_fun,
    .timer0_mode             = TIMER0_TIMER_MODE,
    .timer0_register_size    = TIMER0_8BIT_REGISTER_MODE
};
*/

uint16 lol = 0;

Std_ReturnType ret = E_NOT_OK;

int main() {

    app_intialize();
    
    while(1){
        
     
    }
    return (EXIT_SUCCESS);
}


void timer_isr_fun(void){
    lol ++;
    gpio_pin_toggle_logic(&pin_1);
}

void app_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = timer1_Init(&timer1_obj);
    ret = gpio_pin_initialization (&pin_1);
    ecu_intialize();
}