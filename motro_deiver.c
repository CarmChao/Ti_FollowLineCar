#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

Timer_A_PWMConfig pwmConfigLeft =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        3000,
        TIMER_A_CAPTURECOMPARE_REGISTER_1,
        TIMER_A_OUTPUTMODE_RESET_SET,
        0
};
Timer_A_PWMConfig pwmConfigRight =
{
        TIMER_A_CLOCKSOURCE_SMCLK,
        TIMER_A_CLOCKSOURCE_DIVIDER_1,
        3000,
        TIMER_A_CAPTURECOMPARE_REGISTER_4,
        TIMER_A_OUTPUTMODE_RESET_SET,
        0
};

void Motor_init(){
    //Output to TB6612 to control forward or backward
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN6);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN7);

    /* Configuring GPIO2.4 GPIO5.6 as peripheral output for PWM  */

    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN3,
            GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7,
            GPIO_PRIMARY_MODULE_FUNCTION);
}

//Constrain input value and set PWM
void setPWM(int left,int right){
    int Amplitude = 3000, deadValueLeft = 0, deadValueRight = 0;
    if(left >= 0){
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
        pwmConfigLeft.dutyCycle = left;
    }
    else{
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);

        pwmConfigLeft.dutyCycle = -left;

    }

    if(right >= 0){
        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN6);
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN7);
        pwmConfigRight.dutyCycle = right;
    }
    else{
        GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
        GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN7);
        pwmConfigRight.dutyCycle = -right;

    }
//    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigLeft);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfigRight);
}
