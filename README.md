# APRS-rainsensor

1. Install Arduino
2. Install USB Driver CH340G
3. Install Additional Board Manager ESP8266

##Install Additional Board Manager ESP8266
1. Open Arduino application
2. Click File
3. Click Preferences
4. Insert "http://arduino.esp8266.com/stable/package_esp8266com_index.json" in Additional Boards Manager URLs
5. Click OK
6. Click Tools
7. Pick "NodeMCU 1.0 (ESP-12E Module)" in Board
8. Pick a Port 115200

##Configuration
``
IP and Port Configuration
``
90. const uint16_t port = 14580; // APRS port server
91. const char * host = "103.56.149.95"; // IP APRS server
92. WiFiClient client; 
93. delay(5000); //delay send data to server

``
APRS Call ID & Passcode Configuration
``
100. client.println("user SRD001 pass 21681 vers H-001 filter m/1");  // paremeter aprs id
101. delay (250);
102. client.print("SRD001>APB001,TCPIP*,qAC,WIDE1-1:=0614.73S&10647.99E` }e05]?]]?]??{!EMERGENCY!");     // paremeter aprs
103. client.println("SRD001>APB001,TCPIP*,qAC,WIDE1-1:>HUJAN"); // paremeter aprs
104. delay(10000);

**You can get Passcode in https://apps.magicbug.co.uk/passcode/index.php/passcode**
