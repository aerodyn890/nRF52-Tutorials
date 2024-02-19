/*
        LED Control Tutorials
        Feb. 19, 2024
        Author : S.W. Jeong(Roverdyn Inc.)
        More information : https://www.roverdyn.com
*/
#include <zephyr/kernel.h>
#define GPIO_LED_RED            22
#define GPIO_LED_GREEN          23
#define GPIO_LED_BLUE           24
int main(void)
{
        // Setting GPIO Direction
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        
        // Turn off all LEDs
        NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);

        // RTT Log
        printk("RTT LOG : Start LED control tutorial.\n");
        while(true){
                NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
                NRF_GPIO->OUTCLR = (1 << GPIO_LED_RED);
                printk("RTT LOG : RED\n");
                k_msleep(1000);
                NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
                NRF_GPIO->OUTCLR = (1 << GPIO_LED_GREEN);
                printk("RTT LOG : GREEN\n");
                k_msleep(1000);
                NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
                NRF_GPIO->OUTCLR = (1 << GPIO_LED_BLUE);
                printk("RTT LOG : BLUE\n");
                k_msleep(1000);
        }
        return 0;
}
