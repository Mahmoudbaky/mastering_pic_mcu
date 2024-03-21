/* 
 * File:   mcal_adc.h
 * Author: houda
 *
 * Created on March 21, 2024, 8:30 PM
 */

#ifndef MCAL_ADC_H
#define	MCAL_ADC_H


/* INCLUDS */

#include "mcal_adc_cfg.h"
#include "../../MCAL/mcal_std_types.h"
#include "pic18f4620.h"
#include "../GPIO/mcal_gpio.h"



/* MACRO DECLARATIONS */

#define ADC_AN0_ANALOG_FUNCTIONALITY  0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY  0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY  0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY  0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY  0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY  0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY  0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY  0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY  0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY  0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY 0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY 0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY 0x02

#define ALL_ANALOG_PINS  0x00
#define ALL_DIGITAL_PINS 0x0F

/* MACRO FUNTIONS DECLARATIONS */

#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)

#define ADC_ENABLE()            (ADCON0bits.ADON = 1)
#define ADC_DISABLE()           (ADCON0bits.ADON = 0)

#define ADC_ENABLE_VOLTAGE_REF() do{\
                                    ADCON1bits.VCFG0 = 1;\
                                    ADCON1bits.VCFG1 = 1;\
                                }while(0)
#define ADC_DISABLE_VOLTAGE_REF() do{\
                                    ADCON1bits.VCFG0 = 0;\
                                    ADCON1bits.VCFG1 = 0;\
                                }while(0)


/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */


/*
    * Description: ADC reference voltage selection
*/
typedef enum {
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12
}ADC_Channel_select_t;

/* FUNTIONS DECLARATIONS */


#endif	/* MCAL_ADC_H */

