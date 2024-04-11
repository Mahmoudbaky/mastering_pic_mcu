/*
* mcal_timer2.h
*   
*  Created on: 5/4/2024
*/

/* INCLUDS */

#include "../GPIO/mcal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/INTERRUPT/mcal_internal_interrupt.h"

/* MACRO DECLARATIONS */

/* MACRO FUNTIONS DECLARATIONS */

#define TIMER2_ENABLE()     (T2CONbits.TMR2ON = 1) // enable timer2
#define TIMER2_DISABLE()    (T2CONbits.TMR2ON = 0) // disable timer2

#define TIMER2_PRESCALER_SELECT(_PRESCALER) (T2CONbits.T2CKPS = _PRESCALER)

#define TIMER2_POSTSCALER_SELECT(_POSTSCALER) (T2CONbits.TOUTPS = _POSTSCALER)

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */
typedef enum {
    TIMER2_POSTSCALE_1 = 0,   // postscaler is off
    TIMER2_POSTSCALE_2,
    TIMER2_POSTSCALE_3,
    TIMER2_POSTSCALE_4,
    TIMER2_POSTSCALE_5,
    TIMER2_POSTSCALE_6,
    TIMER2_POSTSCALE_7,
    TIMER2_POSTSCALE_8,
    TIMER2_POSTSCALE_9,
    TIMER2_POSTSCALE_10,
    TIMER2_POSTSCALE_11,
    TIMER2_POSTSCALE_12,
    TIMER2_POSTSCALE_13,
    TIMER2_POSTSCALE_14,
    TIMER2_POSTSCALE_15,
    TIMER2_POSTSCALE_16
}Postscale_t;


typedef enum {
    TIMER2_PRESCALER_1 = 0,  // prescaler is off
    TIMER2_PRESCALER_4,
    TIMER2_PRESCALER_16
}timer2_prescaler_t;


typedef struct {
#if TIMER2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
    void (*timer2_callback)(void);  // pointer to function to be called when timer2 overflow
    interrupt_priority_cfg interrupt_priority;  // interrupt priority
#endif
    uint8                   preloaded_value;
    Postscale_t             Postscale;
    timer2_prescaler_t             prescaler;
}timer2_config_t;

/* FUNTIONS DECLARATIONS */

Std_ReturnType timer2_Init  (timer2_config_t *timer);                     // initialize timer2
Std_ReturnType timer2_DeInit(timer2_config_t *timer);                     // deinitialize timer2
Std_ReturnType timer2_write_value (timer2_config_t *timer, uint8 value);  // write value to timer2
Std_ReturnType timer2_read_value  (timer2_config_t *timer, uint8 *value); // read value from timer2