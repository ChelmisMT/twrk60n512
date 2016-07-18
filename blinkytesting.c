/*
written by,
Lexy Andati, 
Wed 22 Jun 2016 09:01:19 PM EAT 
*/
#include "Mk60.h"
#include "MK60DZ10.h"
//it workssssss!!!!!!!!


void gpio_initialize (void){

//check the port associated with first led orange LED with PTA11 from the datasheet;
//clock that port to initialize it
	//SIM_SCG5 |= (SIM_SCG5_PORT_A_MASK); all ports already clocked in the system init which is in MK60DZ10.H file

//configure the portA pin 11 to gpio, interrupt on rising edge, activate the pullup and down resistor function on the board , select pull down resistor to make the MCU a sink rather than a current source for the LED, now the current source will be 3.3v.
//PORTA_PCR19 |= (PORT_PCR_MUX(0x1) | (PORT_PCR_IRQC(0X9)) | PORT_PCR_PE(0x1) | PORT_PCR_PS(0x1) );
 
 
	PA->PCR[11].mux = 0x01;
	PA->PCR[11].irqc = 0xA;
	PA->PCR[11].pe = 0x01;	//enabling the pull function.
	PA->PCR[11].ps = 0x00; // selecting the pull down resisitor.

//configure the directionality of the pin to the output
	GPIOA->PDDR.bit_reg.bit11 = out;
	
}



 int main (){

 	SystemInit();
	gpio_initialize();
	
		
	int volatile counter; //we use volatile to tell the compiler that the value of counter will change during runtime of the program and therefore it should not optimize its value.
	
	
	while (1){
 		
		counter=0;
		// write to the port registers to blink the orange LED.
		GPIOA_PTOR |=(uint32_t)1<<11;//output data values.
		
		 	
			while (counter<3000000){
 				__asm__("nop");
 				 counter++;
 					}
 
 		
 			
		}
return 0;
}
