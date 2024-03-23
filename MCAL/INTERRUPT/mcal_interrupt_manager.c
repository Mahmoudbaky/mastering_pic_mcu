/* 
 * File:   mcal_interrupt_manager.c
 * Author: houda
 *
 * Created on February 26, 2024, 6:13 PM
 */


#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE

void __interrupt() InterruptManagerHigh (void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* nothing */}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* nothing */}
}

void __interrupt(low_priority) InterruptManagerLow (void){
      if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
}

#else

void __interrupt() InterruptManager(void){
    /* ============ INTx External Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE)&&(INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{/* nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{/* nothing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE)&&(INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{/* nothing */}
    /* ============ INTx External Interrupt End ============ */
    
    /* ============ PortB External On Change Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == PIC_HIGH) && (RB4_Flag = 1)){
        RB4_Flag = 0;
        RB4_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == PIC_LOW) && (RB4_Flag = 0)){
        RB4_Flag = 1;
        RB4_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == PIC_HIGH) && (RB5_Flag = 1)){
        RB5_Flag = 0;
        RB5_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == PIC_LOW)&& (RB5_Flag = 0)){
        RB5_Flag = 1;
        RB5_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == PIC_HIGH) && (RB6_Flag = 1)){
        RB6_Flag = 0;
        RB6_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == PIC_LOW) && (RB6_Flag = 0)){
        RB6_Flag = 1;
        RB6_ISR(1);
    }
    else{ /* Nothing */ }
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == PIC_HIGH) && (RB7_Flag = 1)){
        RB7_Flag = 0;
        RB7_ISR(0);
    }
    else{ /* Nothing */ }
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == PIC_LOW) && (RB7_Flag = 0)){
        RB7_Flag = 1;
        RB7_ISR(1);
    }
    else{ /* Nothing */ }
    
    /* ============ ADC Interrupt Start ============ */
    if((INTERRUPT_ENABLE == PIE1bits.ADIE)&&(INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{/* nothing */}
    /* ============ ADC Interrupt End ============ */

}

#endif