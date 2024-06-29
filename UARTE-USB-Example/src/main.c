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

/* Pin definition */
#define GPIO_LED_RED            22
#define GPIO_LED_GREEN          23
#define GPIO_LED_BLUE           24
#define UARTE_PIN_RX            8
#define UARTE_PIN_TX            7

/* UARTE Buffer */
uint8_t rxBuffer[255] = {0}, txBuffer[255] = {0};

/* UARTE Functions */
void write(uint8_t *data, uint8_t length);
void UARTE_Listener();
int main(void)
{
        // GPIO Configuration
        NRF_GPIO->DIRSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
        NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);

        // UARTE Configuration
        NRF_UARTE0->BAUDRATE = UARTE_BAUDRATE_BAUDRATE_Baud115200;
        NRF_UARTE0->PSEL.RXD = UARTE_PIN_RX;
        NRF_UARTE0->PSEL.TXD = UARTE_PIN_TX;
        NRF_UARTE0->TXD.PTR = (uint32_t)txBuffer;
        NRF_UARTE0->RXD.PTR = (uint32_t)rxBuffer;
        NRF_UARTE0->SHORTS = UARTE_SHORTS_ENDRX_STARTRX_Enabled << UARTE_SHORTS_ENDRX_STARTRX_Pos;
        NRF_UARTE0->INTENSET = UARTE_INTEN_RXDRDY_Enabled << UARTE_INTEN_RXDRDY_Pos;
        NRF_UARTE0->INTENSET = UARTE_INTEN_ENDRX_Enabled << UARTE_INTEN_ENDRX_Pos;
        NRF_UARTE0->INTENSET = UARTE_INTEN_ENDTX_Enabled << NFCT_INTEN_ENDTX_Pos;
        NRF_UARTE0->ENABLE = 0x08;
        NRF_UARTE0->RXD.MAXCNT = 255;
        NRF_UARTE0->TASKS_STARTRX = 1;
        
        // Enable IRQ Handler
        IRQ_DIRECT_CONNECT(UARTE0_UART0_IRQn, 0, UARTE_Listener, 0);
        irq_enable(UARTE0_UART0_IRQn);

        while(true){
                k_usleep(10);
        }
        return 0;
}

void write(uint8_t *data, uint8_t length){
        // Function for UARTE Write
        memcpy(txBuffer, data, length);
        NRF_UARTE0->TXD.MAXCNT = length;
        NRF_UARTE0->TASKS_STARTTX = 1;
}

void UARTE_Listener(){
        // Function for UARTE RXDRDY interrupt
        static uint8_t order = 0;
        if(NRF_UARTE0->EVENTS_ENDTX == 1){
                // Clear Tx Buffer
                NRF_UARTE0->EVENTS_ENDTX = 0;
                memset(txBuffer, 0x00, sizeof(uint8_t));
        }

        if(NRF_UARTE0->EVENTS_RXDRDY == 1){
                // Clear and Stop RxBuffer
                printk("RX data received : %c\r\n", rxBuffer[order]);
                write(&rxBuffer[order], 1);
                if(rxBuffer[order] == 0x0D){
                        NRF_UARTE0->TASKS_STOPRX = 1;
                }else{
                        order++;
                }
                NRF_UARTE0->EVENTS_RXDRDY = 0;
        }

        if(NRF_UARTE0->EVENTS_ENDRX == 1){
                // Clear and Stop RxBuffer
                printk("%d byte received.\r\n", strlen(rxBuffer));
                write(rxBuffer, strlen(rxBuffer));

                // Control LED
                if(strncmp(rxBuffer, "off", 3) == 0){
                        NRF_GPIO->OUTSET = (1 << GPIO_LED_RED) | (1 << GPIO_LED_GREEN) | (1 << GPIO_LED_BLUE);
                }else if(strncmp(rxBuffer, "red", 3) == 0){
                        NRF_GPIO->OUTCLR = 1 << GPIO_LED_RED;
                }else if(strncmp(rxBuffer, "green", 3) == 0){
                        NRF_GPIO->OUTCLR = 1 << GPIO_LED_GREEN;
                }else if(strncmp(rxBuffer, "blue", 3) == 0){
                        NRF_GPIO->OUTCLR = 1 << GPIO_LED_BLUE;
                }

                // Clear parameter
                order = 0;
                memset(rxBuffer, 0x00, sizeof(uint8_t));
                NRF_UARTE0->EVENTS_ENDRX = 0;
        }
}