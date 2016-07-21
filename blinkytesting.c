/*
written by,
Lexy Andati, 
Wed 22 Jun 2016 09:01:19 PM EAT 
*/

#include "MK60DZ10.h"
//it workssssss!!!!!!!!


void gpio_initialize (void){

/*1. check the port associated with first led orange LED with PTA11 from the datasheet;
  2. clock that port to initialize it
  3. configure the portA pin 11 to gpio
  4. activate the pullup and down resistor function on the board 
  5. select pull down resistor to make the MCU a sink rather than a current source for the LED, now the current source will be 3.3v.*/
PORTA_PCR11 |= (PORT_PCR_MUX(0x1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK );
GPIOA_PDDR |= (uint32_t)1<<11;

	}

void led1(void){
/*write to the port registers to blink the orange LED. We choose (uint32_t) to typecast the shift (1<<11) to a 32 bit number because this register is a 32 bit register*/
		GPIOA_PTOR |=(uint32_t)1<<11;//output data values.
	}


void delay(void){
	/*we use volatile to tell the compiler that the value of counter will change during runtime of the program and therefore it should not optimize its value.*/
	int volatile counter; 
		counter=0;
			while (counter<3000000){
 				__asm__("nop");
 				 counter++;
 					}
 					counter=0;
			}

 int main (){

 	SystemInit();
	gpio_initialize();
		
	while (1){
 		led1();
 			delay();
			}
			
return 0;
}
