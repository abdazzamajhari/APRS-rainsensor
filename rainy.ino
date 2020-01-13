#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define SLEEP_DELAY 3000

// Configuration API Server
// === START ===
const char * serverName = "https://azhamudev.com";
String apiKeyValue = "You_Cant&SeeMe!";
String sensorName = "RAIN";
String sensorLocation = "PETSEL";
String sensorLatitude = "-6.2517081";
String sensorLongitude = "106.7565931";
// === END ===

const char* ssid = "Azzam"; //nama wifi
const char* password = "azzam53a"; //wifi password

WiFiClient client;

int sensorPin = A0; //pinout sensor hujan   
int enable2 = 13;      // enable reading Rain sensor
int sensorValue2 = 0;  // variable to store the value coming from sensor Rain sensor

void setup() {
  // declare the enable and ledPin as an OUTPUT:
  pinMode(enable2, OUTPUT);
  Serial.begin(115200);
  
  delay(10);
  
  WiFi.begin(ssid, password);
  
  Serial.println();
  Serial.println();
  
  Serial.print("Connecting to ");
  
  Serial.println(ssid);
  
  Serial.print("..........");
  
  Serial.println();
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  }
  
  Serial.println("TERHUBUNG WIFI");
  Serial.println();
}

void closeConnection(HTTPClient * pClientToClose) {
  pClientToClose -> end();
  delay(SLEEP_DELAY);
}

void loop() {
//--------------------------Rain Sensor-------------------------
  HTTPClient http;

  delay(500);
  
  sensorValue2 = analogRead(sensorPin);
  sensorValue2 = constrain(sensorValue2, 150, 440); 
  sensorValue2 = map(sensorValue2, 150, 440, 1023, 0); 
  
  if (sensorValue2>= 20){  
    Serial.print("HUJAN");
    digitalWrite(enable2, HIGH);
    HTTPClient http;
      
          const uint16_t port = 14580; // masukkan port aprs server
          const char * host = "103.56.149.95"; // masukkan IP aprs server
          WiFiClient client; 
          delay(5000); //
   
          if (!client.connect(host, port)) {        
             return;
          }
   
          client.println("user SRD002 pass 21682 vers H-001 filter m/1");  // paremeter aprs id
          delay (250);
           client.print("SRD002>APB001,TCPIP*,qAC,WIDE1-1:=0615.09S&10645.68E` }e05]?]]?]??{!EMERGENCY!");     // paremeter aprs
           client.println("SRD002>APB001,TCPIP*,qAC,WIDE1-1:>HUJAN"); // paremeter aprs
           delay(10000);

          // Insert to API Server
          // === START ===
          // Your Domain name with URL path or IP address with path
          http.begin(serverName);
          // Specify content-type header
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          // Prepare your HTTP POST request data
          String httpRequestData = "api_key=" + apiKeyValue 
                            + "&sensor=" + sensorName
                            + "$value=" + sensorValue2
                            + "&description=" + "HUJAN" // if sensor value >= 20
                            + "&location=" + sensorLocation 
                            + "&latitude=" + sensorLatitude 
                            + "&longitude=" + sensorLongitude;
          Serial.print("httpRequestData: ");
          Serial.println(httpRequestData);
          // === END ===
    }
    else{
      Serial.print("TIDAK HUJAN");
      digitalWrite(enable2, LOW); 

          // Insert to API Server
          // === START ===
          // Your Domain name with URL path or IP address with path
          http.begin(serverName);
          // Specify content-type header
          http.addHeader("Content-Type", "application/x-www-form-urlencoded");
          // Prepare your HTTP POST request data
          String httpRequestData = "api_key=" + apiKeyValue 
                            + "&sensor=" + sensorName
                            + "$value=" + sensorValue2
                            + "&description=" + "TIDAK HUJAN" // if sensor value < 20
                            + "&location=" + sensorLocation 
                            + "&latitude=" + sensorLatitude 
                            + "&longitude=" + sensorLongitude;
          Serial.print("httpRequestData: ");
          Serial.println(httpRequestData);
          // === END ===
    }
  
    Serial.print("Rain value:       ");
  
    Serial.println(sensorValue2);
    Serial.println();
  
    delay(100);
}
