/*
 * infrared.c
 *
 * Copyright (c) 2015 David Muriuki
 * see the LICENCE file
 */
#include "infrared.h"


void init_infrared(UART_MemMapPtr uartch){
	//initialize uart0 as infrared port through CMP0
	init_uart(UART0_BASE_PTR,periph_clk_khz,115200);
	UART_IR_REG(uartch) |= UART_IR_IREN_MASK;
	UART_IR_REG(uartch) |= UART_IR_TNP(0x00);
	init_cmp(CMP0_BASE_PTR);
	init_cmt();
}

void init_cmt(void){
	//disable CMT
	CMTDisable();
	//Clock Divide Prescaler, source divide by 1
	CMT_MSC |= CMT_MSC_CMTDIV(0);
	//Generates the carrier frequency of 38kHz (fCG typically 30–60 kHz)
	//it uses peripheral bus clock as source = 9600Khz
	CMT_CGH1 = 0x4c; //9600000*0.3/38000~=76 = 0x4C clock_on
	CMT_CGL1 = 0xb1; //9600000*0.7/38000~=177= 0xB1 clock_off
	//Configure the modulator mark and space
	//0x40
	CMT_CMD1 = 0x00;
	CMT_CMD2 = 0x40;
	//0x41
	CMT_CMD3 = 0x00;
	CMT_CMD4 = 0x41;
	//configure time mode
	CMT_MSC &= ~(CMT_MSC_BASE_MASK|CMT_MSC_FSK_MASK);
	//configure signals
	CMT_OC |= CMT_OC_CMTPOL_MASK;//CMT_IRO signal is active high
	CMT_OC |= CMT_OC_IROPEN_MASK;//CMT_IRO signal enabled as output
	//enable CMT, pass whether to set MCGEN bit
	CMTEnable(0x1u);
}

void init_cmp(CMP_MemMapPtr cmpch){
	//disable comparator while configuring
	CMP_CR1_REG(cmpch) &= ~(CMP_CR1_OPE_MASK | CMP_CR1_EN_MASK);
	//PMUX is IN0  by default, but enable PMUX
	CMP_MUXCR_REG(cmpch) |= CMP_MUXCR_PEN_MASK;
	//enable comparator
	CMP_CR1_REG(cmpch) |= (CMP_CR1_OPE_MASK | CMP_CR1_EN_MASK);
}

void infraredsend(uint8_t ch){
	CMTEnable(0x1u);
	uart_putchar (UART0_BASE_PTR,ch);
	delay();
	CMTDisable();
}

char infraredread(void){
	return uart_getchar(UART0_BASE_PTR);
}
