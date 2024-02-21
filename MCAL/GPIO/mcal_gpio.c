/* 
 * File:   mcal_gpio.c
 * Author: houda
 *
 * Created on February 18, 2024, 3:54 PM
 */


#include "mcal_gpio.h"

volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
volatile uint8 *port_registers[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};
volatile uint8 *lat_registers [] = {&LATA ,&LATB ,&LATC ,&LATD ,&LATE};


#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_direction_initialization      (const pin_config_p *_pin_config){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin_config) || (_pin_config->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        switch(_pin_config->direction){
            case PIC_OUTPUT :
                CLEAR_BIT((*tris_registers[_pin_config->port]),_pin_config->pin);
                break;
            case PIC_INPUT :
                SET_BIT((*tris_registers[_pin_config->port]),_pin_config->pin);
                break;
            default: ret = E_NOT_OK;
        } 
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_get_direction_status (const pin_config_p *_pin_config  , direction_p *_direction_status){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin_config) || (NULL == _direction_status) || (_pin_config->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        *_direction_status = BIT_READ((*tris_registers[_pin_config->port]),_pin_config->pin);
    }
    
    return ret;
}
#endif

#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_write_logic          (const pin_config_p *_pin_config , logic_p logic){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin_config) || (_pin_config->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        switch(logic){
            case PIC_LOW :
                CLEAR_BIT((*lat_registers[_pin_config->port]),_pin_config->pin);
                break;
            case PIC_HIGH :
                SET_BIT((*lat_registers[_pin_config->port]),_pin_config->pin);
                break;
            default: ret = E_NOT_OK;
        } 
    }
    return ret;       
}
#endif

#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_read_logic           (const pin_config_p *_pin_config , logic_p *logic){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin_config) || (NULL == logic) || (_pin_config->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        *logic = BIT_READ((*port_registers[_pin_config->port]),_pin_config->pin);
    }
    
    return ret;  
}
#endif

#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_toggle_logic         (const pin_config_p *_pin_config){
    Std_ReturnType ret = E_OK ;
    if ((NULL == _pin_config) || (_pin_config->pin > (MAX_NUMBER_OF_BINS-1))){
        ret = E_NOT_OK;
    }
    else{
        TOGGLE_BIT((*lat_registers[_pin_config->port]),_pin_config->pin);
    }
    return ret;
}
#endif

#if GPIO_PIN_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_pin_initialization(const pin_config_p *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > MAX_NUMBER_OF_BINS-1){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialization(_pin_config);
        ret = gpio_pin_write_logic   (_pin_config, _pin_config->logic);
    }
    return ret;
}
#endif

////////////////////////////////////////////////////////////////////////////////

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_direction_initialization      (port_index_p port , uint8 direction){
    Std_ReturnType ret = E_OK ;
    if ((port > (MAX_NUMBER_OF_PORTS-1))){
        ret = E_NOT_OK;
    }
    else{
        *tris_registers[port] = direction; 
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_get_direction_status(port_index_p port , uint8 *direction){
    Std_ReturnType ret = E_OK ;
    if ((port > (MAX_NUMBER_OF_PORTS-1)) || (NULL == direction)){
        ret = E_NOT_OK;
    }
    else{
        *direction = *tris_registers[port];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_write_logic         (port_index_p port , uint8 logic){
    Std_ReturnType ret = E_OK ;
    if ((port > (MAX_NUMBER_OF_PORTS-1))){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers[port] = logic;
    } 
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_read_logic          (port_index_p port , uint8 *logic){
    Std_ReturnType ret = E_OK ;
    if ((port > (MAX_NUMBER_OF_PORTS-1)) || (NULL == logic)){
        ret = E_NOT_OK;
    }
    else{
        *logic = *lat_registers[port];
    }
    return ret;
}
#endif

#if GPIO_PORT_CONFIGURATION == CONFIG_ENABLE
Std_ReturnType gpio_port_toggle_logic        (port_index_p port){
    Std_ReturnType ret = E_OK ;
    if ((port > (MAX_NUMBER_OF_PORTS-1))){
        ret = E_NOT_OK;
    }
    else{
        *lat_registers [port] ^= 0xFF;
    }
    return ret;
}
#endif