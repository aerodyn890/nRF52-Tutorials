/*
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

/* Button pin no. definition */
#define USER_BTN1       19
#define USER_BTN2       20

/* LED pin no. definition */
#define LED_RED         22
#define LED_GREEN       23
#define LED_BLUE        24

/* Define Event Lisenter */
void GPIOTE_IRQHandler();

/* Global Variables */
static uint8_t led_order = 0;

int main(void)
{
        // Debug message for start
        printk("Application start.\n");

        // Set gpio direction for LEDs & turn off
        NRF_GPIO->DIRSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
        NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);

        // Set Button GPIO as Input
        NRF_GPIO->PIN_CNF[USER_BTN1] = 0x0C;
        NRF_GPIO->PIN_CNF[USER_BTN2] = 0x0C;

        // Set Interrupt Event for buttons
        NRF_GPIOTE->INTENSET = 0x01;                    // Enable EVENT_IN[0]
        NRF_GPIOTE->INTENSET = (0x01 << 4);                   // Enable EVENT_IN[4]
        
        // Set GPIOTE for user button 1
        NRF_GPIOTE->CONFIG[0] = 0x01;                   // Set Event mode for EVENT_IN[0]
        NRF_GPIOTE->CONFIG[0] |= (USER_BTN1 << 8);      // Set pin no. for EVENT_IN[0]
        NRF_GPIOTE->CONFIG[0] |= (0x02 << 16);          // Set HiToLo polarity for EVENT_IN[0]
        
        // Set GPIOTE for user button 2
        NRF_GPIOTE->CONFIG[4] = 0x01;                   // Set Event mode for EVENT_IN[4]
        NRF_GPIOTE->CONFIG[4] |= (USER_BTN2 << 8);      // Set pin no. for EVENT_IN[4]
        NRF_GPIOTE->CONFIG[4] |= (0x02 << 16);          // Set HiToLo polarity for EVENT_IN[4]
        
        // Enable IRQHandler for interrupt
        IRQ_DIRECT_CONNECT(GPIOTE_IRQn, 0, GPIOTE_IRQHandler, 0);
        irq_enable(GPIOTE_IRQn);

        // Main loop
        while(true){
                k_usleep(1);
        }
        return 0;
}

void GPIOTE_IRQHandler(){
        // Interrupt event for button 1
        if(NRF_GPIOTE->EVENTS_IN[0] == 1){
                // Button 1 : Shift color to left
                NRF_GPIOTE->EVENTS_IN[0] = 0;
                if(led_order == 0){
                        led_order = 2;
                }else{
                        led_order--;
                }

                // Turn off all LEDs
                NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
                switch(led_order){
                        case 0:
                                printk("Button 1 pressed : LED Red\n");
                                NRF_GPIO->OUTCLR = (1 << LED_RED);
                        break;
                        case 1:
                                printk("Button 1 pressed : LED Green\n");
                                NRF_GPIO->OUTCLR = (1 << LED_GREEN);
                        break;
                        case 2:
                                printk("Button 1 pressed : LED Blue\n");
                                NRF_GPIO->OUTCLR = (1 << LED_BLUE);
                        break;
                }                
        }

        // Interrupt event for button 2
        if(NRF_GPIOTE->EVENTS_IN[4] == 1){
                // Button 2 : Shift color to right
                NRF_GPIOTE->EVENTS_IN[4] = 0;
                if(led_order == 2){
                        led_order = 0;
                }else{
                        led_order++;
                }

                // Turn off all LEDs
                NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
                switch(led_order){
                        case 0:
                                printk("Button 2 pressed : LED Red\n");
                                NRF_GPIO->OUTCLR = (1 << LED_RED);
                        break;
                        case 1:
                                printk("Button 2 pressed : LED Green\n");
                                NRF_GPIO->OUTCLR = (1 << LED_GREEN);
                        break;
                        case 2:
                                printk("Button 2 pressed : LED Blue\n");
                                NRF_GPIO->OUTCLR = (1 << LED_BLUE);
                        break;
                }  
        }
}