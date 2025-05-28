#include <WiFi.h>
#include <PubSubClient.h>
#include <SPIFFS.h>


// Credentials of Wi-Fi
const char* ssid = "";
const char* password = "";


// MQTT Specifications
const char* mqttServer = "";
const uint16_t mqttPort = 1883; //No TLS
const char* mqttTopic = "esp32/";


// Funtions
void initWifi();
void mqtt_Reconect();
void sendImage();


//Objects
WiFiClient espClient;
PubSubClient mqttClient(espClient);


void setup() {
 
  //Inicialize the baudrate of ESP32
  Serial.begin(115200);

//Evaluate an image upload with SPIFFS
  if (!SPIFFS.begin(true)) {  
    Serial.println("Error al inicializar SPIFFS");
    return;
  }
 
  //Set the IP and Port for connection (Broker)
  mqttClient.setServer(mqttServer, mqttPort);
  
  initWifi(); 
  mqtt_Reconect(); //Inicialize the client against the broker
  
  sendImage("/"); 
}


void loop() {
  if (!mqttClient.connected()) {
    mqtt_Reconect();
  }
  mqttClient.loop();
}

void initWifi(){ 
  // Conectar WiFi
  Serial.print("Conectando a ...");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connection established");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  }


  void mqtt_Reconect(){ 


   while(!mqttClient.connected()){
   
    Serial.println("Connecting to broker MQTT ...");
   
    if(mqttClient.connect("esp32")){
      Serial.println("Connected");
     
      //Assign the topic where did u want subscribe
      mqttClient.subscribe(mqttTopic);
    }
    else{
    Serial.println("Cannot be connected!");
    Serial.println(mqttClient.state());
    delay(5000);
      }
    }
  }

void sendImage(const char* path) {  
  File file = SPIFFS.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("Fail to open an image");
    return;
  }

  Serial.println("Send image to broker ...");

  while (file.available()) {
    size_t len = 512;
    uint8_t buf[len];
    size_t readBytes = file.read(buf, len);
    mqttClient.publish(mqttTopic, buf, readBytes);
    delay(100); // Assigned for not satured a broker with rate of packet for unit of time
  }

  file.close();
  Serial.println("Image send.");
}
