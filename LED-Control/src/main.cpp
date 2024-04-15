/*
        LED Control Tutorials
        Feb. 19, 2024
        Author : S.W. Jeong(Roverdyn Inc.)
        More information : https://www.roverdyn.com
*/
#include <zephyr/kernel.h>
#define GPIO_LED_RED            24
#define GPIO_LED_GREEN          23
#define GPIO_LED_BLUE           22
int main(void)
{
        // Setting GPIO Direction
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        
        // Turn off all LEDs
        NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        while(true){

        }
        return 0;
}
