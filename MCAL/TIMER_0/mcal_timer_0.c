/*
 * mcal_timer_0.c
 *
 *  Created on: Sep 1, 2019
 */

#include "mcal_timer_0.h"

#if TIMER0_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
static void (*timer0_callback)(void) = NULL;
#endif

static uint16 timer0_preloaded = 0;

/* helper functions declerations */
static inline void Timer0_Prescaler_Config(const timer_0_config_t *timer_0);
static inline void Timer0_Reg_Size_Config (const timer_0_config_t *timer_0);
static inline void Timer0_Mode_Config     (const timer_0_config_t *timer_0);


/* main APIs */
Std_ReturnType Timer_0_Init(const timer_0_config_t *timer_0)
{
    Std_ReturnType ret = E_OK;
    if (timer_0 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* disable timer0 */
        TIMER_0_DISABLE();
        /* prescaler configuration */
        Timer0_Prescaler_Config(timer_0);
        /* mode : counter or timer */
        Timer0_Mode_Config(timer_0);
        /* register size select */
        Timer0_Reg_Size_Config(timer_0);
        /* load the timer0 register */
        TMR0H = (uint8)(timer_0->preloaded_value >> 8);
        TMR0L = (uint8)(timer_0->preloaded_value);
        /* save the preloaded value for interrupt purpose "to use this value in TIMER0_ISR" */
        timer0_preloaded = timer_0->preloaded_value;
        /* interrupt config */
#if TIMER0_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        TIMER0_InterruptEnable();
        TIMER0_InterruptFlagClear();
        timer0_callback = timer_0->Timer0_InterruptHandler;
         /* interrupt with periorit config */
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_HIGH_PRIORITY == timer_0->priority){
            INTERRUPT_globalInterruptEnableHigh();
            TIMER0_InterruptPriorityHIGH();
            
        }
        else if(INTERRUPT_LOW_PRIORITY == timer_0->priority){
            INTERRUPT_globalInterruptEnableLow();
            TIMER0_InterruptPriorityLOW();
            
        }
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif

#endif
        TIMER_0_ENABLE();
    }
    return ret;
}

Std_ReturnType Timer_0_DeInit(const timer_0_config_t *timer_0)
{
    Std_ReturnType ret = E_OK;
    if (timer_0 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TIMER_0_DISABLE();
#if TIMER0_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        TIMER0_InterruptDisable();
#endif

    }
    return ret;
}

Std_ReturnType Timer_0_Write(const timer_0_config_t *timer_0, uint16 timer0_value)
{
    Std_ReturnType ret = E_OK;
    if (timer_0 == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TMR0H = (uint8)(timer0_value >> 8);
        TMR0L = (uint8)(timer0_value);
    }
    return ret;
}

Std_ReturnType Timer_0_Read(const timer_0_config_t *timer_0, uint16 *timer0_value)
{
    Std_ReturnType ret = E_OK;
    uint8 tmr0l = 0 , tmr0h = 0;
    if ((timer_0 == NULL) || (timer0_value == NULL))
    {
        ret = E_NOT_OK;
    }
    else
    {   
        tmr0l = TMR0L;
        tmr0h = TMR0H;
        *timer0_value = (uint16)((tmr0h << 8) + tmr0l);
    }
    return ret;
}

/* timer0 isr */
void TIMER0_ISR(void)
{
    /* clear flag */
    TIMER0_InterruptFlagClear();
    /* we must reload the timer with preloaded value */
    TMR0H = (uint8)(timer0_preloaded >> 8);
    TMR0L = (uint8)(timer0_preloaded);
    /* call the callback function */
    if (timer0_callback)
    {
        timer0_callback();
    }
}


/* helper functions implementations */
static inline void Timer0_Prescaler_Config(const timer_0_config_t *timer_0)
{
        if (TIMER_0_PRESCALER_ENABLE_CFG == timer_0->prescaler_enable)
        {
            TIMER_0_PRESCALER_ENABLE();
            T0CONbits.T0PS = timer_0->prescaler_value;
        }
        else if (TIMER_0_PRESCALER_DISABLE_CFG == timer_0->prescaler_enable)
        {
            TIMER_0_PRESCALER_DISABLE();
        }
        else
        { /* Nothing */}
}

static inline void Timer0_Reg_Size_Config(const timer_0_config_t *timer_0){
    if (TIMER0_8BIT_REGISTER_MODE == timer_0->timer0_register_size)
    {
        TIMER_0_8_BIT_MODE();
    }
    else if (TIMER0_16BIT_REGISTER_MODE == timer_0->timer0_register_size)
    {
        TIMER_0_16_BIT_MODE();
    }
    else
    { /* Nothing */}
}

static inline void Timer0_Mode_Config(const timer_0_config_t *timer_0){
    if (TIMER0_TIMER_MODE == timer_0->timer0_mode)
    {
        TIMER_0_INTERNAL_CLOCK_TIMER();
    }
    else if (TIMER0_COUNTER_MODE == timer_0->timer0_mode)
    {
        TIMER_0_EXTERNAL_CLOCK_COUNTER();
        if(TIMER_0_RISING_EDGE_SFG == timer_0->timer0_counter_edge){
            TIMER_0_RISING_EDGE();
        }
        else if(TIMER_0_FALLING_EDGE_SFG == timer_0->timer0_counter_edge){
            TIMER_0_FALLING_EDGE();

        }
        else{ /* Nothing */}
    }
    else
    { /* Nothing */}
}