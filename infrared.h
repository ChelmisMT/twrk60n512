/*
 * infrared.h
 *
 * Copyright (c) 2016 David Muriuki
 * see the LICENCE file
 */
#include "MK60DZ10.h"
#ifndef INFRARED_H_
#define INFRARED_H_

#define CMTDisable(){ CMT_MSC = 0;}
#define CMTEnable(config) { CMT_MSC |= config;}
extern int periph_clk_khz;

void init_infrared(UART_MemMapPtr uartch);
void init_cmp(CMP_MemMapPtr cmpch);
void init_cmt(void);
void infraredsend(uint8_t ch);
char infraredread(void);
extern void uart_putchar (UART_MemMapPtr channel, uint8_t ch);
extern uint8_t uart_getchar (UART_MemMapPtr channel);
extern void init_uart(UART_MemMapPtr uartch, int sysclk, int baud);
extern void delay(void);
#endif /* INFRARED_H_ */
