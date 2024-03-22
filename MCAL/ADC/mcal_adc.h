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

/*
    * Description: ADC source selection
*/
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

#define ADC_RIGHT_JUSTIFIED_RESULT  0x01U
#define ADC_LEFT_JUSTIFIED_RESULT   0x00U

#define ADC_VOLTAGE_REF_ENABLE  0x01U
#define ADC_VOLTAGE_REF_DISABLE 0x00U

/* MACRO FUNTIONS DECLARATIONS */

/*
    * Description: ADC status 
    * @return: 1 if the ADC is busy, 0 A/D idle
*/
#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)

/*
    * Description: macro to start the conversion
*/
#define ADC_START_CONVERSION()  (ADCON0bits.GO_nDONE = 1) 

/*
    * Description: ADC enable
    1: Enable the ADC module
    0: Disable the ADC module
*/
#define ADC_ENABLE()            (ADCON0bits.ADON = 1)
#define ADC_DISABLE()           (ADCON0bits.ADON = 0)

/*
    * Description: ADC VREF ENABLE AND DISABLE
*/
#define ADC_ENABLE_VOLTAGE_REF() do{\
                                    ADCON1bits.VCFG0 = 1;\
                                    ADCON1bits.VCFG1 = 1;\
                                }while(0)
#define ADC_DISABLE_VOLTAGE_REF() do{\
                                    ADCON1bits.VCFG0 = 0;\
                                    ADCON1bits.VCFG1 = 0;\
                                }while(0)

#define ADC_ANALOG_DIGITAL_FUNCTIONALITY(_CONFIG) (ADCON1bits.PCFG = _CONFIG)


#define ADC_RIGHT_JUSTIFIED()   (ADCON2bits.ADFM = 1)
#define ADC_LEFT_JUSTIFIED()    (ADCON2bits.ADFM = 0)


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
}adc_Channel_select_t;


typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_aquisition_time_t;

typedef enum {
    ADC_FOSC_2 = 0,
    ADC_FOSC_8,
    ADC_FOSC_32,
    ADC_FRC,
    ADC_FOSC_4,
    ADC_FOSC_16,
    ADC_FOSC_64
}adc_conversion_clock_t;

typedef struct {
    void (*adc_InterruptHandler)(void);                     /* callback function */
    adc_aquisition_time_t  adc_aquisition_time;     /* @ref adc adc_aquisition_time_t */
    adc_conversion_clock_t adc_conversion_clock;    /* @ref adc_conversion_clock_t */
    adc_Channel_select_t   adc_Channel_select;      /* @ref adc_Channel_select_t */
    uint8                adc_voltage_ref   : 1;   /* voltage ref configuration */
    uint8                adc_result_format : 1;   /* result format */
    uint8                adc_reserved      : 6;
}adc_config_t;

typedef uint16 adc_result_t;

/* FUNTIONS DECLARATIONS */

Std_ReturnType ADC_Init(const adc_config_t *adc);
Std_ReturnType ADC_DeInit(const adc_config_t *adc);
Std_ReturnType ADC_SelectChannel(const adc_config_t *adc, adc_Channel_select_t channel);
Std_ReturnType ADC_StartConversion(const adc_config_t *adc);
Std_ReturnType ADC_IsConversionDone(const adc_config_t *adc, uint8 *conversion_status);
Std_ReturnType ADC_GetResult(const adc_config_t *adc, adc_result_t *result);
Std_ReturnType ADC_GetConversion(const adc_config_t *adc, adc_Channel_select_t channel , adc_result_t *result);


#endif	/* MCAL_ADC_H */

