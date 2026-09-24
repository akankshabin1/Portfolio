/*
 * File:   ecu2_sensor.c
 * Author: Hello
 * Created on 8 April, 2026, 11:15 PM
 */


#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include"digital_keypad.h"  

unsigned int adc_value = 0;
unsigned char key;

unsigned char digit[] = {0xE7,0x21,0xCB,0x6B,0x2D,0x6E,0xEE,0x23,0xEF,0x6F};
unsigned char ssd[4];
    
unsigned int rpm = 0;
char RPM[5];
uint16_t get_rpm()
{
    //Implement the rpm function
    adc_value = read_adc(RPM_ADC_CHANNEL);

        rpm = (adc_value * 6000UL) / 1023;

        RPM[0] = (rpm / 1000)%10+'0';
        RPM[1] = (rpm / 100)%10+'0';
        RPM[2] = (rpm / 10)%10+'0';
        RPM[3] = (rpm % 10)+'0';
        RPM[4] = '\0';
    
        //can_transmit(RPM_MSG_ID,RPM,4);
        return rpm;
}

uint16_t get_engine_temp()   //Optional
{
    //Implement the engine temperature function
}

IndicatorStatus process_indicator()
{
    //Implement the indicator function
    
    char key = read_digital_keypad(STATE_CHANGE); 
      
    static IndicatorStatus state=e_ind_off;

    //can_transmit(INDICATOR_MSG_ID,data,1);
      
    if(key == SWITCH1)
    {
        state=e_ind_left;
    }
    else if(key == SWITCH2)
    {
        state=e_ind_right;
    }
    else if(key == SWITCH3)
    {
        state=e_ind_hazard;
    }
    else if(key == SWITCH4)
    {
        state=e_ind_off;
    }
    uint8_t data[1];
    data[0]=state;
    
    can_transmit(INDICATOR_MSG_ID,data,1);
    for (int wait = 2000; wait>0;wait--);
    //__delay_ms(80);
    return state;
    
}