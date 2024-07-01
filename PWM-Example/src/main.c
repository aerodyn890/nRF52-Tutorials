/*
        PWM for LED Control Example
        Roverdyn Inc.
        2024. 7. 2.

        MIT License

        Copyright (c) 2024. Seonguk Jeong, Roverdyn Inc.

        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
        in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
        OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
        SOFTWARE.
*/

#include <zephyr/kernel.h>

/* GPIO LED Configuration */
#define GPIO_LED_RED            22
#define GPIO_LED_GREEN          23
#define GPIO_LED_BLUE           24

/* PWM Counter */
uint16_t dutyCycle[4] = {0, 0, 0, 0};
int main(void){
        printk("PWM Application started.\n");
        // PWM Configurations
        NRF_PWM0->PRESCALER = 0x00;
        NRF_PWM0->MODE = 0x01;
        NRF_PWM0->DECODER = PWM_DECODER_LOAD_Individual << PWM_DECODER_LOAD_Pos;
        NRF_PWM0->SEQ[0].PTR = (uint32_t)dutyCycle;
        NRF_PWM0->SEQ[0].CNT = 4;
        NRF_PWM0->SEQ[0].REFRESH = 0;
        NRF_PWM0->SEQ[0].ENDDELAY = 0;
        NRF_PWM0->COUNTERTOP = 32000;
        NRF_PWM0->PSEL.OUT[0] = GPIO_LED_RED;
        NRF_PWM0->PSEL.OUT[1] = GPIO_LED_GREEN;
        NRF_PWM0->PSEL.OUT[2] = GPIO_LED_BLUE;
        NRF_PWM0->ENABLE = 0x01;
        NRF_PWM0->TASKS_SEQSTART[0] = 1;
        
        while(true){
                // Main loop
                dutyCycle[0] += 100;
                dutyCycle[1] += 100;
                if(dutyCycle[0] > 32000){
                        dutyCycle[0] = 0;
                        dutyCycle[1] = 0;
                }
                NRF_PWM0->TASKS_SEQSTART[0] = 1;
                k_msleep(10);
        }
        return 0;
}
