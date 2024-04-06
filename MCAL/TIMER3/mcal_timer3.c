/*
* mcal_timer3.c
*   
*  Created on: 5/4/2024
*/


/* INCLUDS */

#include "mcal_timer3.h"

/************* randoms ****************/

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR3_InterruptHandler)(void) = NULL;
#endif

static uint16 timer3_preload = ZERO_INIT;

/************* helper functions declerations ****************/
static inline void Timer3_Mode_Select(const timer3_config_t *timer);


/************* main functions ****************/

Std_ReturnType Timer3_Init  (const timer3_config_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* disable timer3 */
        TIMER3_DISABLE();
        /* prescaler configuration */
        TIMER3_PRESCALER_SELECT(timer->timer3_prescaler_value);
        /* mode : counter or timer */
        Timer3_Mode_Select(timer);
        /* load the timer1 register if 8 bit is enabled*/
        TMR3H = (timer->timer3_preload_value) >> 8;
        TMR3L = (uint8)(timer->timer3_preload_value);
        /* save the preloaded value for interrupt purpose "to use this value in TIMER3_ISR" */
        timer3_preload = timer->timer3_preload_value;
        /* interrupt config */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
        TIMER3_InterruptFlagClear();
        TMR3_InterruptHandler = timer->TMR3_InterruptHandler;
        /* interrupt with periority config */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer->priority){
            INTERRUPT_globalInterruptEnableHigh();
            TIMER3_InterruptPriorityHIGH();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer->priority){
            INTERRUPT_globalInterruptEnableHigh();
            TIMER3_InterruptPriorityLOW();
        }
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        /* enable timer3 */ 
        TIMER3_ENABLE();
    }

    return ret;
}

Std_ReturnType Timer3_DeInit(const timer3_config_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* disable timer3 */
        TIMER3_DISABLE();
        /* disable interrupt */
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_InterruptEnable();
#endif
    }
    return ret;
}

Std_ReturnType Timer3_Write_Value(const timer3_config_t *timer, uint16 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR3H = (value) >> 8;
        TMR3L = (uint8)(value);
    }

    return ret;
}

Std_ReturnType Timer3_Read_Value (const timer3_config_t *timer, uint16 *value){
    Std_ReturnType ret = E_OK;
    uint8 l_high = ZERO_INIT , l_low = ZERO_INIT;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        l_low  = TMR3L;
        l_high = TMR3H;
        *value = (uint16)((TMR3H << 8) + TMR3L);
    }

    return ret;
}



/************* helper functions ****************/
static inline void Timer3_Mode_Select(const timer3_config_t *timer){
    if(TIMER3_TIMER_MODE  == timer->timer3_mode){
        TIMER3_CLOCK_SOURCE_INTERNAL_TIMER_MODE();
    }
    else if(TIMER3_COUNTER_MODE == timer->timer3_mode){
        TIMER3_CLOCK_SOURCE_EXTERNAL_COUNTER_MODE();
        if(TIMER3_SYNC_COUNTER_MODE == timer->timer3_counter_mode){
            TIMER3_SYNC_FOR_COUNTER_MODE();
        }
        else if(TIMER3_ASYNC_COUNTER_MODE == timer->timer3_counter_mode){
            TIMER3_ASYNC_FOR_COUNTER_MODE();
        }
        else{ /* nothing */ }
    }
    else{ /* nothing */ }
}


/************* isr function ****************/
void TIMER3_ISR(void){
    /* clear flag */
    TIMER3_InterruptFlagClear();
    /* code  */
    TMR3H = (timer3_preload) >> 8;
    TMR3L = (uint8)(timer3_preload);
    /* call back */
    if(TMR3_InterruptHandler){ TMR3_InterruptHandler(); } 

}