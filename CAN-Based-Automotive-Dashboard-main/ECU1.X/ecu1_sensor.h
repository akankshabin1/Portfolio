/* 
 * File:   ecu1_sensor.h
 * Author: Hello
 * Created on 8 April, 2026, 08:03 PM
 */

#ifndef ECU1_SENSOR_H
#define	ECU1_SENSOR_H

#include <stdint.h>
#include "digital_keypad.h"
#include <xc.h>

#define MAX_GEAR 6
#define SPEED_ADC_CHANNEL 0x04
#define GEAR_UP             SWITCH1
#define GEAR_DOWN           SWITCH2
#define COLLISION           SWITCH3

uint16_t get_speed();
unsigned char get_gear_pos();
#endif	/* ECU1_SENSOR_H */

