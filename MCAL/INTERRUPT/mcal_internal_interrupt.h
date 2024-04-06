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


// timer1 interrupt macros:

#if TIMER1_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer1 module*/
#define TIMER1_InterruptDisable()         (PIE1bits.TMR1IE = 0)
/* This routine sets the interrupt enable for the timer1 module*/
#define TIMER1_InterruptEnable()          (PIE1bits.TMR1IE = 1)
/* This routine clears the interrupt flag for the timer1 module*/
#define TIMER1_InterruptFlagClear()       (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer1 Interrupt Priority to be High priority */
#define TIMER1_InterruptPriorityHIGH()     (IPR1bits.TMR1IP = 1)
/* This routine set the timer1 Interrupt Priority to be Low priority */
#define TIMER1_InterruptPriorityLOW()      (IPR1bits.TMR1IP = 0)
#endif
#endif

// timer2 interrupt macros:
#if TIMER2_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer2 module*/
#define TIMER2_InterruptDisable()        (PIE1bits.TMR2IE = 0)
/* This routine sets the interrupt enable for the timer2 module*/
#define TIMER2_InterruptEnable()         (PIE1bits.TMR2IE = 1)
/* This routine clears the interrupt flag for the timer2 module*/
#define TIMER2_InterruptFlagClear()      (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer2 Interrupt Priority to be High priority */
#define TIMER2_InterruptPriorityHIGH()   (IPR1bits.TMR2IP = 1)
/* This routine set the timer2 Interrupt Priority to be Low priority */
#define TIMER2_InterruptPriorityLOW()    (IPR1bits.TMR2IP = 0)
#endif
#endif


// timer3 interrupt macros:
#if TIMER3_INTURRUPT_FUNCTION_ENABLE == INTERRUPT_ENABLE_FEATURE
/* This routine clears the interrupt enable for the timer3 module*/
#define TIMER3_InterruptDisable()        (PIE2bits.TMR3IE = 0)
/* This routine sets the interrupt enable for the timer3 module*/
#define TIMER3_InterruptEnable()         (PIE2bits.TMR3IE = 1)
/* This routine clears the interrupt flag for the timer3 module*/
#define TIMER3_InterruptFlagClear()      (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_FEATURE  == INTERRUPT_ENABLE_FEATURE
/* This routine set the timer3 Interrupt Priority to be High priority */
#define TIMER3_InterruptPriorityHIGH()   (IPR2bits.TMR3IP = 1)
/* This routine set the timer3 Interrupt Priority to be Low priority */
#define TIMER3_InterruptPriorityLOW()    (IPR2bits.TMR3IP = 0)
#endif
#endif

/* DATA TYPE DECLARATIONS (ENUMS,UNIONS,STRUCTS) */

/* FUNTIONS DECLARATIONS */


#endif	/* MCAL_INTERNAL_INTERRUPT_H */

