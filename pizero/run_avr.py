#!/usr/bin/env python3
import time
from spi import BitBangSPI
#!/usr/bin/env python
#
# Bitbang'd SPI interface with an MCP3008 ADC device
# MCP3008 is 8-channel 10-bit analog to digital converter
#  Connections are:
#     CLK => 18  
#     DOUT => 23 (chip's data out, RPi's MISO)
#     DIN => 24  (chip's data in, RPi's MOSI)
#     CS => 25 

import RPi.GPIO as GPIO
import time
import sys

# GPIO 5 als Output verwenden
reset_pin = 5  

spi_dev = BitBangSPI(delay=0.001)

GPIO.setup(reset_pin, GPIO.OUT)

text = ""
print("RUN AVR")
GPIO.output(reset_pin, True)

while input().upper() != "Q":
    text = ""
    while (last_byte := spi_dev.spi_transfer(0)) == 0:
        time.sleep(1)
        continue
    
    while(last_byte != 0):
        print("A")
        text += chr(last_byte)
        last_byte = spi_dev.spi_transfer(0)
        
    text+=" "
    print("Rec:", text)
    
GPIO.output(reset_pin, False)
time.sleep(1)
spi_dev.cleanup_gpio()