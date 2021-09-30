/*
 * File:   newmain.c
 * Author: BEV
 *
 * Created on September 30, 2021, 11:00 AM
 */


#include <xc.h>
#include <avr/interrupt.h>
#define F_CPU 4000000UL //informa a frequência do clock utilizado

void TCA0_init(void)
{
    PORTC.DIR  |= PIN6_bm;
    PORTC.OUT  |= PIN6_bm;
    
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
    TCA0.SINGLE.CTRLB = 0x00;
    TCA0.SINGLE.PER = 0x4C4A; //INVERTER COM FUNÇÃO DE BAIXO SE DER ERRADO
    TCA0.SINGLE.EVCTRL = 0x00;
    TCA0.SINGLE.INTFLAGS = 0x01;
    //SREG = 0x80;
    TCA0.SINGLE.CTRLA = 0x0F;
}

ISR(TCA0_OVF_vect){
        PORTC.OUTTGL = 0b01000000;;

        TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
    }

void main(void) {
     _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_4M_gc); //escolhendo 
    //frequência do clock
     
    TCA0_init();
    
    sei();
    
    while(1){
        
    }
    
    return;
}
