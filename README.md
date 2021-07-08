# APRS-rainsensor
Please star and fork it for my work. Thanks!

## Version
1. rain.uno => version 1.0
2. rainy.uno => version 2.0 (sending package through the server with API from header)

## What You Need
1. NodeMCU ESP8266 v3
2. Raindrop Sensor

## What You Can Do First!
1. Install Arduino
2. Install USB Driver CH340G
3. Install Additional Board Manager ESP8266

## Install Additional Board Manager ESP8266
1. Open Arduino application
2. Click File
3. Click Preferences
4. Insert "http://arduino.esp8266.com/stable/package_esp8266com_index.json" in Additional Boards Manager URLs
5. Click OK
6. Click Tools
7. Pick "NodeMCU 1.0 (ESP-12E Module)" in Board
8. Pick Upload Speed 115200

## Cable Connection
Raindrop sensor to ESP8266
```bash
- (VCC) to 3V
- (GND) to G
- (DO) to A0
```

## Configuration
### IP and Port Configuration
```bash
const uint16_t port = 14580; // APRS port server
const char * host = "103.56.149.95"; // IP APRS server
WiFiClient client; 
delay(5000); //delay send data to server
```

### APRS Call ID & Passcode Configuration
```bash
client.println("user SRD001 pass 21681 vers H-001 filter m/1");  // parameter aprs id
delay (250);
client.print("SRD001>APB001,TCPIP*,qAC,WIDE1-1:=0614.73S&10647.99E` }e05]?]]?]??{!EMERGENCY!");     // paremeter aprs
client.println("SRD001>APB001,TCPIP*,qAC,WIDE1-1:>HUJAN"); // paremeter aprs
delay(10000);
```
**You can get Passcode in https://apps.magicbug.co.uk/passcode/index.php/passcode**
