# ESP32-LanNetworking-EEPROM
Stores all needed information in ESP-32 EERPOM for Ethernet connection. Stores: IP, Subnet, Gateway, DNS, and MAC address

Hardware
ESP-32
W5500
DSD OLED

Code
This code loads networking information into an ESP-32 EEPROM and then reads the EEPROM to verify networking information was saved to EEPROM. The EEPROM is read to the serial monitor and an OLED I2C display. This makes it easy to verity networking information is correct when setting up hardware. 

Other code can then be loaded onto the ESP-32 to use Ethernet hardware, such as W5500, and the networking information will still be in EEPROM from new code to reference. 

Enjoy,
Let me know if you have any questions. 
