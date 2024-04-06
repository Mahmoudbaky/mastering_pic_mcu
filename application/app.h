/* 
 * File:   app.h
 * Author: houda
 *
 * Created on February 18, 2024, 3:42 PM
 */

#ifndef APP_H
#define	APP_H

/* INCLUDS */
#include "../ecu/ecu_config.h"

#include "../MCAL/INTERRUPT/mcal_external_interrupt.h"
#include "../MCAL/INTERRUPT/mcal_internal_interrupt.h"
#include "../MCAL/EEPROM/mcal_eeprom.h"
#include "../MCAL/ADC/mcal_adc.h"
#include "../MCAL/TIMER_0/mcal_timer_0.h"
#include "../MCAL/TIMER1/mcal_timer1.h"
/* MACRO DECLARATIONS */



/* MACRO FUNTIONS DECLARATIONS */

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */
extern pin_config_p pin;
extern chr_lcd_4bit_t lcd_1;
extern chr_lcd_8bit_t lcd_2;
extern button_p btn_1;

/* FUNTIONS DECLARATIONS */

void app_intialize(void);

#endif	/* APP_H */

