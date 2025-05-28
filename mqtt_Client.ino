#include <WiFi.h>
#include <PubSubClient.h>
#include <SPIFFS.h>


// CONFIGURACIÓN WIFI
const char* ssid = "";
const char* password = "";


// CONFIGURACIÓN MQTT
const char* mqttServer = "";
const uint16_t mqttPort = 1883; //No TLS
const char* mqttTopic = "esp32/ag1";


//Funciones
void initWifi();
void mqtt_Reconect();
void sendImage();


//Objetos
WiFiClient espClient;
PubSubClient mqttClient(espClient);


void setup() {
 
  //Inicializas la velocidad de operatividad del micro
  Serial.begin(115200);

//Evaluas si lee correctamente de la memoria la imagen precargada
// (No usamos SD)
  if (!SPIFFS.begin(true)) {  
    Serial.println("Error al inicializar SPIFFS");
    return;
  }
 
  //Asignas IP y puerto de servicio del broker MQTT
  mqttClient.setServer(mqttServer, mqttPort);
  
 //Debido a que el dispositivo opera con tecnología WiFi, 
 // asignas credenciales de acceso al medio
  initWifi(); 
  mqtt_Reconect(); //Aseguramos la conectividad al broker
  
 //La imagen cargada a la flash se manda
  sendImage("/ag1.png"); 
}


void loop() {
  if (!mqttClient.connected()) {
    mqtt_Reconect();
  }
  mqttClient.loop();
}

//Función de conexión por WiFi empleando credenciales
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
  Serial.println("Conexión establecida");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  }


  void mqtt_Reconect(){ //Función de conectividad al broker


   while(!mqttClient.connected()){
   
    Serial.println("Conectando al servidor MQTT ...");
   
    if(mqttClient.connect("esp32")){
      Serial.println("Conectado");
      /*Topicos a los que suscribirse*/
      mqttClient.subscribe(mqttTopic);
    }
    else{
    Serial.println("Fallo al iniciar sesión");
    Serial.println(mqttClient.state());
    delay(5000);
      }
    }
  }

// Función encarga de obtener la imagen y mandarla de manera
// fragmentada debido a sus limitaciones
void sendImage(const char* path) {  
  File file = SPIFFS.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("Fallo al abrir la imagen");
    return;
  }

  Serial.println("Enviando imagen por MQTT...");

  while (file.available()) {
    size_t len = 512;
    uint8_t buf[len];
    size_t readBytes = file.read(buf, len);
    mqttClient.publish(mqttTopic, buf, readBytes);
    delay(100); // Para evitar saturar el broker
  }

  file.close();
  Serial.println("Imagen enviada.");
}
