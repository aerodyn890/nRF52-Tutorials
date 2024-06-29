# LED Control Tutorial

## Summary
Control on-board RGB LED in Roverdyn Inc. nRF52DK development kit.

- **Author** : S.W. Jeong
- **License** : GPLv2
- **Last update** : Feb. 19, 2024
- **Target MCU** : nRF52810-QFAA, nRF52832-QFAA

## Environment
  - **Microsoft Visual Studio** : 1.85.1
  - **NCS Toolchain** : 2.5.0
  - **NCS SDK** : 2.5.0
  - **Zephyr Version** : 3.4.99-ncs1

## Implementation
1. Connect the USB-C cable or connect the battery to provide power.
2. Connect J-Link or other debugger/programmer to target board.
3. Select MCU type(nrf52810/nrf52832) and click "Build All Configurations" in NRF CONNECT:APPLICATIONS panel.
4. After build complete, connect debugger and click "Flash All Linked Devices"
5. After download complete, push the reset button or connect through J-Link RTT Viewer if you have "J-Link debugger"
