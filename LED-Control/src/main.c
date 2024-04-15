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

/* LED pin no. definition */
#define LED_RED         22
#define LED_GREEN       23
#define LED_BLUE        24

int main(void)
{
        // Debug message for start
        printk("Application start.\n");

        // Set gpio direction for LEDs & turn off
        NRF_GPIO->DIRSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
        NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);

        // Main loop
        while(true){
                // Turn off all LEDs & Turn on Red
                NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
                NRF_GPIO->OUTCLR = (1 << LED_RED);
                printk("Red LED on\n");
                k_msleep(1000);

                // Turn off all LEDs & Turn on Green
                NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
                NRF_GPIO->OUTCLR = (1 << LED_GREEN);
                printk("Green LED on\n");
                k_msleep(1000);

                // Turn off all LEDs & Turn on Blue
                NRF_GPIO->OUTSET = (1 << LED_RED) | (1 << LED_GREEN) | (1 << LED_BLUE);
                NRF_GPIO->OUTCLR = (1 << LED_BLUE);
                printk("Blue LED on\n");
                k_msleep(1000);
        }
        return 0;
}
