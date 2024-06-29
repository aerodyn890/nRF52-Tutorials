#include <zephyr/kernel.h>

/* Pin definition */
#define GPIO_LED_RED            22
#define GPIO_LED_GREEN          23
#define GPIO_LED_BLUE           24
#define UARTE_PIN_RX            8
#define UARTE_PIN_TX            7

int main(void)
{
        // GPIO Configuration
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);

        // UARTE Configuration
        
        while(true){

        }
        return 0;
}
