##### I2C COMMUNITY BETWEEN 2 MCU ####

#  IDE:    S32DS version 3.5
#  MCU:    S32K144EVB Devkit

## result:    Successfully
## tool test: Logic analyzer

## NOTE: 
## Sequence:
# 1. Load Mater program into MCU 1, and load Slave program into MCU 2.
# 2. Reset MCU 2 first, after that reset MCU 1.
# 3. Using A2, A3 to connect between 2 MCU (another wire for GND)
# 4. Using logic analyzer to check

## ON slave:
#  case 1: We can use Led blink with frequence 1 second to 10 seconds to check LPIT frequence base on ADC value from master.
#  case 2: Using D11 is pin_3, D12 is pin_4


## THANK YOU