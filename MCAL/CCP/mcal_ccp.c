/*
    * mcal_ccp.c
    *
    *  Created on: 6/4/2024
*/

/* INCLUDS */

#include "mcal_ccp.h"


/************* randoms ****************/
#if CCP1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
    static void (*ccp1_InterruptHandler)(void) = NULL ;
#endif

#if CCP2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
    static void (*ccp2_InterruptHandler)(void) = NULL ;
#endif

/************* helper functions declerations ****************/
static void CCP_Interrupt_Config (const ccp_config_t *ccp);
static void CCP_PWM_Mode_Config  (const ccp_config_t *ccp);
static void CCP_Mode_Timer_Select(const ccp_config_t *ccp);
static Std_ReturnType CCP_Capture_Mode_Config(const ccp_config_t *ccp);
static Std_ReturnType CCP_Compare_Mode_Config(const ccp_config_t *ccp);



/************* main functions ****************/

// INITIALIZATION AND DEINITIALIZATION:

Std_ReturnType ccp_Init  (ccp_config_t *ccp){
    Std_ReturnType ret = E_OK;
    if(NULL == ccp){
        ret = E_NOT_OK;
    }
    else{
        /***  disable ccp ***/

        if     (CCP1_PICK == ccp->ccp_pick){ CCP1_SET_MODE(CCP_DISABLE); }
        else if(CCP2_PICK == ccp->ccp_pick){ CCP2_SET_MODE(CCP_DISABLE); }
        else                               { /* nothing */ }

        /*** set ccp mode ***/

            // CAPTURE MODE:
        if(CCP_CAPTURE_MODE == ccp->ccp_mode){
            CCP_Capture_Mode_Config(ccp);
        }
            // COMPARE MODE:
        else if (CCP_COMPARE_MODE == ccp->ccp_mode){
            CCP_Compare_Mode_Config(ccp);
        }
            // PWM MODE:
#if (CCP1_SELECTED_MODE == CPP_CFG_PWM_MODE) || (CCP2_SELECTED_MODE == CPP_CFG_PWM_MODE)
        else if (CCP_PWM_MODE == ccp->ccp_mode){
            CCP_PWM_Mode_Config(ccp);
        }
#endif

        /*** pin configuration ***/
        ret = gpio_pin_initialization(&(ccp->pin));

        /*** interrupt configuration ***/
        CCP_Interrupt_Config(ccp);


    }
    return ret;
}

Std_ReturnType ccp_DeInit(ccp_config_t *ccp){
    Std_ReturnType ret = E_OK;
    if(NULL == ccp){
        ret = E_NOT_OK;
    }
    else{
        /* disable ccp1 */
        if(CCP1_PICK == ccp->ccp_pick){ 
            /* disable ccp1 */
            CCP1_SET_MODE(CCP_DISABLE); 
            /* interrupt configuration */
#if CCP1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
            CCP1_InterruptDisable();
#endif
            }
        else if(CCP2_PICK == ccp->ccp_pick){
            /* disable ccp2 */
            CCP2_SET_MODE(CCP_DISABLE); 
            /* interrupt configuration */
#if CCP2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
            CCP2_InterruptDisable();
#endif 
            }
        else{ /* nothing */ }

    }
    return ret;
}


// CAPTURE MODE:

#if (CCP1_SELECTED_MODE == CPP_CFG_CAPTURE_MODE) || (CCP2_SELECTED_MODE == CPP_CFG_CAPTURE_MODE)
Std_ReturnType CCP_IsCapturedDataReady    (const ccp_config_t *ccp , uint8 *capture_status){
    Std_ReturnType ret = E_OK;
    if(NULL == capture_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_PICK ==  ccp->ccp_pick){
            if(CCP_CAPTURE_READY == PIR1bits.CCP1IF){
                *capture_status = CCP_CAPTURE_READY;
                CCP1_InterruptFlagClear();
            }
            else if(CCP_CAPTURE_NOT_READY == PIR1bits.CCP1IF){
                *capture_status = CCP_CAPTURE_NOT_READY;
            } 
        }
        else if(CCP2_PICK == ccp->ccp_pick){
            if(CCP_CAPTURE_READY == PIR2bits.CCP2IF){
                *capture_status = CCP_CAPTURE_READY;
                CCP2_InterruptFlagClear();
            }
            else if(CCP_CAPTURE_NOT_READY == PIR2bits.CCP2IF){
                *capture_status = CCP_CAPTURE_NOT_READY;
            } 
        }  
    }

    return ret;
}

Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_config_t *ccp , uint16 *capture_value){
    Std_ReturnType ret = E_OK;
    ccp_period_reg_t temp_value = {.ccpr_low = 0 , .ccpr_high = 0};

    if(NULL == capture_value){
        ret = E_NOT_OK;
    }
    else{
        if (CCP1_PICK == ccp->ccp_pick)
        {   
            /* copy value from low and high registers */
            temp_value.ccpr_low  = CCPR1L;
            temp_value.ccpr_high = CCPR1H;

            /* paste it in the pointer which i will receive the value on it */
            *capture_value = temp_value.ccpr_16bit;
        }
        else if(CCP2_PICK == ccp->ccp_pick){
            /* copy value from low and high registers */
            temp_value.ccpr_low  = CCPR2L;
            temp_value.ccpr_high = CCPR2H;

            /* paste it in the pointer which i will receive the value on it */
            *capture_value = temp_value.ccpr_16bit;
        }
        
        
    }
   
    return ret;
}
#endif

// COMPARE MODE:

#if (CCP1_SELECTED_MODE == CPP_CFG_COMPARE_MODE) || (CCP2_SELECTED_MODE == CPP_CFG_COMPARE_MODE)
Std_ReturnType CCP_IsCompareComplete     (const ccp_config_t *ccp ,uint8 *compare_status){
    Std_ReturnType ret = E_OK;
    if(NULL == compare_status){
        ret = E_NOT_OK;
    }
    else{
        if(CCP1_PICK == ccp->ccp_pick){
            if(CCP_COMPARE_READY == PIR1bits.CCP1IF){
                *compare_status = CCP_COMPARE_READY;
                CCP1_InterruptFlagClear();
            }
            else if(CCP_COMPARE_NOT_READY  == PIR1bits.CCP1IF){
                *compare_status = CCP_COMPARE_NOT_READY ;
            } 
        }
        else if(CCP2_PICK == ccp->ccp_pick){
            if(CCP_COMPARE_READY == PIR2bits.CCP2IF){
                *compare_status = CCP_COMPARE_READY;
                 CCP2_InterruptFlagClear();
            }
            else if(CCP_COMPARE_NOT_READY  == PIR2bits.CCP2IF){
                *compare_status = CCP_COMPARE_NOT_READY;
            }
        }
    }
    return ret;
}

Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_config_t *ccp , uint16 compare_value){
    Std_ReturnType ret = E_OK;
    ccp_period_reg_t temp_value = {.ccpr_low = 0 , .ccpr_high = 0};

    temp_value.ccpr1_16bit = compare_value;
    if(CCP1_PICK == ccp->ccp_pick){
        CCPR1L =  temp_value.ccpr_low;
        CCPR1H =  temp_value.ccpr_high;
    }
    else if(){
        CCPR2L =  temp_value.ccpr_low;
        CCPR2H =  temp_value.ccpr_high;
    }

    return ret;
}
#endif

// PWM MODE:

#if (CCP1_SELECTED_MODE == CPP_CFG_PWM_MODE) || (CCP2_SELECTED_MODE == CPP_CFG_PWM_MODE)
Std_ReturnType CCP_PWM_Set_Duty(ccp_config_t *ccp , const uint8 duty){
    Std_ReturnType ret = E_OK;
    uint16 temp_dutycycle_value = 0;
    if(NULL == ccp){
        ret = E_NOT_OK;
    }
    else {
        temp_dutycycle_value = (uint16)(((float)PR2 + 1.0) * ((float)duty/100.0) * (float)4.0);
        if (CCP1_PICK == ccp->ccp_pick){
            CCP1CONbits.DC1B     = (temp_dutycycle_value & 0x0003);
            CCPR1L               = (uint8)(temp_dutycycle_value >> 2);
        }
        else if (CCP2_PICK == ccp->ccp_pick){
            CCP2CONbits.DC2B     = (temp_dutycycle_value & 0x0003);
            CCPR2L               = (uint8)(temp_dutycycle_value >> 2);
        }
    }
    return ret;
}

Std_ReturnType CCP_PWM_Start   (ccp_config_t *ccp){
    Std_ReturnType ret = E_OK;
    if(CCP1_PICK == ccp->ccp_pick){
        CCP1_SET_MODE(CCP_PWM_MODE_MODULE);
    }
    else if(CCP2_PICK == ccp->ccp_pick){
        CCP2_SET_MODE(CCP_PWM_MODE_MODULE);
    }
    else{ /* NOTHING */ }
    return ret;
}

Std_ReturnType CCP_PWM_Stop    (ccp_config_t *ccp){
    Std_ReturnType ret = E_OK;
    if(CCP1_PICK == ccp->ccp_pick){
        CCP1_SET_MODE(CCP_DISABLE);
    }
    else if(CCP2_PICK == ccp->ccp_pick){
        CCP2_SET_MODE(CCP_DISABLE);
    }
    else{ /* NOTHING */ }
    return ret;
}
#endif

/************* helper functions ****************/

static void CCP_Interrupt_Config(const ccp_config_t *ccp){

// CCP1 interrupt configuration
#if CCP1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        CCP1_InterruptEnable();
        CCP1_InterruptFlagClear();
        ccp1_InterruptHandler = ccp->ccp1_isr;
        // interrupt priority configuration
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_HIGH_PRIORITY == ccp->ccp1_priority){
            INTERRUPT_globalInterruptEnableHigh();
            CCP1_InterruptPriorityHIGH();
        }
        else if(INTERRUPT_LOW_PRIORITY == ccp->ccp1_priority){
            INTERRUPT_globalInterruptEnableLow();
            CCP1_InterruptPriorityLOW();
        }
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif


// CCP2 interrupt configuration
#if CCP2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        CCP2_InterruptEnable();
        CCP2_InterruptFlagClear();
        ccp2_InterruptHandler = ccp->ccp2_isr;
        // interrupt priority configuration
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
        INTERRUPT_InterruptPriorityEnable();
        if(INTERRUPT_HIGH_PRIORITY == ccp->ccp2_priority){
            INTERRUPT_globalInterruptEnableHigh();
            CCP2_InterruptPriorityHIGH();
        }
        else if(INTERRUPT_LOW_PRIORITY == ccp->ccp2_priority){
            INTERRUPT_globalInterruptEnableLow();
            CCP2_InterruptPriorityLOW();
        }
#else
        INTERRUPT_globalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif

}

#if (CCP1_SELECTED_MODE == CPP_CFG_PWM_MODE) || (CCP2_SELECTED_MODE == CPP_CFG_PWM_MODE)
static void CCP_PWM_Mode_Config(const ccp_config_t *ccp){
    /* PWM frequency inti */
    PR2 = (uint8)(((float)_XTAL_FREQ / (4.0* (float) ccp->pwm_freq * (float) ccp->prescaler * (float) ccp->Postscale)) - 1.0);

    if(ccp->ccp_pick == CCP1_PICK){
        if (CCP_PWM_MODE_MODULE == ccp->ccp_mode_variant){
            CCP1_SET_MODE(CCP_PWM_MODE_MODULE);
        }
    }
    else if(ccp->ccp_pick == CCP2_PICK){
        if (CCP_PWM_MODE_MODULE == ccp->ccp_mode_variant){
            CCP2_SET_MODE(CCP_PWM_MODE_MODULE);
        }
    }
}
#endif

static void CCP_Mode_Timer_Select(const ccp_config_t *ccp){
    if(CCP1_CCP2_TIMER1 == ccp->ccp_timer_mode){
        // CCP1 and CCP2 using timer1
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_TIMER1_CCP2_TIMER3 == ccp->ccp_timer_mode){
        // CCP1 using timer1 and CCP2 using timer3
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP1_CCP2_TIMER3 == ccp->ccp_timer_mode){
        // CCP1 and CCP2 using timer3
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    }
    else{ /* nothing */ }

}

static Std_ReturnType CCP_Capture_Mode_Config(const ccp_config_t *ccp){
    Std_ReturnType ret = E_OK;

    if(CCP1_PICK == ccp->ccp_pick){
        switch (ccp->ccp_mode_variant)
        {
        case CCP_CAPTURE_MODE_FALLING_EDGE    : CCP1_SET_MODE(CCP_CAPTURE_MODE_FALLING_EDGE);     break;
        case CCP_CAPTURE_MODE_RISING_EDGE     : CCP1_SET_MODE(CCP_CAPTURE_MODE_RISING_EDGE);      break;
        case CCP_CAPTURE_MODE_4th_RISING_EDGE : CCP1_SET_MODE(CCP_CAPTURE_MODE_4th_RISING_EDGE);  break;
        case CCP_CAPTURE_MODE_16th_RISING_EDGE: CCP1_SET_MODE(CCP_CAPTURE_MODE_16th_RISING_EDGE); break;
        default: break;
        }
    }
    else if(CCP2_PICK == ccp->ccp_pick){
        switch (ccp->ccp_mode_variant)
        {
        case CCP_CAPTURE_MODE_FALLING_EDGE    : CCP2_SET_MODE(CCP_CAPTURE_MODE_FALLING_EDGE);     break;
        case CCP_CAPTURE_MODE_RISING_EDGE     : CCP2_SET_MODE(CCP_CAPTURE_MODE_RISING_EDGE);      break;
        case CCP_CAPTURE_MODE_4th_RISING_EDGE : CCP2_SET_MODE(CCP_CAPTURE_MODE_4th_RISING_EDGE);  break;
        case CCP_CAPTURE_MODE_16th_RISING_EDGE: CCP2_SET_MODE(CCP_CAPTURE_MODE_16th_RISING_EDGE); break;
        default: break;
        }
    }
    else{ /* nothing */ }

    CCP_Mode_Timer_Select(ccp);

    return ret;

}

static Std_ReturnType CCP_Compare_Mode_Config(const ccp_config_t *ccp){
    Std_ReturnType ret = E_OK;

    if(ccp->ccp_pick == CCP1_PICK){
        switch (ccp->ccp_mode_variant){
        case CCP_COMPARE_MODE_TOGGLE           : CCP1_SET_MODE(CCP_COMPARE_MODE_TOGGLE);           break;
        case CCP_COMPARE_MODE_FORCE_HIGH       : CCP1_SET_MODE(CCP_COMPARE_MODE_FORCE_HIGH);       break;
        case CCP_COMPARE_MODE_FORCE_LOW        : CCP1_SET_MODE(CCP_COMPARE_MODE_FORCE_LOW);        break;
        case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
        case CCP_COMPARE_MODE_GEN_EVENT        : CCP1_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
        default: break;
        }
    }
    else if(ccp->ccp_pick == CCP2_PICK){
        switch (ccp->ccp_mode_variant){
        case CCP_COMPARE_MODE_TOGGLE           : CCP2_SET_MODE(CCP_COMPARE_MODE_TOGGLE);           break;
        case CCP_COMPARE_MODE_FORCE_HIGH       : CCP2_SET_MODE(CCP_COMPARE_MODE_FORCE_HIGH);       break;
        case CCP_COMPARE_MODE_FORCE_LOW        : CCP2_SET_MODE(CCP_COMPARE_MODE_FORCE_LOW);        break;
        case CCP_COMPARE_MODE_GEN_SW_INTERRUPT : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_SW_INTERRUPT); break;
        case CCP_COMPARE_MODE_GEN_EVENT        : CCP2_SET_MODE(CCP_COMPARE_MODE_GEN_EVENT);        break;
        default: break;
        }
    }
    else{ /* nothing */ }
    
    CCP_Mode_Timer_Select(ccp);
    
    return ret;
}

/************* isr function ****************/

void CCP1_ISR(void){
    CCP1_InterruptFlagClear();

    if(ccp1_InterruptHandler){ ccp1_InterruptHandler();}
}

void CCP2_ISR(void){
    CCP2_InterruptFlagClear();

    if(ccp2_InterruptHandler){ccp2_InterruptHandler();}
}