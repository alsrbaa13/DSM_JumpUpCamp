/*
* File        	: catch_the_mole
* By          	: Lim MinGyu
* 2017.08.03	: Last modified
*
********************************************************************************
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>

#define DDR_SW DDRF 
#define DDR_LED DDRB

#define PORT_SW PORTF
#define PORT_LED PORTB

#define LED1 PORT4
#define LED2 PORT5
#define LED3 PORT6
#define LED4 PORT7

volatile unsigned int LED_Num; // random LED number
volatile unsigned int Score; // catched mole number
unsigned char sw;

ISR(INT0_vect)
{
    if(LED_Num == 4) Score++; //check to catch the mole
    PORT_LED &= ~((1<< LED1) & 0xff); // led off 
    _delay_ms(100);
 
}

ISR(INT1_vect)
{
    if(LED_Num == 5) Score++;
    PORT_LED &= ~((1<< LED2) & 0xff);
    _delay_ms(100);
}

ISR(INT2_vect)
{   
    if(LED_Num == 6) Score++;
    PORT_LED &= ~((1<< LED3) & 0xff);
    _delay_ms(100);
}


ISR(INT3_vect)
{   
    if(LED_Num == 7) Score++;
    PORT_LED &= ~((1<< LED4) & 0xff);
    _delay_ms(100);
} 

//initialize gpio
void init_GPIO(){
    DDR_LED = (1<< LED1) | (1<< LED2) | (1<<LED3) | (1<<LED4);
    PORT_LED = 0x00;
}
//initialize interrupt
void init_Interrupt(){
    EICRA = (1 << ISC01) | (0 << ISC00) | (1 << ISC11) | (0 << ISC10) | (1 << ISC21) | (0 << ISC20) | (1 << ISC31) | (0 << ISC30);
    EIMSK = (1 << INT0) | (1 << INT1) | (1 << INT2) | (1 << INT3);
}

void GameStart(){
       LED_Num = (rand()%4)+4; // pick random number
       PORT_LED = (1 << LED_Num); // LED on
}


int main(void)
{  
    init_GPIO();
    init_Interrupt();
    sei();
   for(;;){
   
        if(Score >= 25){
	    PORT_LED = 0xFF; // game set
	    _delay_ms(1500);
            PORT_LED = 0x00;
            _delay_ms(1500);
            Score = 0;
	  }
        GameStart();
        _delay_ms(215);

    }
  
}
