/* 
 * File:   mcal_adc.h
 * Author: houda
 *
 * Created on March 21, 2024, 8:30 PM
 */

#include "mcal_adc.h"

#if ADC_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
static void (*ADC_InterruptHandler)(void) = NULL;
#endif

/* HELPER FUNCTIONS DECLERATIONS */
static inline void adc_input_channel_port_configuration(adc_Channel_select_t channel);
static inline void select_result_format(const adc_config_t *adc);
static inline void configure_VREF(const adc_config_t *adc);


/*MAIN API FUNCTIONS */
Std_ReturnType ADC_Init(const adc_config_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        /* disable the adc */
        ADC_DISABLE();
        /* configure the acquistions time */
        ADCON2bits.ACQT = adc->adc_aquisition_time;
        /* configure the conversion clock */
        ADCON2bits.ADCS = adc->adc_conversion_clock;
        /* configure the default channel */
        ADCON0bits.CHS = adc->adc_Channel_select;
        adc_input_channel_port_configuration(adc->adc_Channel_select);
        /* configure the interrupt */
#if ADC_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
            
            ADC_InterruptEnable();
            ADC_InterruptFlagClear();
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
            if(INTERRUPT_HIGH_PRIORITY == adc->priority){ADC_InterruptPriorityHIGH();}
            else if(INTERRUPT_LOW_PRIORITY == adc->priority){ADC_InterruptPriorityLOW();}
            else{/* NOTHING */}
#else 
            INTERRUPT_globalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
            #endif
            ADC_InterruptHandler = adc->adc_InterruptHandler;
        #endif
        /* configure the result format */
        select_result_format(adc);
        /* configure the voltage reference */
        configure_VREF(adc);
        /* enable the adc */
        ADC_ENABLE();
    }
    return ret;
}

Std_ReturnType ADC_DeInit(const adc_config_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
        /* disable the adc */
        ADC_DISABLE();
        /* configure the interrupt */
        #if ADC_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
        ADC_InterruptDisable();
        #endif
    }
    return ret;
}

Std_ReturnType ADC_SelectChannel(const adc_config_t *adc, adc_Channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
       /* configure the default channel */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configuration(channel);
    }
    return ret;
}

Std_ReturnType ADC_StartConversion(const adc_config_t *adc){
    Std_ReturnType ret = E_OK;
    if(NULL == adc){
        ret = E_NOT_OK;
    }
    else{
       ADC_START_CONVERSION();
    }
    return ret;
}

Std_ReturnType ADC_IsConversionDone(const adc_config_t *adc, uint8 *conversion_status){
    Std_ReturnType ret = E_OK;
    if((NULL == adc) || (NULL == conversion_status)){
        ret = E_NOT_OK;
    }
    else{
      *conversion_status = (uint8)(!(ADC_CONVERSION_STATUS()));
    }
    return ret;
}

Std_ReturnType ADC_GetResult(const adc_config_t *adc, adc_result_t *result){
    Std_ReturnType ret = E_OK;
    if((NULL == adc) || (NULL == result)){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RIGHT_JUSTIFIED_RESULT == adc->adc_result_format){
            *result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
        else if (ADC_LEFT_JUSTIFIED_RESULT == adc->adc_result_format){
            *result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{
            *result = (adc_result_t)((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Blocking(const adc_config_t   *adc
                                         ,adc_Channel_select_t channel
                                         ,adc_result_t         *result){
    Std_ReturnType ret = E_OK;
    if((NULL == adc) || (NULL == result)){
        ret = E_NOT_OK;
    }
    else{
        /* select channel */
        ret = ADC_SelectChannel(adc, channel);
        /* start adc conversion */
        ret = ADC_StartConversion(adc);
        /* check adc status */
        while(ADCON0bits.GO_nDONE);
        /* get the result */
        ret = ADC_GetResult(adc, result);
    }
    return ret;
}

Std_ReturnType ADC_GetConversion_Interrupt(const adc_config_t *adc, adc_Channel_select_t channel){
    Std_ReturnType ret = E_OK;
    if((NULL == adc)){
        ret = E_NOT_OK;
    }
    else{
        /* select channel */
        ret = ADC_SelectChannel(adc, channel);
        /* start adc conversion */
        ret = ADC_StartConversion(adc);
    }
}


/* HELPER FUNCTIONS */
static inline void adc_input_channel_port_configuration(adc_Channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_0:
            SET_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_1:
            SET_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_2:
            SET_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_3:
            SET_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_4:
            SET_BIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_5:
            SET_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_6:
            SET_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_7:
            SET_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_8:
            SET_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_9:
            SET_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_10:
            SET_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_11:
            SET_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_12:
            SET_BIT(TRISB, _TRISB_RB0_POSN);
            break;
        default: /* NOTHING */
            break;
    }
}

static inline void select_result_format(const adc_config_t *adc){
    if(ADC_RIGHT_JUSTIFIED_RESULT == adc->adc_result_format){
        ADC_RIGHT_JUSTIFIED();
    }
    else if (ADC_LEFT_JUSTIFIED_RESULT == adc->adc_result_format){
        ADC_LEFT_JUSTIFIED();
    }
    else{
        /* NOTHING */
    }
}

static inline void configure_VREF(const adc_config_t *adc){

    if(ADC_VOLTAGE_REF_ENABLE == adc->adc_voltage_ref){
        ADC_ENABLE_VOLTAGE_REF();
    }
    else if (ADC_VOLTAGE_REF_DISABLE == adc->adc_voltage_ref){
        ADC_DISABLE_VOLTAGE_REF();
    }
    else{
        /* NOTHING */
    }
}


/* ADC INTERRUPT SERVICE ROUTINE */
void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_InterruptHandler){ADC_InterruptHandler();}
}