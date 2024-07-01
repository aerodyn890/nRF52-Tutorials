/*
        Roverdyn Inc. SAADC Example.
        2024. 6. 30.

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

/* SAADC Sample Rate */
#define SAADC_SAMPLERATE 1024

/* SAADC interrupt functions */
void SAADC_IRQHandler();

/* SAADC  Buffer */
uint8_t saadc_buffer[255] = {0};

int main(void)
{
        printk("SAADC Example application start.\n");
        // SAADC Configurations
        NRF_SAADC->SAMPLERATE = SAADC_SAMPLERATE_MODE_Timers << SAADC_SAMPLERATE_MODE_Pos;
        NRF_SAADC->SAMPLERATE |= SAADC_SAMPLERATE << SAADC_SAMPLERATE_CC_Pos;
        NRF_SAADC->RESOLUTION = SAADC_RESOLUTION_VAL_14bit << SAADC_RESOLUTION_VAL_Pos;
        NRF_SAADC->CH[0].CONFIG |= SAADC_CH_CONFIG_GAIN_Gain1_6 << SAADC_CH_CONFIG_GAIN_Pos;
        NRF_SAADC->CH[0].CONFIG |= SAADC_CH_CONFIG_TACQ_10us << SAADC_CH_CONFIG_TACQ_Pos;
        NRF_SAADC->CH[0].PSELP = SAADC_CH_PSELP_PSELP_AnalogInput0;
        NRF_SAADC->CH[0].PSELN = 0;
        NRF_SAADC->RESULT.PTR = (uint32_t)saadc_buffer;
        NRF_SAADC->RESULT.MAXCNT = 255;
        NRF_SAADC->INTENSET = SAADC_INTEN_CALIBRATEDONE_Enabled << SAADC_INTEN_CALIBRATEDONE_Pos;
        NRF_SAADC->INTENSET |= SAADC_INTEN_RESULTDONE_Enabled << SAADC_INTEN_RESULTDONE_Pos;
        NRF_SAADC->ENABLE = 0x01;
        
        // Interrupt Settings
        IRQ_DIRECT_CONNECT(SAADC_IRQn, 0, SAADC_IRQHandler, 0);
        irq_enable(SAADC_IRQn);

        // SAADC Calibration
        NRF_SAADC->TASKS_START = 1;
        NRF_SAADC->TASKS_CALIBRATEOFFSET = 1;

        while(true){
                // Main loop
                k_msleep(100);
                //printk("%d\n", saadc_buffer[0]);
        }
        return 0;
}

void SAADC_IRQHandler(){
        // Fucntions for SAADC Interrupt
        static uint8_t order = 0;
        if(NRF_SAADC->EVENTS_CALIBRATEDONE == 1){
                NRF_SAADC->EVENTS_CALIBRATEDONE = 0;
                printk("EVENTS_CALIBRATEDONE\n");
                NRF_SAADC->TASKS_SAMPLE = 1;
        }

        if(NRF_SAADC->EVENTS_RESULTDONE == 1){
                NRF_SAADC->EVENTS_RESULTDONE = 0;
                //printk("EVENTS_RESULTDONE\n");
                printk("%03d : %d\n", order, saadc_buffer[order++]);
                if(order == 255){
                        order = 0;
                }
        }
}