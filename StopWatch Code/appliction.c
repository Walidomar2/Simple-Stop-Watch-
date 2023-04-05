/* 
 * File:   appliction.c
 * Author: Walid Omar
 *
 * Created on November 13, 2022, 9:08 PM
 */

#include "application.h"

Std_ReturnType ret=E_NOT_OK;



uint8 miniSeconds=0;
uint8 seconds=0;
uint8 minutes=0;
uint8 counter=0;
uint8 watchFlag=0;


void StopWatchReset_ISR(void){
    miniSeconds = 0;
    seconds = 0;
    minutes =0;
    counter=0;
    watchFlag=0;
}

void ContinuePause_ISR(void){
    
    if(0==watchFlag){
        watchFlag=1;
    }
    else
    {
       watchFlag = 0; 
    }
}


interrupt_INTx_t int0_obj = {
  .EXT_InterruptHandler =StopWatchReset_ISR,
  .edge = INTERRUPT_RISING_EDGE,
  .INTx_pin.Port = PORTB_INDEX,
  .INTx_pin.Direction=INPUT,
  .INTx_pin.Pin=PIN0,
  .INTx_pin.Logic=LOW
};

interrupt_INTx_t int1_obj = {
  .EXT_InterruptHandler =ContinuePause_ISR,
  .edge = INTERRUPT_RISING_EDGE,
  .INTx_pin.Port = PORTB_INDEX,
  .INTx_pin.Direction=INPUT,
  .INTx_pin.Pin=PIN1,
  .INTx_pin.Logic=LOW
};

int main(){
    Interrupt_INTx_Enable(&int0_obj);
    Interrupt_INTx_Enable(&int1_obj);
    
    ret=gpio_port_init(PORTC_INDEX,0xF0);
    ret=gpio_port_init(PORTD_INDEX,0x00);
    while(1){
        
        if(1==watchFlag)
        {
            while(watchFlag)
            {
            gpio_port_write_logic(PORTD_INDEX,0x3B);  // 0011 1011  
            gpio_port_write_logic(PORTC_INDEX,((uint8)seconds/10));
            __delay_us(2500);
            gpio_port_write_logic(PORTD_INDEX,0x37);   // 0011 0111
            gpio_port_write_logic(PORTC_INDEX,((uint8)seconds%10));
            __delay_us(2500);

            gpio_port_write_logic(PORTD_INDEX,0x2F);    // 0010 1111
            gpio_port_write_logic(PORTC_INDEX,((uint8)miniSeconds/10));
            __delay_us(2500);
            gpio_port_write_logic(PORTD_INDEX,0x1F);     // 0001 1111 
            gpio_port_write_logic(PORTC_INDEX,((uint8)miniSeconds%10));
            __delay_us(2500);

            gpio_port_write_logic(PORTD_INDEX,0x3E);   //0011 1110
            gpio_port_write_logic(PORTC_INDEX,((uint8)minutes/10));
            __delay_us(2500);
            gpio_port_write_logic(PORTD_INDEX,0x3D);  //0011  1101
            gpio_port_write_logic(PORTC_INDEX,((uint8)minutes%10));
            __delay_us(2500);
            }
        }
        
        if(0==watchFlag){
            for(counter=0;counter<2;counter++){    
            gpio_port_write_logic(PORTD_INDEX,0x3B);  // 0011 1011  
            gpio_port_write_logic(PORTC_INDEX,((uint8)seconds/10));
            __delay_us(2500);
            gpio_port_write_logic(PORTD_INDEX,0x37);   // 0011 0111
            gpio_port_write_logic(PORTC_INDEX,((uint8)seconds%10));
            __delay_us(2500);

            gpio_port_write_logic(PORTD_INDEX,0x2F);    // 0010 1111
            gpio_port_write_logic(PORTC_INDEX,((uint8)miniSeconds/10));
            __delay_us(2500);
            gpio_port_write_logic(PORTD_INDEX,0x1F);     // 0001 1111 
            gpio_port_write_logic(PORTC_INDEX,((uint8)miniSeconds%10));
            __delay_us(2500);

            gpio_port_write_logic(PORTD_INDEX,0x3E);   //0011 1110
            gpio_port_write_logic(PORTC_INDEX,((uint8)minutes/10));
            __delay_us(2500);
            gpio_port_write_logic(PORTD_INDEX,0x3D);  //0011  1101
            gpio_port_write_logic(PORTC_INDEX,((uint8)minutes%10));
            __delay_us(2500);  
            }

            miniSeconds++;
            if(90 == miniSeconds)
            {
                seconds++;
                miniSeconds= 0;
            }

            if(60 == minutes)
            {
                minutes=0;
            }
     
        }
    }
    return (EXIT_SUCCESS);
}
