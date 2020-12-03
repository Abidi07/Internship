//Program ATTiny85 to blink LED connected to PB1 at 1s interval.
//Assumes ATTiny85 is running at 8MHz internal clock speed.
//Using Timer0

#include<avr/io.h>
//#define F_CPU 8000000UL
#include<util/delay.h>


void timer_config()
{
 DDRB =0b00000010;                       

//Set PB1 as output
 
 TCCR0A=0x00;  
 TIFR=0X02;                  
         
//TCCR0A = Timer counter control register, 
//8 bit regsiter, first two bits are WGM (wave generation mode), next two bits 
//are reserved bits and last four bits are for COM0A [7:6],COM0B [5:4]  
//For normal mode operation (counting direction always up and incrementing), COM0A/B set to be [0:0]

 TCCR0B=0x05; 				 
 
//TCCRB first three bits [2:0] are used for prescaling 
//[0:0:0] is used for no clock source 
//clk(i/0)= 1024 (prescaler) the bits should be [1:0:1]

 TCNT0=0;                                
 
//8 bit data register, initial value set to 0 
//it holds the value from 0 - 255, once it overflows it starts incrementing from 0

}

//Description for seting up the delay for 1sec
//T = 1 / F = 1/ 8000000 = 0.125us
//8000000/1024= 7812.5Hz 
//Time taken per increment = 1/7812.5hz = 128us 
//Time taken for 0 to 255 count in TCNT0 register = 128us x 255 = 0.03264
//We need a delay of 1 sec, which can be 1/0.03264 = 30.63 ~ 31
//Repeating the loop 31 times will give us (31*0.03264ms) = 1011.84 ms ~ 1s 


void tmdel()
{
 unsigned int i=0;
 
 while(i<=30)
  {                                        
   while((TIFR & (1 << TOV0) )==0);     
      
//TIFR=Timer/Counter Interrupt Flag Register (all bits as flags)   
//Waiting for 0-255 and flag to raise
   
   TIFR|=(1<<TOV0);                        

//TIFR is a 8 bit register which holds the status of Timer0,  Bit 1 – TOV0: Timer/Counter0 Overflow Flag
//TOV0 = Timer0 overflow flag, high the flag when TCNT0 reaches 255 (maximum value)
   
   i++;                                    

//incremented by one
  }
}


int main()
{
 timer_config();
 while(1)
 {
  PORTB= 0xff;                         //PortB high 
  tmdel();                             //Function call for the delay of 1 second
  PORTB=0x00;                          //PORTB low
  tmdel();                             //Function call for the delay of 1 second
 }
}
