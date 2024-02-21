/* 
 * File:   mcal_gpio.h
 * Author: houda
 *
 * Created on February 18, 2024, 3:54 PM
 */

#ifndef MCAL_GPIO_H
#define	MCAL_GPIO_H

/* INCLUDS */
#include "mcal_gpio_cfg.h"
#include "../../MCAL/mcal_std_types.h"
#include "pic18f4620.h"
#include "../../MCAL/device_config.h"

/* MACRO DECLARATIONS */

#define BIT_MASK            (uint8)0x01

#define MAX_NUMBER_OF_BINS  8
#define MAX_NUMBER_OF_PORTS 5

/* MACRO FUNTIONS DECLARATIONS */

#define HWREG8(_X)    (*((volatile uint8 *)(_X)))      // to convert the address to a pionter (usint casting)

#define SET_BIT(REG_ADD,BIT_POSS)     (REG_ADD |=  (BIT_MASK << BIT_POSS))
#define CLEAR_BIT(REG_ADD,BIT_POSS)   (REG_ADD &= ~(BIT_MASK << BIT_POSS))
#define TOGGLE_BIT(REG_ADD,BIT_POSS)  (REG_ADD ^=  (BIT_MASK << BIT_POSS))
#define BIT_READ(REG_ADD,BIT_POSS)    ((REG_ADD >> BIT_POSS) & BIT_MASK)


/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum {
    PIC_LOW = 0,
    PIC_HIGH
}logic_p;

typedef enum {
    PIC_OUTPUT = 0,
    PIC_INPUT
}direction_p;

typedef enum {
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
}pin_index_p;

typedef enum {
    PORTA_P = 0,
    PORTB_P,
    PORTC_P,
    PORTD_P,
    PORTE_P
}port_index_p;

typedef struct {
    uint8 port      : 3;
    uint8 pin       : 3;
    uint8 direction : 1;
    uint8 logic     : 1;
}pin_config_p;

/* FUNTIONS DECLARATIONS */

Std_ReturnType gpio_pin_direction_initialization (const pin_config_p *_pin_config);
Std_ReturnType gpio_pin_get_direction_status     (const pin_config_p *_pin_config , direction_p *_direction_status);
Std_ReturnType gpio_pin_write_logic              (const pin_config_p *_pin_config , logic_p logic);
Std_ReturnType gpio_pin_read_logic               (const pin_config_p *_pin_config , logic_p *logic);
Std_ReturnType gpio_pin_toggle_logic             (const pin_config_p *_pin_config);
Std_ReturnType gpio_pin_initialization           (const pin_config_p *_pin_config);


Std_ReturnType gpio_port_direction_initialization      (port_index_p port , uint8 direction);
Std_ReturnType gpio_port_get_direction_status          (port_index_p port , uint8 *direction);
Std_ReturnType gpio_port_write_logic                   (port_index_p port , uint8 logic);
Std_ReturnType gpio_port_read_logic                    (port_index_p port , uint8 *logic);
Std_ReturnType gpio_port_toggle_logic                  (port_index_p port);





#endif	/* MCAL_GPIO_H */

