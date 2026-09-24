/*
 * File:   clcd.c
 * Author: Hello
 * Created on 9 April, 2026, 07:12 AM
 */


#include <xc.h>
#include "clcd.h"

void clcd_write(unsigned char byte, unsigned char control_bit)
{
	CLCD_RS = control_bit;         //Setting as command mode
	CLCD_PORT = byte;              //Selecting the address

	/* Should be atleast 200ns */
	CLCD_EN = HI;           
	CLCD_EN = LO;                  //Genrating the pulse

	PORT_DIR = INPUT;              //changing the RD7 to read mode
	CLCD_RW = HI;                  //setting the read mode in R/W PIN
	CLCD_RS = INSTRUCTION_COMMAND; //setting the instruction mode in register select PIN

	do
	{
		CLCD_EN = HI;
		CLCD_EN = LO;
	} while (CLCD_BUSY);           //Genrating the clock pulse until RD7 is become 0

	CLCD_RW = LO;                  //Setting the write mode in R/W mode
	PORT_DIR = OUTPUT;             //Setting RD7 as output
}

void init_clcd()
{
	/* Set PortD as output port for CLCD data */
	TRISD = 0x00;
	/* Set PortC as output port for CLCD control */
	TRISC = TRISC & 0xF8;

	CLCD_RW = LO;

	
     /* Startup Time for the CLCD controller */
    __delay_ms(30);
    
    /* The CLCD Startup Sequence */
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(4100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(100);
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND	);
    __delay_us(1); 
    
    CURSOR_HOME;
    __delay_us(100);
    TWO_LINE_5x8_MATRIX_8_BIT;
    __delay_us(100);
    CLEAR_DISP_SCREEN;
    __delay_us(500);
    DISP_ON_AND_CURSOR_OFF;
    __delay_us(100);
}

void clcd_print(const unsigned char *data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0')
	{
		clcd_write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(const unsigned char data, unsigned char addr)
{
	clcd_write(addr, INSTRUCTION_COMMAND);
	clcd_write(data, DATA_COMMAND);
}