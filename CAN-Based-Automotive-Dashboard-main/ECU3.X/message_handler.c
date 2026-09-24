  /*
 * File:   message_handler.c
 * Author: Hello
 * Created on 9 April, 2026, 07:05 AM
 */

#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"
#include "adc.h"
#include "matrix_keypad.h"

volatile unsigned char led_state = 0;
/* Global Variables */

uint16_t msg_id;
uint8_t arr[8];
uint8_t len;

unsigned int rpm = 0;
unsigned int speed = 0;
unsigned int adc_value = 0;

unsigned char buff[3];
unsigned char RPM[5];

unsigned char key;
static unsigned char gear_index = 0;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    clcd_putch(data[0], LINE2(0));
    clcd_putch(data[1], LINE2(1));
}

void handle_gear_data(uint8_t *data, uint8_t len)
{
    unsigned char gear_arr[][3] ={"RG","NG","G1","G2","G3","G4","G5","CC"};
    gear_index=*data;
    if(gear_index < 8)
    {
    clcd_print(gear_arr[gear_index], LINE2(3));
    }
    
}

void handle_rpm_data(uint8_t *data, uint8_t len)
{
    if(len>=4)
    {
    clcd_putch(data[0],LINE2(6));
    clcd_putch(data[1], LINE2(7));
    clcd_putch(data[2],LINE2(8));
    clcd_putch(data[3],LINE2(9)); 
    }
}

void handle_indicator_data(uint8_t *data, uint8_t len)
{
    // Indicator logic can be added here
    led_state = !led_state;
    switch(data[0])
    {
        case 0:
            if(led_state)
                LEFT_IND_ON();
            else
                LEFT_IND_OFF();
            
            RIGHT_IND_OFF();
            clcd_putch('<',LINE2(11));
            clcd_putch('-',LINE2(12));
            clcd_putch('L',LINE2(13));
            break;

        case 1:
            if(led_state)
                RIGHT_IND_ON();
            else
                RIGHT_IND_OFF();
            
            LEFT_IND_OFF();
            clcd_putch('-',LINE2(11));
            clcd_putch('>',LINE2(12));
            clcd_putch('R',LINE2(13));
            break;

        case 2:
            if(led_state)
            {
                RIGHT_IND_ON();
                LEFT_IND_ON();
            }
            else
            {
                RIGHT_IND_OFF();
                LEFT_IND_OFF();
            }
            clcd_putch('<',LINE2(11));
            clcd_putch('H',LINE2(12));
            clcd_putch('>',LINE2(13));
            break;
            
        case 3:
            RIGHT_IND_OFF();
            LEFT_IND_OFF();
            clcd_putch('O',LINE2(11));
            clcd_putch('F',LINE2(12));
            clcd_putch('F',LINE2(13));
            break;
    }
}

void process_canbus_data()
{
    can_receive(&msg_id, arr, &len);
    arr[len+2] = '\0';
 
    //clcd_print("T",LINE2(15));
            if(msg_id == SPEED_MSG_ID)
            {
//                clcd_print("T1",LINE2(14));
                handle_speed_data(arr,len);  
            }
            else if(msg_id == RPM_MSG_ID)
            {
                //clcd_print("T2",LINE2(14));
                handle_rpm_data(arr,len);
            }
            else if(msg_id == GEAR_MSG_ID)
            {
                //clcd_print("T3",LINE1(14));
                handle_gear_data(&arr[0],len);
            }   
            else if(msg_id == INDICATOR_MSG_ID)
            {
               // clcd_print("T4",LINE2(14));
                handle_indicator_data(arr,len);
            }
//            else
//            {
//               // clcd_print("Te",LINE2(14));
//                clcd_print("NO DATA",LINE2(0));
//            }
        
}