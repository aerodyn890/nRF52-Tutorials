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

// Register definitions
#define ICM42670_MCLK_RDY                0x00
#define ICM42670_DEVICE_CONFIG           0x01
#define ICM42670_SIGNAL_PATH_REST        0x02
#define ICM42670_DRIVE_CONFIG1           0x03
#define ICM42670_DRIVE_CONFIG2           0x04
#define ICM42670_DRIVE_CONFIG3           0x05
#define ICM42670_INT_CONFIG              0x06
#define ICM42670_TEMP_DATA1              0x09
#define ICM42670_TEMP_DATA0              0x0A
#define ICM42670_ACCEL_DATA_X1           0x0B
#define ICM42670_ACCEL_DATA_X0           0x0C
#define ICM42670_ACCEL_DATA_Y1           0x0D
#define ICM42670_ACCEL_DATA_Y0           0x0E
#define ICM42670_ACCEL_DATA_Z1           0x0F
#define ICM42670_ACCEL_DATA_Z0           0x10
#define ICM42670_GYRO_DATA_X1            0x11
#define ICM42670_GYRO_DATA_X0            0x12
#define ICM42670_GYRO_DATA_Y1            0x13
#define ICM42670_GYRO_DATA_Y0            0x14
#define ICM42670_GYRO_DATA_Z1            0x15
#define ICM42670_GYRO_DATA_Z0            0x16
#define ICM42670_TMST_FSYNCH             0x17
#define ICM42670_TMST_FSYNCL             0x18
#define ICM42670_APEX_DATA4              0x1D
#define ICM42670_APEX_DATA5              0x1E
#define ICM42670_PWR_MGMT0               0x1F
#define ICM42670_GYRO_CONFIG0            0x20
#define ICM42670_ACCEL_CONFIG0           0x21
#define ICM42670_TEMP_CONFIG0            0x22
#define ICM42670_GYRO_CONFIG1            0x23
#define ICM42670_ACCEL_CONFIG1           0x24
#define ICM42670_APEX_CONFIG0            0x25
#define ICM42670_APEX_CONFIG1            0x26
#define ICM42670_WOM_CONFIG              0x27
#define ICM42670_FIFO_CONFIG1            0x28
#define ICM42670_FIFO_CONFIG2            0x29
#define ICM42670_FIFO_CONFIG3            0x30
#define ICM42670_INT_SOURCE0             0x2B
#define ICM42670_INT_SOURCE1             0x2C
#define ICM42670_INT_SOURCE3             0x2D
#define ICM42670_INT_SOURCE4             0x2E
#define ICM42670_FIFO_LOST_PKT0          0x2F
#define ICM42670_FIFO_LOST_PKT1          0x30
#define ICM42670_APEX_DATA0              0x31
#define ICM42670_APEX_DATA1              0x32
#define ICM42670_APEX_DATA2              0x33
#define ICM42670_APEX_DATA3              0x34
#define ICM42670_INTF_CONFIG0            0x35
#define ICM42670_INTF_CONFIG1            0x36
#define ICM42670_INT_STATUS_DRDY         0x39
#define ICM42670_INT_STATUS              0x3A
#define ICM42670_INT_STATUS2             0x3B
#define ICM42670_INT_STATUS3             0x3C
#define ICM42670_FIFO_COUNTH             0x3D
#define ICM42670_FIFO_COUNTL             0x3E
#define ICM42670_FIFO_DATA               0x3F
#define ICM42670_WHO_AM_I                0x75
#define ICM42670_BLK_SEL_W               0x79
#define ICM42670_MADDR_W                 0x7A
#define ICM42670_M_W                     0x7B
#define ICM42670_BLK_SEL_R               0x7C
#define ICM42670_MADDR_R                 0x7D
#define ICM42670_M_R                     0x7E

// USER BANK 1
#define ICM42670_TMST_CONFIG1            0x00
#define ICM42670_FIFO_CONFIG5            0x01    
#define ICM42670_FIFO_CONFIG6            0x02
#define ICM42670_FSYNC_CONFIG            0x03
#define ICM42670_INT_CONFIG0             0x04
#define ICM42670_INT_CONFIG1             0x05
#define ICM42670_SENSOR_CONFIG3          0x06
#define ICM42670_ST_CONFIG               0x13
#define ICM42670_SELFTEST                0x14
#define ICM42670_INTF_CONFIG6            0x23
#define ICM42670_INTF_CONFIG10           0x25
#define ICM42670_INTF_CONFIG7            0x28
#define ICM42670_OTP_CONFIG              0x2B
#define ICM42670_INT_SOURCE6             0x2F
#define ICM42670_INT_SOURCE7             0x30
#define ICM42670_INT_SOURCE8             0x31
#define ICM42670_INT_SOURCE9             0x32
#define ICM42670_INT_SOURCE10            0x33
#define ICM42670_APEX_CONFIG2            0x44
#define ICM42670_APEX_CONFIG3            0x45
#define ICM42670_APEX_CONFIG4            0x46
#define ICM42670_APEX_CONFIG5            0x47
#define ICM42670_APEX_CONFIG9            0x48
#define ICM42670_APEX_CONFIG10           0x49
#define ICM42670_APEX_CONFIG11           0x4A
#define ICM42670_ACCEL_WOM_X_THR         0x4B
#define ICM42670_ACCEL_WOM_Y_THR         0x4C
#define ICM42670_ACCEL_WOM_Z_THR         0x4D
#define ICM42670_OFFSET_USER0            0x4E
#define ICM42670_OFFSET_USER1            0x4F
#define ICM42670_OFFSET_USER2            0x50
#define ICM42670_OFFSET_USER3            0x51
#define ICM42670_OFFSET_USER4            0x52
#define ICM42670_OFFSET_USER5            0x53
#define ICM42670_OFFSET_USER6            0x54
#define ICM42670_OFFSET_USER7            0x55
#define ICM42670_OFFSET_USER8            0x56
#define ICM42670_ST_STATUS1              0x63
#define ICM42670_ST_STATUS2              0x64
#define ICM42670_FDR_CONFIG              0x66
#define ICM42670_APEX_CONFIG12           0x67

// USER BANK 2
#define ICM42670_OPT_CTRL7               0x06

// USER BANK3
#define ICM42670_XA_ST_DATA              0x00
#define ICM42670_YA_ST_DATA              0x01
#define ICM42670_ZA_ST_DATA              0x02
#define ICM42670_XG_ST_DATA              0x03
#define ICM42670_YG_ST_DATA              0x04
#define ICM42670_ZG_ST_DATA              0x05

// Pre-defined settings
#define ICM42670_USER_BANK_MREG1        0x00
#define ICM42670_USER_BANK_MREG2        0x28
#define ICM42670_USER_BANK_MREG3        0x50
#define ICM42670_GYRO_RANGE_250		(0b11 << 5)
#define ICM42670_GYRO_RANGE_500		(0b10 << 5)
#define ICM42670_GYRO_RANGE_1000	(0b01 << 5)
#define ICM42670_GYRO_RANGE_2000	(0b00 << 5)
#define ICM42670_GYRO_ODR_12		0b1100
#define ICM42670_GYRO_ODR_25		0b1011
#define ICM42670_GYRO_ODR_50		0b1010
#define ICM42670_GYRO_ODR_100		0b1001
#define ICM42670_GYRO_ODR_200		0b1000
#define ICM42670_GYRO_ODR_400		0b0111
#define ICM42670_GYRO_ODR_800		0b0110
#define ICM42670_GYRO_ODR_1600		0b0101
#define ICM42670_GYRO_LPF_16HZ		0b0111
#define ICM42670_GYRO_LPF_25HZ		0b0110
#define ICM42670_GYRO_LPF_34HZ		0b0101
#define ICM42670_GYRO_LPF_53HZ		0b0100
#define ICM42670_GYRO_LPF_73HZ		0b0011
#define ICM42670_GYRO_LPF_121HZ		0b0010
#define ICM42670_GYRO_LPF_180HZ		0b0001
#define ICM42670_GYRO_LPF_DISABLE	0b0000
#define ICM42670_ACCEL_RANGE_2		(0b11 << 5)
#define ICM42670_ACCEL_RANGE_4		(0b10 << 5)
#define ICM42670_ACCEL_RANGE_8		(0b01 << 5)
#define ICM42670_ACCEL_RANGE_16		(0b00 << 5)
#define ICM42670_ACCEL_ODR_12		0b1100
#define ICM42670_ACCEL_ODR_25		0b1011
#define ICM42670_ACCEL_ODR_50		0b1010
#define ICM42670_ACCEL_ODR_100		0b1001
#define ICM42670_ACCEL_ODR_200		0b1000
#define ICM42670_ACCEL_ODR_400		0b0111
#define ICM42670_ACCEL_ODR_800		0b0110
#define ICM42670_ACCEL_ODR_1600		0b0101
#define ICM42670_ACCEL_LPF_16HZ		0b0111
#define ICM42670_ACCEL_LPF_25HZ		0b0110
#define ICM42670_ACCEL_LPF_34HZ		0b0101
#define ICM42670_ACCEL_LPF_53HZ		0b0100
#define ICM42670_ACCEL_LPF_73HZ		0b0011
#define ICM42670_ACCEL_LPF_121HZ	0b0010
#define ICM42670_ACCEL_LPF_180HZ	0b0001
#define ICM42670_ACCEL_LPF_DISABLE	0b0000

// Address definitions
#define ICM42670_ADDR0  0x68
#define ICM42670_ADDR1  0x69

// ICM42670 Pin Configurations
#define ICM42670_PIN_SDA        11
#define ICM42670_PIN_SCL        12
#define TWIM_FREQUENCY_400KHZ   0x04000000
#define TWIM_INTERRUPT_LASTRX   (1 << 23)

#include <zephyr/kernel.h>

/* Buffer for TWIM */
uint8_t rxBuffer[255] = {0}, txBuffer[255] = {0};

/* TWIM Interrupt Function */
void TWIM0_IRQHandler();

/* TWIM Tx function */
void writeBytes(uint8_t *data, uint8_t length);
void Write(uint8_t addr, uint8_t *data, uint8_t length);
void Read(uint8_t addr, uint8_t *recv, uint8_t recv_length, uint8_t *write, uint8_t write_length);
int16_t *getRawAccel();
int16_t *getRawGyro();

int main(void)
{
        // Initialize TWIM0(I2C)
        NRF_TWIM0->PSEL.SDA = ICM42670_PIN_SDA;
        NRF_TWIM0->PSEL.SCL = ICM42670_PIN_SCL;
        NRF_TWIM0->FREQUENCY = TWIM_FREQUENCY_400KHZ;
        NRF_TWIM0->TXD.PTR = (uint32_t)txBuffer;
        NRF_TWIM0->TXD.MAXCNT = 0;
        NRF_TWIM0->RXD.PTR = (uint32_t)rxBuffer;
        NRF_TWIM0->RXD.MAXCNT = 255;
        
        // Set interrupt for TWIM0
        NRF_TWIM0->INTENSET = TWIM_INTERRUPT_LASTRX;
        NRF_TWIM0->SHORTS = 0;
        IRQ_DIRECT_CONNECT(SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn, 0, TWIM0_IRQHandler, 0);
        irq_enable(SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn);

        // Enable & Start Rx
        NRF_TWIM0->ENABLE = 0x06;
        NRF_TWIM0->TASKS_STARTRX = 1;

        // Enable Sensor
        uint8_t data[2] = {ICM42670_PWR_MGMT0, 0x9F};
        Write(ICM42670_ADDR0, data, 2);

        // 가속도 센서 설정
        data[0] = ICM42670_ACCEL_CONFIG0;
        data[1] = ICM42670_ACCEL_RANGE_2 | ICM42670_ACCEL_ODR_800;
        Write(ICM42670_ADDR0, data, 2);
        data[0] = ICM42670_ACCEL_CONFIG1;
        data[1] = ICM42670_GYRO_LPF_16HZ;
        Write(ICM42670_ADDR0, data, 2);

        // 자이로 센서 설정
        data[0] = ICM42670_GYRO_CONFIG0;
        data[1] = ICM42670_GYRO_RANGE_1000 | ICM42670_GYRO_ODR_800;
        Write(ICM42670_ADDR0, data, 2);
        data[0] = ICM42670_GYRO_CONFIG1;
        data[1] = ICM42670_GYRO_LPF_16HZ;
        Write(ICM42670_ADDR0, data, 2);
        while(true){
                // Main Loop
                int16_t *ACCEL, *GYRO;
                ACCEL = getRawAccel();
                GYRO = getRawGyro();
                printk("%d,%d,%d,%d,%d,%d\n", ACCEL[0], ACCEL[1], ACCEL[2], GYRO[0], GYRO[1], GYRO[2]);
        }
        return 0;
}
void Write(uint8_t addr, uint8_t *data, uint8_t length){
        memset(rxBuffer, 0x00, sizeof(rxBuffer));
        memcpy(txBuffer, data, length);
        NRF_TWIM0->ADDRESS = addr;
        NRF_TWIM0->TXD.MAXCNT = length;
        NRF_TWIM0->TASKS_STARTTX = 1;
        while(!NRF_TWIM0->EVENTS_TXSTARTED){}
        NRF_TWIM0->EVENTS_TXSTARTED = 0;
        while(!NRF_TWIM0->EVENTS_LASTTX){}
        NRF_TWIM0->EVENTS_LASTTX = 0;
        NRF_TWIM0->TASKS_STOP = 1;
        while(!NRF_TWIM0->EVENTS_STOPPED){}
        NRF_TWIM0->EVENTS_STOPPED = 0;
}

void TWIM0_IRQHandler(){
        // TWIM Interrupt Handler Functions
        if(NRF_TWIM0->EVENTS_LASTRX == 1){
                // Last RX Events
                NRF_TWIM0->EVENTS_LASTRX = 0;
        }
}

void Read(uint8_t addr, uint8_t *recv, uint8_t recv_length, uint8_t *write, uint8_t write_length){
        // 데이터 Read 함수
        uint8_t *output = recv;
        memset(txBuffer, 0x00, sizeof(txBuffer));
        memset(rxBuffer, 0x00, sizeof(rxBuffer));
        memcpy(txBuffer, write, write_length);
        NRF_TWIM0->ADDRESS = addr;
        NRF_TWIM0->TXD.MAXCNT = write_length;
        NRF_TWIM0->TASKS_STARTTX = 1;
        while(!NRF_TWIM0->EVENTS_LASTTX){}
        NRF_TWIM0->EVENTS_LASTTX = 0;
        NRF_TWIM0->TASKS_STARTRX = 1;
        while(!NRF_TWIM0->EVENTS_LASTRX){}
        NRF_TWIM0->EVENTS_LASTRX = 0;
        NRF_TWIM0->TASKS_STOP = 1;
        while(!NRF_TWIM0->EVENTS_STOPPED){}
        NRF_TWIM0->EVENTS_STOPPED = 0;
        for(uint8_t i=0;i<recv_length;i++){
                output[i] = rxBuffer[i];
        }
}

int16_t *getRawAccel(){
    static int16_t output[3] = {0};
    uint8_t reg_addr = ICM42670_ACCEL_DATA_X1;
    uint8_t temp[6] = {0};
    Read(ICM42670_ADDR0, temp, 6, &reg_addr, 1);
    for(uint8_t i=0;i<3;i++){
        output[i] = (temp[2*i] << 8) | temp[2*i + 1];
    }
    return output;
}

int16_t *getRawGyro(){
    static int16_t output[3] = {0};
    uint8_t reg_addr = ICM42670_GYRO_DATA_X1;
    uint8_t temp[6] = {0};
    Read(ICM42670_ADDR0, temp, 6, &reg_addr, 1);
    for(uint8_t i=0;i<3;i++){
        output[i] = (temp[2*i] << 8) | temp[2*i + 1];
    }
    return output;
}