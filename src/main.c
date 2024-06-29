#include <zephyr/kernel.h>

#define GPIO_LED_RED            22
#define GPIO_LED_GREEN          23
#define GPIO_LED_BLUE           24
#define UARTE_PIN_RX            8
#define UARTE_PIN_TX            7

/* UARTE Buffer */
uint8_t rxBuffer[255] = {0};
uint8_t txBuffer[255] = {0};
int main(void)
{
        // Configure GPIO
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);

        // Configure UARTE
        NRF_UARTE0->BAUDRATE = UARTE_BAUDRATE_BAUDRATE_Baud115200;
        NRF_UARTE0->PSEL.RXD = UARTE_PIN_RX;
        NRF_UARTE0->PSEL.TXD = UARTE_PIN_TX;
        NRF_UARTE0->RXD.PTR = (uint32_t)&rxBuffer[0];
        NRF_UARTE0->TXD.PTR = (uint32_t)&txBuffer[0];
        NRF_UARTE0->SHORTS = UARTE_SHORTS_ENDRX_STARTRX_Enabled << UARTE_SHORTS_ENDRX_STARTRX_Pos;
        NRF_UARTE0->RXD.MAXCNT = 1;
        NRF_UARTE0->ENABLE = 0x08;
        NRF_UARTE0->TASKS_STARTRX = 1;

        while(true){
                if(NRF_UARTE0->RXD.AMOUNT > 0){
                        printk("Datagaet : %c\n", rxBuffer[0]);
                        NRF_UARTE0->TASKS_STOPRX = 1;
                }
        }
        return 0;
}
