#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
while(1)
{
DDRB= 0xff; 

PORTB= 0xff; 
_delay_ms(1000);

PORTB= 0x00;
_delay_ms(1000);
}
}
