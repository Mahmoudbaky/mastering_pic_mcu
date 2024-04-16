/* 
 * File:   app.c
 * Author: houda
 *
 * Created on February 18, 2024, 3:42 PM
 */

#include "app.h"

void isr1_fun(void);
void isr2_fun(void);

volatile uint16 isr_flage1 = ZERO_INIT;
volatile uint16 isr_flage2 = ZERO_INIT;

volatile uint8 rx_data = ZERO_INIT;

pin_config_p led_1 = {
    .port = PORTD_P,
    .pin  = PIN_0,
    .logic= PIC_LOW,
    .direction = PIC_OUTPUT
};


eusart_obj_t eusart_obj =  {
    .eusart_baudrate_value           = 9600,
    .eusart_baudrate_equation_select = BUADRATE_ASYNC_8BIT_LOW_SPEED,

    .eusart_tx_cfg.eusart_tx_9bit_enable      = EUSART_ASYNC_TX_9BIT_DISABLE,
    .eusart_tx_cfg.eusart_tx_enable           = EUSART_ASYNC_TX_ENABLE,
    .eusart_tx_cfg.eusart_tx_interrupt_enable = EUSART_ASYNC_TX_INTERRUPT_ENABLE,
    .eusart_tx_isr                            = NULL,

    .eusart_rx_cfg.eusart_rx_9bit_enable      = EUSART_ASYNC_RX_9BIT_DISABLE,
    .eusart_rx_cfg.eusart_rx_enable           = EUSART_ASYNC_RX_ENABLE,
    .eusart_rx_cfg.eusart_rx_interrupt_enable = EUSART_ASYNC_RX_INTERRUPT_ENABLE,
    .eusart_rx_isr                            = isr2_fun
};



Std_ReturnType ret = E_NOT_OK;

int main() {

    app_intialize();
    ret = EUSART_WriteByte_blocking('a');

    while(1){
    
    }
    return (EXIT_SUCCESS);
}


void app_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = EUSART_Async_Init(&eusart_obj);
    ret = gpio_pin_initialization(&led_1);
    // ecu_intialize();
}

void isr1_fun(void){ 

}

void isr2_fun(void){
    Std_ReturnType ret = E_NOT_OK;
    EUSART_ReadByte_nonblocking(&rx_data);
    if ('c' == rx_data){
        ret = gpio_pin_write_logic(&led_1, PIC_HIGH);
        ret = EUSART_WriteByte_blocking('b');
        __delay_ms(250);
    }
    if ('d' == rx_data){
        ret = gpio_pin_write_logic(&led_1, PIC_LOW);
        ret = EUSART_WriteByte_blocking('a');
        __delay_ms(250);
    }
}