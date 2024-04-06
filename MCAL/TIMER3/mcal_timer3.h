/*
* mcal_timer3.h
*   
*  Created on: 5/4/2024
*/



/* INCLUDS */

#include "../GPIO/mcal_gpio.h"
#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../MCAL/INTERRUPT/mcal_internal_interrupt.h"

/* MACRO DECLARATIONS */

/* Timer3 Clock Source (Timer or Counter) */
#define TIMER3_COUNTER_MODE            1
#define TIMER3_TIMER_MODE              0
/* Timer3 External Clock Input Synchronization */
#define TIMER3_ASYNC_COUNTER_MODE      1
#define TIMER3_SYNC_COUNTER_MODE       0
/* Timer3 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8Bit_MODE        0
#define TIMER3_RW_REG_16Bit_MODE       1



/* MACRO FUNTIONS DECLARATIONS */

/* Enable or Disable Timer3 Module */
#define TIMER3_ENABLE()     (T3CONbits.TMR3ON = 1) // enable timer3
#define TIMER3_DISABLE()    (T3CONbits.TMR3ON = 0) // disable timer3
/*  Timer3 Clock Source (Timer or Counter) */
#define TIMER3_CLOCK_SOURCE_INTERNAL_TIMER_MODE()    (T3CONbits.TMR3CS = 0)   // Internal clock (FOSC/4)
#define TIMER3_CLOCK_SOURCE_EXTERNAL_COUNTER_MODE()  (T3CONbits.TMR3CS = 1)   // Timer1 oscillator or T13CKI

/*  Timer3 External Clock Input Synchronization */
// WORKS ONLY WHEN TMR3CS = 1 ......
#define TIMER3_SYNC_FOR_COUNTER_MODE()     (T3CONbits.T3SYNC = 0)
#define TIMER3_ASYNC_FOR_COUNTER_MODE()    (T3CONbits.T3SYNC = 1)

/* Timer3 Input Clock Pre-scaler */
#define TIMER3_PRESCALER_SELECT(_PRESCALER)          (T3CONbits.T3CKPS = _PRESCALER)

/* Timer3 16-Bit Read/Write Mode */
#define TIMER3_RW_REG_8BIT_MODE_ENABLE()    (T3CONbits.RD16 = 0)
#define TIMER3_RW_REG_16BIT_MODE_ENABLE()   (T3CONbits.RD16 = 1)
                                                    

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum {
    prescaler_1 = 0,
    prescaler_2,
    prescaler_4,
    prescaler_8
}prescaler_t;

typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* TMR3_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    uint16      timer3_preload_value;
    prescaler_t timer3_prescaler_value;
    uint8       timer3_mode : 1;
    uint8       timer3_counter_mode : 1;
    uint8       timer3_reg_wr_mode : 1;
    uint8       timer3_reserved : 3;
}timer3_config_t;

/* FUNTIONS DECLARATIONS */
Std_ReturnType Timer3_Init  (const timer3_config_t *timer);
Std_ReturnType Timer3_DeInit(const timer3_config_t *timer);
Std_ReturnType Timer3_Write_Value(const timer3_config_t *timer, uint16 value);
Std_ReturnType Timer3_Read_Value (const timer3_config_t *timer, uint16 *value);


