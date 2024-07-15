/*
        Roverdyn Inc. Timer Interrupt Example.
        2024. 7. 15.

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

#define GPIO_LED_RED    22
#define GPIO_LED_GREEN  23
#define GPIO_LED_BLUE   24

// Interrupt Handler
void TIMER2_IRQHandler();
int main(void)
{
        // GPIO Configuration
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);

        /*
                Timer Interrupt Setting
                Timer Bitmode : 32bit => Max. 2^32 counts
                Mode : Timer Mode
                Interrupt Event Channel : EVENT_COMPARE[0]
                Prescaler = 2^9 = 512
                1sec counts : 16000000/512 = 31250 = 1sec
                Comapre Counter(CC) : 15625 -> 31250 / 15625 = 0.5 period 
        */
        NRF_TIMER2->BITMODE = TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;
        NRF_TIMER2->PRESCALER = 9 << TIMER_PRESCALER_PRESCALER_Pos;
        NRF_TIMER2->MODE = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
        NRF_TIMER2->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
        NRF_TIMER2->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
        NRF_TIMER2->CC[0] = 15625;      // Interrupt Period : 0.5sec(31250/2 = 0.5)
        NRF_TIMER2->TASKS_START = 1;
        
        // Enable IRQn
        IRQ_DIRECT_CONNECT(TIMER2_IRQn, 0, TIMER2_IRQHandler, 0);
        irq_enable(TIMER2_IRQn);
        
        while(true){
                k_usleep(1);        // Wait For Interrupt
        }
        return 0;
}

void TIMER2_IRQHandler(){
        // TIMER2 Interrupt Handler
        static bool isLedOn = false;
        if(NRF_TIMER2->EVENTS_COMPARE[0] == 1){
                NRF_TIMER2->EVENTS_COMPARE[0] = 0;
                if(!isLedOn){
                        isLedOn = true;
                        NRF_GPIO->OUTCLR = (1 << GPIO_LED_GREEN);
                }else{
                        isLedOn = false;
                        NRF_GPIO->OUTSET = (1 << GPIO_LED_GREEN);
                }
        }
}