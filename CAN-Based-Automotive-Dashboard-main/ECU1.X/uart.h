/* 
 * File:   uart.h
 * Author: Hello
 * Created on 8 April, 2026, 08:05 PM
 */

//#ifndef SCI_H
//#define SCI_H
#ifndef UART_H
#define UART_H

#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch(unsigned char byte);
int puts(const char *s);
unsigned char getch(void);
unsigned char getch_with_timeout(unsigned short max_time);
unsigned char getche(void);

#endif
