/* 
 * File:   mcal_interrupt_gen_cfg.h
 * Author: houda
 *
 * Created on February 26, 2024, 7:56 PM
 */

#ifndef MCAL_INTERRUPT_GEN_CFG_H
#define	MCAL_INTERRUPT_GEN_CFG_H

#define INTERRUPT_ENABLE_FEATURE    1
#define INTERRUPT_DISABLE_FEATURE   0 

/* EXTERNAL INTERRUPT CONFIGURATIONS */
#define INTERRUPT_PRIORITY_FEATURE  INTERRUPT_DISABLE_FEATURE  /* enable the interrupt priority */
#define INTERRUPT_INTx_FEATURE      INTERRUPT_ENABLE_FEATURE   /* enable the edge interrupt */
#define INTERRUPT_ON_CHANGE_FEATURE INTERRUPT_ENABLE_FEATURE   /* enable the on change interrupt */

/* INTERNAL INTERRUPT CONFIGURATIONS */
#define ADC_INTURRUPT_FUNCTION_ENABLE  INTERRUPT_ENABLE_FEATURE   /* enable the ADC interrupt */
#define ADC_INTURRUPT_PRIORITY_FEATURE INTERRUPT_DISABLE_FEATURE  /* enable the ADC interrupt priority */


#endif	/* MCAL_INTERRUPT_GEN_CFG_H */

