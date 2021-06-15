
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 2021  <chao: wangchao9214@live.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/******************************************************************************
 * main file to start the program
 *
 * Author: 
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

extern Timer_A_PWMConfig pwmConfigLeft;
extern Timer_A_PWMConfig pwmConfigRight;


int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    extern void Motor_init();
    extern void setPWM(int left, int right);

    Motor_init();
    setPWM(5000, -5000);

    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN5);
    while(1)
    {
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN5);
        int i=0;
        for(i=1000000; i>0; i--);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN5);
        for(i=1000000; i>0; i--);
    }
}
