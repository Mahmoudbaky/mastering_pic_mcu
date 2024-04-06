/*
* mcal_timer2.c
*   
*  Created on: 5/4/2024
 * 
 *
*/

/* INCLUDS */

#include "mcal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*TMR2_InterruptHandler)(void) = NULL;
#endif

static uint8 timer2_preload = ZERO_INIT;


/* main functions */ 

Std_ReturnType timer2_Init  (timer2_config_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* disable timer2 */
        TIMER2_ENABLE();
        /* prescaler configuration */
        TIMER2_PRESCALER_SELECT(timer->prescaler);
        /* postscaler configuration */
        TIMER2_POSTSCALER_SELECT(timer->Postscale);
        /* load the timer2 register */
        TMR2 = timer->preloaded_value;
        /* save the preloaded value for interrupt purpose "to use this value in TIMER2_ISR" */
        timer2_preload = timer->preloaded_value;
        /* Interrupt Configurations */
#if TIMER2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        TIMER2_InterruptEnable();
        TIMER2_InterruptFlagClear();
        TMR2_InterruptHandler = timer->timer2_callback;
        /* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer->interrupt_priority){
            INTERRUPT_globalInterruptEnableHigh();
            TIMER2_InterruptPriorityHIGH();
        }
        else if(INTERRUPT_LOW_PRIORITY == timer->interrupt_priority){
            INTERRUPT_globalInterruptEnableLow();
            TIMER2_InterruptPriorityLOW();
        }
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        /* enable timer2 */
        TIMER2_ENABLE();


    }
    return ret;
}                    

Std_ReturnType timer2_DeInit(timer2_config_t *timer){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        /* disable timer2 */
        TIMER2_ENABLE();
        /* disable interrupt */
    #if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        TIMER2_InterruptDisable();
    #endif
    }
    return ret;
}          

Std_ReturnType timer2_write_value (timer2_config_t *timer, uint8 value){
    Std_ReturnType ret = E_OK;
    if(NULL == timer){
        ret = E_NOT_OK;
    }
    else{
        TMR2 = value;
    }
    return ret;
}     

Std_ReturnType timer2_read_value  (timer2_config_t *timer, uint8 *value){
    Std_ReturnType ret = E_OK;
    if((NULL == timer) || (NULL == value)){
        ret = E_NOT_OK;
    }
    else{
        *value = TMR2;
    }
    return ret;
}


// timer2 isr :
void TIMER2_ISR(void){
    /* clear flag */
    TIMER2_InterruptFlagClear();
    /* code  */
    TMR2 = timer2_preload;
    /* call back */
    if(TMR2_InterruptHandler){ TMR2_InterruptHandler(); }
}