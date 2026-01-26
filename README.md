###### MOCK MCU - BOOT LOADER ######

## TrungNV87
## S32DS version 3.5
## Board S32K144

## Guide ##
# Reset - red light will be blink 3 times
# keep sw2 on board until blue light on
# transmit data from terminal throught UART to board (S-record file)
# if green light on -> successfully
# if red light   on -> fail

# reset - red light will be blink 3 times
# not do anything -> application will be run(if it was flash success before)

## Application start with 0x4000
## baud rate  = 9600

### THANK YOU