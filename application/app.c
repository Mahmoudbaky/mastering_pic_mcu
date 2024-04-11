/* 
 * File:   app.c
 * Author: houda
 *
 * Created on February 18, 2024, 3:42 PM
 */

#include "app.h"

void isr1_fun(void);
void isr2_fun(void);

volatile uint8 isr_flage1 = 0;
volatile uint8 isr_flage2 = 0;

ccp_config_t ccp1_obj = {
    .ccp_pick          = CCP1_PICK,
    //.pwm_freq          = 20000,
    //.Postscale         = CCP_TIMER2_POSTSCALE_1,
    //.prescaler         = CCP_TIMER2_PRESCALER_1,
    .ccp_mode         = CCP_CAPTURE_MODE,
    .ccp_mode_variant = CCP_CAPTURE_MODE_RISING_EDGE,
    .pin.port      = PORTC_P,
    .pin.pin       = PIN_2,
    .pin.direction = PIC_INPUT,
    .pin.logic     = PIC_HIGH,
    .ccp_timer_mode = CCP1_CCP2_TIMER3,
    .ccp1_isr     = isr1_fun
};



timer3_config_t timer_obj = {
    .TMR3_InterruptHandler  = isr2_fun,
    .timer3_mode            = TIMER3_TIMER_MODE,
    .timer3_preload_value   = 0,
    .timer3_prescaler_value = prescaler_1,
    .timer3_reg_wr_mode     = TIMER3_RW_REG_8Bit_MODE
};



Std_ReturnType ret = E_NOT_OK;

int main() {

    app_intialize();

    
    
    while(1){
        
     
    }
    return (EXIT_SUCCESS);
}


void isr_fun(void){
    
}

void app_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = ccp_Init   (&ccp1_obj);
    ret = Timer3_Init(&timer_obj);
    // ecu_intialize();
}

void isr1_fun(void){
    isr_flage1++;
}
void isr2_fun(void){
    isr_flage2++;
}