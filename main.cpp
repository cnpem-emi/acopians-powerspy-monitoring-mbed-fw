/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"


int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);
    DigitalOut led3(LED3);
    DigitalOut led4(LED4);

    while (true) {
        //led4 = !led4;
        //osDelay(100);
        led3 = !led3;
        osDelay(150); 
        //led2 = !led2;
        //osDelay(200);
        //led1 = !led1;
        //osDelay(250);
        
        
    }
}
