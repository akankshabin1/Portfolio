/*
 * File:   main.c
 * Author: Hello
 * Created on 9 April, 2026, 07:12 AM
 */


#include <xc.h>
//#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
#include "timer0.h"
#include"adc.h"
#include"matrix_keypad.h"

void init_leds() {
    TRISB = 0x00; 
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    
    init_leds();
    init_can();
//    init_adc();
//    init_matrix_keypad();
//    init_timer0();
    // Enable Interrupts
//    PEIE = 1;
//    GIE = 1;
}
uint8_t data[8];
uint8_t len;
void main(void) {
    // Initialize peripherals
    init_config();

    /* ECU1 main loop */
    clcd_print("SP GE RPM  IND",LINE1(0));
    while (1) 
    {
        // Read CAN Bus data and handle it
        process_canbus_data();
//         handle_indicator_data(data,len);
//         __delay_ms(300);
    }
}
