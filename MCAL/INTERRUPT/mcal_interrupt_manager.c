/* 
 * File:   mcal_interrupt_manager.c
 * Author: houda
 *
 * Created on February 26, 2024, 6:13 PM
 */


#include "mcal_interrupt_manager.h"

#if INTERRUPT_PRIORITY_FEATURE == INTERRUPT_ENABLE_FEATURE

void __interrupt InterruptManagerHigh (void){


}

void __interrupt(low_priority) InterruptManagerLow (void){


}

#else

void __interrupt() InterruptManager(void){
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
}

#endif