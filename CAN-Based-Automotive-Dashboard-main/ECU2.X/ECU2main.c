/*
 * File:   ECU2main.c
 * Author: Hello
 * Created on 8 April, 2026, 11:06 PM
 */

#include <xc.h>
#include "adc.h"
#include"can.h"
#include "digital_keypad.h"
#include"msg_id.h"
#include"ecu2_sensor.h"
#include"uart.h"

uint16_t msg_id;
unsigned char len;

void init_config(void)
{
    init_adc();
    init_digital_keypad();
    init_can();
}

void main(void) 
{
    TRISB = 0x00;      
    PORTB = 0x00;

    init_config();

    while(1)
    {
        unsigned int RPM = get_rpm();
        
        char buff[5];
        buff[0]=(RPM/1000)+'0';
        buff[1]=((RPM/100)%10)+'0';
        buff[2]=((RPM/10)%10)+'0';
        buff[3]=(RPM%10)+'0';
        buff[4]='\0';
        
        can_transmit(RPM_MSG_ID,buff,4);
        for (int wait = 2000; wait>0;wait--);
       
         process_indicator();
        
        }
}
