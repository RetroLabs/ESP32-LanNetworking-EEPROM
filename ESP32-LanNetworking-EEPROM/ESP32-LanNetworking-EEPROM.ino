/* 
 * Write IP information to ESP-32 EEPROM
 * Display IP information over Serial and OLED
 */

// Download libraries from library manager
#include <SPI.h>
#include "EEPROM.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// MAC address
uint8_t eth_MAC[] = { 0x12, 0xF0, 0x2D, 0xBE, 0x14, 0x15 };

// Varibles for IP address. Each holds one octet
byte IPa = 10;
byte IPb = 0;
byte IPc = 0;
byte IPd = 35;

// varibles for Subnet address.
byte subA = 255;
byte subB = 255;
byte subC = 255;
byte subD = 0;

// varibles for DNS address.
// default is 8.8.8.8 Google DNS
byte DNSa = 8;
byte DNSb = 8;
byte DNSc = 8;
byte DNSd = 8;

// varibles for Gateway address.
byte GWa = 10;
byte GWb = 0;
byte GWc = 0;
byte GWd = 1;

// varibles for MAC address.
byte MACa = 0;
byte MACb = 0;
byte MACc = 0;
byte MACd = 0;
byte MACe = 0;
byte MACf = 0;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ip string for EEPROM
String ipInputAddress = "";
uint8_t ip[4];

// EEPROM addresses
int IPaddress = 100;
int SUBaddress = 105;
int GWaddress = 110;
int DNSaddress = 115;
int MACaddress = 120;

IPAddress eth_IP(IPa, IPb, IPc, IPd);
IPAddress eth_MASK(subA, subB, subC, subD);
IPAddress eth_DNS(DNSa, DNSb, DNSc, DNSd);
IPAddress eth_GW(GWa, GWb, GWc, GWd);

void setup() {

    // delay needed for serial to begin correctly
    delay(1000);
    Serial.begin(115200);
    Serial.println("Serial Started @ 115200 baud");
    
    // Starts EEPROM and tests it. Will Reboot and test again if fails
    Serial.println("Testing EEPROM Library");
    Serial.println(" ");
    
      if (!EEPROM.begin(1000)) {
        Serial.println("Failed to initialise EEPROM");
        Serial.println("Restarting...");
        delay(1000);
        ESP.restart();
      }

    // Writing EEPROM data for IP information for the first time
    Serial.print("Writing IP address to EEPROM: ");
    Serial.println(IPaddress);
                          
    EEPROM.writeByte(IPaddress, IPa);
    IPaddress += sizeof(byte);
    EEPROM.writeByte(IPaddress, IPb); 
    IPaddress += sizeof(byte);
    EEPROM.writeByte(IPaddress, IPc);
    IPaddress += sizeof(byte);
    EEPROM.writeByte(IPaddress, IPd);
    IPaddress += sizeof(byte);

    // test to see byte addresses
    Serial.print("Ending byte IP address on EEPROM: ");
    Serial.println(IPaddress-1);
                          
    EEPROM.commit();

    // Read and view IP information over Serial 
    IPaddress = 100;
    Serial.print("IP Address read from EEPROM: ");
    IPa = EEPROM.readByte(IPaddress);
    Serial.print(IPa);
    IPaddress += sizeof(byte);
    Serial.print(".");
    IPb = EEPROM.readByte(IPaddress);
    Serial.print(IPb);
    IPaddress += sizeof(byte);
    Serial.print(".");
    IPc = EEPROM.readByte(IPaddress);
    Serial.print(IPc);
    IPaddress += sizeof(byte);
    Serial.print(".");
    IPd = EEPROM.readByte(IPaddress);
    Serial.println(IPd);
    IPaddress += sizeof(byte);
    Serial.println(" ");   

    // Writing EEPROM data for Subnet information for the first time
    Serial.print("Writing Subnet address to EEPROM: ");
    Serial.println(SUBaddress);
                          
    EEPROM.writeByte(SUBaddress, subA);
    SUBaddress += sizeof(byte);
    EEPROM.writeByte(SUBaddress, subB); 
    SUBaddress += sizeof(byte);
    EEPROM.writeByte(SUBaddress, subC);
    SUBaddress += sizeof(byte);
    EEPROM.writeByte(SUBaddress, subD);
    SUBaddress += sizeof(byte);

    // test to see byte addresses
    Serial.print("Ending byte Subnet address on EEPROM: ");
    Serial.println(SUBaddress-1);
                          
    EEPROM.commit();

    // Read and view Subnet information over Serial 
    SUBaddress = 105;
    Serial.print("Subnet Address read from EEPROM: ");

    subA = EEPROM.readByte(SUBaddress);
    Serial.print(subA);
    SUBaddress += sizeof(byte);
    Serial.print(".");
    subB = EEPROM.readByte(SUBaddress);
    Serial.print(subB);
    SUBaddress += sizeof(byte);
    Serial.print(".");
    subC = EEPROM.readByte(SUBaddress);
    Serial.print(subC);
    SUBaddress += sizeof(byte);
    Serial.print(".");
    subD = EEPROM.readByte(SUBaddress);
    Serial.println(subD);
    SUBaddress += sizeof(byte);
    Serial.println(" ");   

    // Writing EEPROM data for Gateway information for the first time
    Serial.print("Writing Gateway address to EEPROM: ");
    Serial.println(GWaddress);
                          
    EEPROM.writeByte(GWaddress, GWa);
    GWaddress += sizeof(byte);
    EEPROM.writeByte(GWaddress, GWb); 
    GWaddress += sizeof(byte);
    EEPROM.writeByte(GWaddress, GWc);
    GWaddress += sizeof(byte);
    EEPROM.writeByte(GWaddress, GWd);
    GWaddress += sizeof(byte);

    // test to see byte addresses
    Serial.print("Ending byte Gateway address on EEPROM: ");
    Serial.println(GWaddress-1);
                          
    EEPROM.commit();

    // Read and view Gateway information over Serial 
    GWaddress = 110;
    Serial.print("Gateway Address read from EEPROM: ");

    subA = EEPROM.readByte(GWaddress);
    Serial.print(subA);
    GWaddress += sizeof(byte);
    Serial.print(".");
    subB = EEPROM.readByte(GWaddress);
    Serial.print(subB);
    GWaddress += sizeof(byte);
    Serial.print(".");
    subC = EEPROM.readByte(GWaddress);
    Serial.print(subC);
    GWaddress += sizeof(byte);
    Serial.print(".");
    subD = EEPROM.readByte(GWaddress);
    Serial.println(subD);
    GWaddress += sizeof(byte);
    Serial.println(" ");   

// Writing EEPROM data for IP information for the first time
    Serial.print("Writing DNS address to EEPROM: ");
    Serial.println(DNSaddress);
                          
    EEPROM.writeByte(DNSaddress, DNSa);
    DNSaddress += sizeof(byte);
    EEPROM.writeByte(DNSaddress, DNSb); 
    DNSaddress += sizeof(byte);
    EEPROM.writeByte(DNSaddress, DNSc);
    DNSaddress += sizeof(byte);
    EEPROM.writeByte(DNSaddress, DNSd);
    DNSaddress += sizeof(byte);

    // test to see byte addresses
    Serial.print("Ending byte DNS address on EEPROM: ");
    Serial.println(DNSaddress-1);
                          
    EEPROM.commit();

    // Read and view DNS information over Serial 
    DNSaddress = 115;
    Serial.print("DNS Address read from EEPROM: ");
    DNSa = EEPROM.readByte(DNSaddress);
    Serial.print(DNSa);
    DNSaddress += sizeof(byte);
    Serial.print(".");
    DNSb = EEPROM.readByte(DNSaddress);
    Serial.print(DNSb);
    DNSaddress += sizeof(byte);
    Serial.print(".");
    DNSc = EEPROM.readByte(DNSaddress);
    Serial.print(DNSc);
    DNSaddress += sizeof(byte);
    Serial.print(".");
    DNSd = EEPROM.readByte(DNSaddress);
    Serial.println(DNSd);
    DNSaddress += sizeof(byte);
    Serial.println(" ");   

//================================================================================

// Writing EEPROM data for IP information for the first time
    Serial.print("Writing MAC address to EEPROM: ");
    Serial.println(MACaddress);                    
    EEPROM.writeByte(MACaddress, eth_MAC[0]);
    MACaddress += sizeof(byte);
    EEPROM.writeByte(MACaddress, eth_MAC[1]); 
    MACaddress += sizeof(byte);
    EEPROM.writeByte(MACaddress, eth_MAC[2]);
    MACaddress += sizeof(byte);
    EEPROM.writeByte(MACaddress, eth_MAC[3]);
    MACaddress += sizeof(byte);
    EEPROM.writeByte(MACaddress, eth_MAC[4]);
    MACaddress += sizeof(byte);
    EEPROM.writeByte(MACaddress, eth_MAC[5]);
    MACaddress += sizeof(byte);

    // test to see byte addresses
    Serial.print("Ending byte MAC address on EEPROM: ");
    Serial.println(MACaddress-1);
                          
    EEPROM.commit();

    // Read and view DNS information over Serial 
    MACaddress = 120;
    Serial.print("MAC Address read from EEPROM: ");
    
    MACa = EEPROM.readByte(MACaddress);   
    MACaddress += sizeof(byte);
    Serial.print(MACa, HEX);
    Serial.print(":");
    MACb = EEPROM.readByte(MACaddress);
    Serial.print(MACb, HEX);
    MACaddress += sizeof(byte);
    Serial.print(":");
    MACc = EEPROM.readByte(MACaddress);
    Serial.print(MACc, HEX);
    MACaddress += sizeof(byte);
    Serial.print(":");
    MACd = EEPROM.readByte(MACaddress);
    Serial.print(MACd, HEX);
    MACaddress += sizeof(byte);
    Serial.print(":");
    MACe = EEPROM.readByte(MACaddress);
    Serial.print(MACe, HEX);
    MACaddress += sizeof(byte);
    Serial.print(":");
    MACf = EEPROM.readByte(MACaddress);
    Serial.println(MACf, HEX);
    MACaddress += sizeof(byte);
    Serial.println(" ");   

    eth_MAC[0] = MACa;
    eth_MAC[1] = MACb;
    eth_MAC[2] = MACc;
    eth_MAC[3] = MACd;
    eth_MAC[4] = MACe;
    eth_MAC[5] = MACf;
  
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    // OLED Display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
      }

  // delay to allow user to see boot screen
  delay(500);

  // Shows devices IP address for users knowledge
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(eth_IP);
//  display.println(Ethernet.localIP());
  display.display();      // Show initial text


}

void loop() {
  
    // Shows devices IP address for users knowledge
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("EEPROM IP:");
  display.println(eth_IP);
  display.display();      // Show initial text

  delay(2000);

  // Shows devices Subnet address for users knowledge
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("EEPROM Subgate:");
  display.println(eth_MASK);
  display.display();      // Show initial text

  delay(2000);

  // Shows devices Gateway address for users knowledge
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("EEPROM Gateway:");
  display.println(eth_GW);
  display.display();      // Show initial text

  delay(2000);

  // Shows devices DNS address for users knowledge
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("EEPROM DNS:");
  display.println(eth_DNS);
  display.display();      // Show initial text

  delay(2000);

  // Shows devices DNS address for users knowledge
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("MAC:");
  display.print(MACa, HEX);
  display.print(":");
  display.print(MACb, HEX);
  display.print(":");
  display.print(MACc, HEX);
  display.print(":");
  display.print(MACd, HEX);
  display.print(":");
  display.print(MACe, HEX);
  display.print(":");
  display.print(MACf, HEX);
  display.display();      // Show initial text

  delay(2000);
  }
