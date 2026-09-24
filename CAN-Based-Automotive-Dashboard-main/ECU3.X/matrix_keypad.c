/*
 * File:   matrix_keypad.c
 * Author: Hello
 * Created on 9 April, 2026, 07:07 AM
 */


#include <xc.h>
#include"matrix_keypad.h"

void init_matrix_keypad()
{
    RBPU=0;    
    
    TRISB = TRISB &0x1F;  
    
    TRISB=TRISB | 0x1E;  
    
    PORTB = PORTB | 0xE0;  
}

unsigned char scan_key(void)
{
    RW1 = 0 ;
    RW2=RW3=1;
    
    if(COL1==0)
        return SW1;
    
    RW2=0;
    RW1=RW3=1;
    
    if(COL1==0)
        return SW2;
    
    RW3=0;
    RW1=RW2=1;
    
    if(COL1==0)
        return SW3;
    
    return 0xFF;
}
unsigned char read_matrix_keypad(unsigned char triggering_method)
{
 static unsigned char once =1;
 if(triggering_method == LEVEL)
 {
     return scan_key();
 }
 else if(triggering_method == EDGE)
 {
     unsigned char key = scan_key();
     if((key != 0xFF ) && (once ==1))
     {
         once = 0;
         return key;
     }
     else if(key == 0xFF)
     {
         once =1;
     }
 }
    return 0xFF;
}