/*
 * File:   newmain.c
 * Author: BEV
 *
 * Created on September 30, 2021, 11:00 AM
 */


#include <xc.h>
#include <avr/interrupt.h>
#define F_CPU 4000000UL //informa a frequ�ncia do clock utilizado

void TCA0_init(void)
{
    PORTC.DIR  |= PIN6_bm; //definindo porta PC6 como output
    PORTC.OUT  |= PIN6_bm; //definindo led como apagado no in�cio
    
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; //permitindo a interrup��o de overflow do TCA
    TCA0.SINGLE.CTRLB = 0x00; //colocando como forma de onda normal 
    TCA0.SINGLE.PER = 0x4C4A; //definindo o tempo em segundos (5) at� a interrup��o
    TCA0.SINGLE.EVCTRL = 0x00; 
    TCA0.SINGLE.INTFLAGS = 0x01; //limpando a flag de interrup��o antes do in�cio da aplica��o
    //SREG = 0x80;
    TCA0.SINGLE.CTRLA = 0x0F; //definindo o valor do prescaler e iniciando timer
}

ISR(TCA0_OVF_vect){
        PORTC.OUTTGL = 0b01000000; //mudando o valor da sa�da PC6

        TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; //Limpando flag
    }

void main(void) {
     _PROTECTED_WRITE(CLKCTRL.OSCHFCTRLA, CLKCTRL_FREQSEL_4M_gc); //escolhendo 
    //frequ�ncia do clock
     
    TCA0_init();
    
    sei();
    
    while(1){
        
    }
    
    return;
}
