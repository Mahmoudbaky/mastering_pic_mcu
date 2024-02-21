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

/* MACRO DECLARATIONS */

/* MACRO FUNTIONS DECLARATIONS */

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */
extern pin_config_p pin;
extern chr_lcd_4bit_t lcd_1;
extern chr_lcd_8bit_t lcd_2;
/* FUNTIONS DECLARATIONS */

void app_intialize(void);

#endif	/* APP_H */

