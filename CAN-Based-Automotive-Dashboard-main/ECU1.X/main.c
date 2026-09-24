/*
 * File:   main.c
 * Author: Hello
 * Created on 8 April, 2026, 05:43 PM
 */


#include<xc.h>
#include "adc.h"
#include"digital_keypad.h"
#include"msg_id.h"
#include"uart.h"
#include"can.h"
#include"ecu1_sensor.h"
//#include"clcd.h"

static void init_config(void) {
    init_adc();
    init_digital_keypad();
    //    init_uart();
    init_can();
    //init_clcd();
}
uint16_t msg_id;
unsigned char data[8];
unsigned char len;

int main() {
    const unsigned char arr[][3]={"RG","NG","G1","G2","G3","G4","G5","CC"};
    init_config();

    while (1) {
        int speed = get_speed();

        char buff[2];
        buff[0] = (speed / 10) + '0';
        buff[1] = (speed % 10) + '0';
        buff[2]='\0';

        can_transmit(SPEED_MSG_ID, buff, 2);
        for (int wait = 2000; wait--;);

        char gear = get_gear_pos();
        can_transmit(GEAR_MSG_ID, &gear, 1);
        for (int wait = 2000; wait--;);

    }
}
