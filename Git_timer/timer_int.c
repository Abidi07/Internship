#include<avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>

int intr_count=0;


ISR (TIMER0_OVF_vect)               //Interrupt vector for Timer0
{

  if (intr_count==31)               //waiting for 31 because to get 1 sec delay
 
  {
    PORTB^=(0xff);                  //toggling the LED
    intr_count=0;                   //making intr_count=0 to repeat the count
    ++intr_count;
  }
  
  else  intr_count++;               //incrementing c upto 31
}

void timer_setup()
{

  DDRB |=0xff;                     //set PORTB as output(LED)
  TCCR0A=0x00;                     //Normal mode operation 
  TCCR0B=0x05;   	            //prescaling with 1024
  sei();                           //enabling global interrupt
  TCNT0=0;                         //8 bit data register, initial value set to 0, it holds the value from 0 - 255 & once it overflows it starts incrementing from 0
  TIMSK|=(1<<TOIE0);               //enabling timer0 interrupt
  PORTB|=0xff;                     //Turn on all LEDs

}

int main () 
{
  timer_setup();
  while(1)
  {
    
  }
}
