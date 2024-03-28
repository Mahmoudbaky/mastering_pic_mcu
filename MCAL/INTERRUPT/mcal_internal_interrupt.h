/* 
 * File:   mcal_internal_interrupt.h
 * Author: houda
 *
 * Created on February 26, 2024, 6:08 PM
 */

#ifndef MCAL_INTERNAL_INTERRUPT_H
#define	MCAL_INTERNAL_INTERRUPT_H

/* INCLUDS */

#include "mcal_interrupt_config.h"
#include "../ADC/mcal_adc.h"

/* MACRO DECLARATIONS */

/* MACRO FUNTIONS DECLARATIONS */

// ADC interrupt macros:
#if ADC_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the ADC module*/
#define ADC_InterruptDisable()         (PIE1bits.ADIE = 0)
/* This routine sets the interrupt enable for the ADC module*/
#define ADC_InterruptEnable()          (PIE1bits.ADIE = 1)
/* This routine clears the interrupt flag for the ADC module*/
#define ADC_InterruptFlagClear()       (PIR1bits.ADIF = 0)
/* This routine sets the interrupt priority for the ADC module*/
#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE
/* This routine set the ADC Interrupt Priority to be High priority */
#define ADC_InterruptPriorityHIGH()     (IPR1bits.ADIP = 1)
/* This routine set the ADC Interrupt Priority to be Low priority */
#define ADC_InterruptPriorityLOW()      (IPR1bits.ADIP = 0)
#endif
#endif

// timer0 interrupt macros:
#if TIMER0_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer0 module*/
#define TIMER0_InterruptDisable()         (INTCONbits.TMR0IE = 0)
/* This routine sets the interrupt enable for the timer0 module*/
#define TIMER0_InterruptEnable()          (INTCONbits.TMR0IE = 1)
/* This routine clears the interrupt flag for the timer0 module*/
#define TIMER0_InterruptFlagClear()       (INTCONbits.TMR0IF = 0)
/* This routine sets the interrupt priority for the timer0 module*/
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer0 Interrupt Priority to be High priority */
#define TIMER0_InterruptPriorityHIGH()     (INTCON2bits.TMR0IP = 1)
/* This routine set the timer0 Interrupt Priority to be Low priority */
#define TIMER0_InterruptPriorityLOW()      (INTCON2bits.TMR0IP = 0)
#endif
#endif


/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

/* FUNTIONS DECLARATIONS */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

