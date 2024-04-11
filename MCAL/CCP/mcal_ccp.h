/*
    * mcal_ccp.h
    *
    *  Created on: 6/4/2024
*/

/*
    x registers to controrl the CCPx module
    1. CCPxCON : control register  
*/

/* INCLUDS */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/mcal_gpio.h"
#include "../INTERRUPT/mcal_internal_interrupt.h"
#include "mcal_ccp_cfg.h"

/* MACRO DECLARATIONS */

// MODE VARIANT :
#define CCP_DISABLE                         ((uint8)0X00)

#define CCP_CAPTURE_MODE_FALLING_EDGE       ((uint8)0X04)   
#define CCP_CAPTURE_MODE_RISING_EDGE        ((uint8)0X05)   
#define CCP_CAPTURE_MODE_4th_RISING_EDGE    ((uint8)0X06)  
#define CCP_CAPTURE_MODE_16th_RISING_EDGE   ((uint8)0X07)  

#define CCP_COMPARE_MODE_TOGGLE             ((uint8)0X02)    
#define CCP_COMPARE_MODE_FORCE_HIGH         ((uint8)0X08)    
#define CCP_COMPARE_MODE_FORCE_LOW          ((uint8)0X09)    
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT   ((uint8)0x0A)
#define CCP_COMPARE_MODE_GEN_EVENT          ((uint8)0x0B)

#define CCP_PWM_MODE_MODULE                 ((uint8)0x0C)

/* CCP Capture Mode State  */
#define CCP_CAPTURE_NOT_READY              0X00
#define CCP_CAPTURE_READY                  0X01

/* CCP Compare Mode State  */
#define CCP_COMPARE_NOT_READY              0X00
#define CCP_COMPARE_READY                  0X01

#define    CCP_TIMER2_POSTSCALE_1    1
#define    CCP_TIMER2_POSTSCALE_2    2
#define    CCP_TIMER2_POSTSCALE_3    3
#define    CCP_TIMER2_POSTSCALE_4    4
#define    CCP_TIMER2_POSTSCALE_5    5 
#define    CCP_TIMER2_POSTSCALE_6    6
#define    CCP_TIMER2_POSTSCALE_7    7
#define    CCP_TIMER2_POSTSCALE_8    8
#define    CCP_TIMER2_POSTSCALE_9    9
#define    CCP_TIMER2_POSTSCALE_10   10
#define    CCP_TIMER2_POSTSCALE_11   11
#define    CCP_TIMER2_POSTSCALE_12   12
#define    CCP_TIMER2_POSTSCALE_13   13
#define    CCP_TIMER2_POSTSCALE_14   14
#define    CCP_TIMER2_POSTSCALE_15   15
#define    CCP_TIMER2_POSTSCALE_16   16

#define    CCP_TIMER2_PRESCALER_1  1
#define    CCP_TIMER2_PRESCALER_4  4
#define    CCP_TIMER2_PRESCALER_16 16

/* MACRO FUNTIONS DECLARATIONS */

#define CCP1_SET_MODE(MODE) (CCP1CONbits.CCP1M = MODE)
#define CCP2_SET_MODE(_MODE) (CCP2CONbits.CCP2M = _MODE)

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

typedef enum{
    CCP_CAPTURE_MODE = 0,
    CCP_COMPARE_MODE,
    CCP_PWM_MODE
}ccp_mode_t;


typedef union {
    struct {
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct {
        uint16 ccpr_16bit;
    };
}ccp_period_reg_t;

typedef enum {
    CCP1_PICK = 0,
    CCP2_PICK
}CCP_PICK_t;


typedef enum {
    CCP1_CCP2_TIMER1 = 0,
    CCP1_TIMER1_CCP2_TIMER3,
    CCP1_CCP2_TIMER3
}CCP_TIMER_MODE_t;


typedef struct {
    ccp_mode_t       ccp_mode;
    uint8            ccp_mode_variant;    // mode variant
    pin_config_p     pin;                // CCP1 pin
    CCP_PICK_t       ccp_pick;          // CCP1 or CCP2
    CCP_TIMER_MODE_t ccp_timer_mode;   // CCP1 or CCP2 timer mode

#if (CCP1_SELECTED_MODE == CPP_CFG_PWM_MODE) || (CCP2_SELECTED_MODE == CPP_CFG_PWM_MODE)
    uint32 pwm_freq;
    uint8             Postscale;
    uint8             prescaler;
#endif

#if CCP1_INTURRUPT_FUNCTION_ENABLE  ==  INTERRUPT_ENABLE_FEATURE
    void (*ccp1_isr)(void);
    interrupt_priority_cfg ccp1_priority;
#endif

#if CCP1_INTURRUPT_FUNCTION_ENABLE  ==  INTERRUPT_ENABLE_FEATURE
    void (*ccp2_isr)(void);
    interrupt_priority_cfg ccp2_priority;
#endif
}ccp_config_t;


/* FUNTIONS DECLARATIONS */

Std_ReturnType ccp_Init  (ccp_config_t *ccp);
Std_ReturnType ccp_DeInit(ccp_config_t *ccp);

#if (CCP1_SELECTED_MODE == CPP_CFG_CAPTURE_MODE)
Std_ReturnType CCP_IsCapturedDataReady    (const ccp_config_t *ccp , uint8 *capture_status);
Std_ReturnType CCP_Capture_Mode_Read_Value(const ccp_config_t *ccp , uint16 *capture_value);
#endif


#if (CCP1_SELECTED_MODE == CPP_CFG_COMPARE_MODE)
Std_ReturnType CCP_IsCompareComplete     (const ccp_config_t *ccp , uint8 *compare_status);
Std_ReturnType CCP_Compare_Mode_Set_Value(const ccp_config_t *ccp , uint16 compare_value);
#endif


#if (CCP1_SELECTED_MODE == CPP_CFG_PWM_MODE)
Std_ReturnType CCP_PWM_Set_Duty(ccp_config_t *ccp , const uint8 duty);
Std_ReturnType CCP_PWM_Start   (ccp_config_t *ccp);
Std_ReturnType CCP_PWM_Stop    (ccp_config_t *ccp);
    
#endif