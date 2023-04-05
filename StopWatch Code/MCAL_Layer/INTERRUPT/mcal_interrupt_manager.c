/* 
 * File:   mcal_interrupt_manager.c
 * Author: Walid Omar
 *
 * Created on December 31, 2022, 9:22 PM
 */

#include "mcal_interrupt_manager.h"

#if INTERRUPT_FEATURE == INTERRUPT_PRIORITY_ENABLE

void __interrupt()InterruptManagerHigh(void){
    
    if((PIE1bits.TMR1IE == INTERRUPT_ENABLE)&&(PIR1bits.TMR1IF == INTERRUPT_OCCUR))
    {
        TMR1_ISR();
    }
    else {/* Nothing */}
}

void __interrupt(low_priority) InterruptManagerLow(void){
 
}


#else
void __interrupt()InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE )&& (INTERRUPT_OCCUR == INTCONbits.INT0IF))
    {
        INT0_ISR();
    }
    else{/*nothing*/}
    
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE )&& (INTERRUPT_OCCUR == INTCON3bits.INT1IF))
    {
        INT1_ISR();
    }
    else{/*nothing*/}
}

#endif
